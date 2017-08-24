#!/usr/bin/env bash
set -e

function errecho {
    >&2 echo $@
}

# Customization variables.
CE3D2_SOURCE_DIRECTORY=CE3D2
CE3D2_BUILD_DIRECTORY=build
CE3D2_DOCS_BUILD_DIRECTORY=$CE3D2_BUILD_DIRECTORY/docs
CE3D2_DEBUG_BUILD_DIRECTORY=$CE3D2_BUILD_DIRECTORY/debug
CE3D2_RELEASE_BUILD_DIRECTORY=$CE3D2_BUILD_DIRECTORY/release
CE3D2_PUBLISH_DIRECTORY=$CE3D2_BUILD_DIRECTORY/publish

CMAKE_FLAGS=""
CMAKE_DEBUG_FLAGS="-DCMAKE_BUILD_TYPE=Debug -DTESTS_ENABLED=ON"
CMAKE_RELEASE_FLAGS="-DCMAKE_BUILD_TYPE=Release"
CMAKE_DOCS_FLAGS="-DCMAKE_BUILD_TYPE=Documentation"

# Executes the given task while displaying the task description.
function task {
    echo -n $1
    ${*/$1/""}
    echo " Done."
}

# Creates the given build directory.
function create_build_directory {
    if ! test -d "$1"; then
        task "Creating build directory..." \
            mkdir -p "$1"
    fi
}

# Performs the common build steps for all build targets.
# Arguments:
# 1: The build directory.
# 2: Additional flags to pass to CMake together with CMAKE_FLAGS.
# 3: The target for the generated makefile (can be left empty).
function build {
    create_build_directory $1
    working_dir=$(pwd)

    cd $1

    cmake $working_dir/$CE3D2_SOURCE_DIRECTORY $CMAKE_FLAGS $2
    make $3

    cd $working_dir
}


function TARGET_help {
    echo "Following targets are available:"
    echo
    echo "help       Displays this help."
    echo
    echo "debug      Build CE3D2 (debug) into '$CE3D2_DEBUG_BUILD_DIRECTORY'."
    echo "release    Build CE3D2 (release) into" \
                     "'$CE3D2_RELEASE_BUILD_DIRECTORY'."
    echo "docs       Builds the HTML documentation into" \
                     "'$CE3D2_DOCS_BUILD_DIRECTORY/html'."
    echo "install debug|release"
    echo "           Installs CE3D2 onto your system."
    echo "publish    Publishes CE3D2 binaries. This command creates also"
    echo "           necessary branches and commits to advance the versions"
    echo "           correctly. If a custom version (MAJOR.MINOR) is provided"
    echo "           as argument, this will be the next dev-version incremented"
    echo "           to. If no argument is given, the minor-version will be"
    echo "           incremented by one as the next dev-version."
    echo "clean      Clean up build files."
}

function TARGET_debug {
    build $CE3D2_DEBUG_BUILD_DIRECTORY "$CMAKE_DEBUG_FLAGS"
}

function TARGET_release {
    build $CE3D2_RELEASE_BUILD_DIRECTORY "$CMAKE_RELEASE_FLAGS"
}

function TARGET_docs {
    build $CE3D2_DOCS_BUILD_DIRECTORY "$CMAKE_DOCS_FLAGS" doc
}

function TARGET_install {
    if [ "$1" == "debug" ]; then
        build $CE3D2_DEBUG_BUILD_DIRECTORY "$CMAKE_DEBUG_FLAGS" install
    elif [ "$1" == "release" ]; then
        build $CE3D2_RELEASE_BUILD_DIRECTORY "$CMAKE_RELEASE_FLAGS" install
    else
        echo "Invalid parameter for install target, use 'debug' or 'release'."
    fi
}

function TARGET_clean {
    task "Deleting debug build..." \
        rm -rf $CE3D2_DEBUG_BUILD_DIRECTORY
    task "Deleting release build..." \
        rm -rf $CE3D2_RELEASE_BUILD_DIRECTORY
    task "Deleting documentation..." \
        rm -rf $CE3D2_DOCS_BUILD_DIRECTORY
}

