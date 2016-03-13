#!/bin/bash
set -e

# Customization variables.
CE3D2_SOURCE_DIRECTORY=CE3D2
CE3D2_DOC_BUILD_DIRECTORY=build/doc
CE3D2_DEBUG_BUILD_DIRECTORY=build/debug
CE3D2_RELEASE_BUILD_DIRECTORY=build/release


working_dir=$(pwd)
CE3D2_SOURCE_DIRECTORY="$working_dir/$CE3D2_SOURCE_DIRECTORY"
CE3D2_DEBUG_BUILD_DIRECTORY="$working_dir/$CE3D2_DEBUG_BUILD_DIRECTORY"
CE3D2_RELEASE_BUILD_DIRECTORY="$working_dir/$CE3D2_RELEASE_BUILD_DIRECTORY"

CMAKE_FLAGS=""
CMAKE_DEBUG_FLAGS="-DCMAKE_BUILD_TYPE=Debug -DTESTS_ENABLED=ON"
CMAKE_RELEASE_FLAGS="-DCMAKE_BUILD_TYPE=Release"
CMAKE_DOC_FLAGS="-DCMAKE_BUILD_TYPE=Documentation"

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
    cd $1
    cmake $CE3D2_SOURCE_DIRECTORY $CMAKE_FLAGS $2
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
    echo "doc        Builds the HTML documentation into" \
                     "'$CE3D2_DOC_BUILD_DIRECTORY/html'."
    echo "install debug|release"
    echo "           Installs CE3D2 onto your system."
    echo "clean      Clean up build files."
}

function TARGET_debug {
    build $CE3D2_DEBUG_BUILD_DIRECTORY "$CMAKE_DEBUG_FLAGS"
}

function TARGET_release {
    build $CE3D2_RELEASE_BUILD_DIRECTORY "$CMAKE_RELEASE_FLAGS"
}

function TARGET_doc {
    build $CE3D2_DOC_BUILD_DIRECTORY "$CMAKE_DOC_FLAGS" doc
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
        rm -rf $CE3D2_DOC_BUILD_DIRECTORY
}


# Redirect to target functions.
case $1 in
    "help")
        TARGET_help;;
    "debug")
        TARGET_debug;;
    "release")
        TARGET_release;;
    "doc")
        TARGET_doc;;
    "install")
        TARGET_install $2;;
    "clean")
        TARGET_clean;;
    *)
        echo "Invalid target specified."
        TARGET_help;;
esac
