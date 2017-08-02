#!/usr/bin/env bash
set -e

# Customization variables.
CE3D2_SOURCE_DIRECTORY=CE3D2
CE3D2_BUILD_DIRECTORY=build
CE3D2_DOCS_BUILD_DIRECTORY=$CE3D2_BUILD_DIRECTORY/docs
CE3D2_DEBUG_BUILD_DIRECTORY=$CE3D2_BUILD_DIRECTORY/debug
CE3D2_RELEASE_BUILD_DIRECTORY=$CE3D2_BUILD_DIRECTORY/release

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
    echo "pack       Packs builds into archives. Supported arguments are "
    echo "           'debug' (for putting the debug build together with the "
    echo "           source into a tar.gz), 'release' (the same with release), "
    echo "           'docs' (for the documentation), 'source' (for the source "
    echo "           files only) and 'all' (pack every available target)."
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

function TARGET_pack {
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

    GIT_TRACKED_FILES=`git ls-tree -r HEAD --name-only | tr '\n' ' '`

    if [ "$1" == "debug" ]; then
        PACKFILES="$GIT_TRACKED_FILES $CE3D2_DEBUG_BUILD_DIRECTORY"
        PLATFORM="x86_64"
    elif [ "$1" == "release" ]; then
        PACKFILES="$GIT_TRACKED_FILES $CE3D2_RELEASE_BUILD_DIRECTORY"
        PLATFORM="x86_64"
    elif [ "$1" == "docs" ]; then
        PACKFILES="--directory=$CE3D2_DOCS_BUILD_DIRECTORY html/"
        PLATFORM=""
    elif [ "$1" == "source" ]; then
        PACKFILES="$GIT_TRACKED_FILES"
        PLATFORM=""
    else
        echo "Invalid parameter for pack target, use 'debug', 'release', "
        echo "'docs', 'source' or 'all'."
        return
    fi

    if [ -n "$PLATFORM" ]; then
        PLATFORM="-$PLATFORM"
    fi

    ARCHIVE_NAME="CE3D2-$CE3D2_VERSION_MAJOR$CE3D2_VERSION_MINOR"
    ARCHIVE_NAME+="$CE3D2_VERSION_MICRO$PLATFORM-$1.tgz"

    tar -cvzf $ARCHIVE_NAME $PACKFILES
    mv $ARCHIVE_NAME $CE3D2_BUILD_DIRECTORY/$ARCHIVE_NAME
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
    "pack")
        if [ "$2" == "all" ]; then
            TARGET_pack "debug"
            TARGET_pack "release"
            TARGET_pack "docs"
            TARGET_pack "source"
        else
            TARGET_pack $2
        fi
        ;;
    "clean")
        TARGET_clean;;
    *)
        echo "Invalid target specified."
        TARGET_help;;
esac