function TARGET_publish {
    # Read the current CE3D2 version using the main CMakeLists.txt
    CMAKE_LISTS_CONTENTS="$(cat $CE3D2_SOURCE_DIRECTORY/CMakeLists.txt)"
    regex="set\(CE3D2_VERSION_MAJOR ([0-9]+)\)"
    [[ $CMAKE_LISTS_CONTENTS =~ $regex ]] && \
        CE3D2_VERSION_MAJOR=${BASH_REMATCH[1]}
    regex="set\(CE3D2_VERSION_MINOR ([0-9]+)\)"
    [[ $CMAKE_LISTS_CONTENTS =~ $regex ]] && \
        CE3D2_VERSION_MINOR=${BASH_REMATCH[1]}
    regex="set\(CE3D2_VERSION_MICRO ([0-9]+|dev)\)"
    [[ $CMAKE_LISTS_CONTENTS =~ $regex ]] && \
        CE3D2_VERSION_MICRO=${BASH_REMATCH[1]}

    CE3D2_VERSION="$CE3D2_VERSION_MAJOR.$CE3D2_VERSION_MINOR.$CE3D2_VERSION_MICRO"

    if [ "$CE3D2_VERSION_MICRO" != "dev" ]; then
        errecho "CE3D2's version is currently a release version ($CE3D2_VERSION)!"
        errecho "Please change CE3D2_VERSION_MICRO back to 'dev' inside"
        errecho "CMakeLists.txt before publishing again."
        return 1
    fi

    # Save away current branch name to switch back again to in the end.
    branch_name=$(git symbolic-ref -q HEAD)
    branch_name=${branch_name##refs/heads/}
    branch_name=${branch_name:-HEAD}

    function replace {
        grep -q "$1" "$3"
        sed --in-place --expression "s/$1/$2/g" $3
    }

    # Start release modifications on a new branch. Stash away existing changes.
    number_of_stashes=`git stash list | wc -l`
    git stash
    if [ "$number_of_stashes" -eq "$(git stash list | wc -l)" ]; then
        stash_pop_needed="no"
    else
        stash_pop_needed="yes"
    fi

    branch_name_release="release-$CE3D2_VERSION_MAJOR.$CE3D2_VERSION_MINOR"
    git checkout -b $branch_name_release

    # Modify versions and other information in source.
    replace "set(CE3D2_VERSION_MICRO dev)" "set(CE3D2_VERSION_MICRO 0)" CE3D2/CMakeLists.txt
    replace "PROJECT_NUMBER\( *\)= \"\\\${PROJECT_VERSION} (at \\\${GIT_HEAD} on \\\${GIT_BRANCH})\"" "PROJECT_NUMBER\1= \"\\\${PROJECT_VERSION}\"" CE3D2/doxyfile.in

    # Stage all modified files and commit. Ignore all untracked files.
    git commit -a -m "Release $CE3D2_VERSION_MAJOR.$CE3D2_VERSION_MINOR"

    # Build all necessary targets for publishing.
    TARGET_release
    TARGET_debug
    TARGET_docs

    # Build archives.
    mkdir -p $CE3D2_PUBLISH_DIRECTORY

    function generate-archive-name {
        echo "CE3D2-$CE3D2_VERSION_MAJOR-$CE3D2_VERSION_MINOR-x86_64-$1"
    }

    function build-archive {
        local tempdir=`mktemp --directory`
        local archive_name=`generate-archive-name $1`

        mkdir -p $tempdir/$archive_name
        cp -r "${@:2}" $tempdir/$archive_name
        tar -czvf $CE3D2_PUBLISH_DIRECTORY/$archive_name.tar.gz -C $tempdir $archive_name

        rm -rf $tempdir
    }

    build-archive release LICENSE $CE3D2_RELEASE_BUILD_DIRECTORY/libCE3D2.so
    build-archive debug LICENSE $CE3D2_DEBUG_BUILD_DIRECTORY/libCE3D2.so
    build-archive docs LICENSE $CE3D2_DOCS_BUILD_DIRECTORY/html/*

    # Increment to next dev-version. Do that on a new branch.
    if [ -z "$1" ]; then
        CE3D2_NEXT_VERSION_MAJOR="$CE3D2_VERSION_MAJOR"
        CE3D2_NEXT_VERSION_MINOR=$((CE3D2_VERSION_MINOR+1))
    else
        regex="([0-9]+)\.([0-9]+)"
        [[ $1 =~ $regex ]] && \
            CE3D2_NEXT_VERSION_MAJOR=${BASH_REMATCH[1]} && \
            CE3D2_NEXT_VERSION_MINOR=${BASH_REMATCH[2]}
    fi

    branch_name_post_release="release-$CE3D2_NEXT_VERSION_MAJOR.$CE3D2_NEXT_VERSION_MINOR.dev"
    git checkout -b $branch_name_post_release

    replace "set(CE3D2_VERSION_MAJOR [0-9]\+)" "set(CE3D2_VERSION_MAJOR $CE3D2_NEXT_VERSION_MAJOR)" CE3D2/CMakeLists.txt
    replace "set(CE3D2_VERSION_MINOR [0-9]\+)" "set(CE3D2_VERSION_MINOR $CE3D2_NEXT_VERSION_MINOR)" CE3D2/CMakeLists.txt
    replace "set(CE3D2_VERSION_MICRO 0)" "set(CE3D2_VERSION_MICRO dev)" CE3D2/CMakeLists.txt
    replace "PROJECT_NUMBER\( *\)= \"\\\${PROJECT_VERSION}\"" "PROJECT_NUMBER\1= \"\\\${PROJECT_VERSION} (at \\\${GIT_HEAD} on \\\${GIT_BRANCH})\"" CE3D2/doxyfile.in

    git commit -a -m "Increment version to $CE3D2_NEXT_VERSION_MAJOR.$CE3D2_NEXT_VERSION_MINOR.dev"

    git checkout $branch_name
    if [ "$stash_pop_needed" = "yes" ]; then
        git stash pop
    fi

    echo
    echo "Created following branches:"
    echo "- $branch_name_release"
    echo "- $branch_name_post_release"
    echo
    echo "To do a proper release now, take following steps:"
    echo "1. Create a Pull-Request for $branch_name_release on GitHub."
    echo "2. Merge the Pull-Request."
    echo "3. Create a release tag on GitHub for the master branch. Attach following files:"
    echo "   - $CE3D2_PUBLISH_DIRECTORY/$(generate-archive-name release).tar.gz"
    echo "   - $CE3D2_PUBLISH_DIRECTORY/$(generate-archive-name debug).tar.gz"
    echo "   - $CE3D2_PUBLISH_DIRECTORY/$(generate-archive-name docs).tar.gz"
    echo "4. Create a Pull-Request for $branch_name_post_release."
    echo "5. Merge the Pull-Request."
}

# Redirect to target functions.
case $1 in
    "help")
        TARGET_help;;
    "debug")
        TARGET_debug;;
    "release")
        TARGET_release;;
    "docs")
        TARGET_docs;;
    "install")
        TARGET_install $2;;
    "publish")
        TARGET_publish $2;;
    "clean")
        TARGET_clean;;
    *)
        echo "Invalid target specified."
        TARGET_help;;
esac
