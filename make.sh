#!/bin/bash

# Customization variables.
CE3D2_SOURCE_DIRECTORY=CE3D2
CE3D2_DEBUG_BUILD_DIRECTORY=build/debug
CE3D2_RELEASE_BUILD_DIRECTORY=build/release


working_dir=$(pwd)
CE3D2_SOURCE_DIRECTORY="$working_dir/$CE3D2_SOURCE_DIRECTORY"
CE3D2_DEBUG_BUILD_DIRECTORY="$working_dir/$CE3D2_DEBUG_BUILD_DIRECTORY"
CE3D2_RELEASE_BUILD_DIRECTORY="$working_dir/$CE3D2_RELEASE_BUILD_DIRECTORY"

CMAKE_FLAGS=""
CMAKE_DEBUG_FLAGS="-DCMAKE_BUILD_TYPE=Debug -DTESTS_ENABLED=ON"
CMAKE_RELEASE_FLAGS="-DCMAKE_BUILD_TYPE=Release"

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


function TARGET_help {
    echo "Following targets are available:"
    echo
    echo "help       Displays this help."
    echo
    echo "debug      Build CE3D2 (debug) into $CE3D2_DEBUG_BUILD_DIRECTORY."
    echo "release    Build CE3D2 (release) into $CE3D2_RELEASE_BUILD_DIRECTORY."
    echo "clean      Clean up build files."
}

function TARGET_debug {
    create_build_directory $CE3D2_DEBUG_BUILD_DIRECTORY
    cd $CE3D2_DEBUG_BUILD_DIRECTORY
    cmake $CE3D2_SOURCE_DIRECTORY $CMAKE_FLAGS $CMAKE_DEBUG_FLAGS
    make
    cd $working_dir
}

function TARGET_release {
    create_build_directory $CE3D2_RELEASE_BUILD_DIRECTORY
    cd $CE3D2_RELEASE_BUILD_DIRECTORY
    cmake $CE3D2_SOURCE_DIRECTORY $CMAKE_FLAGS $CMAKE_RELEASE_FLAGS
    make
    cd $working_dir
}

function TARGET_clean {
    task "Deleting debug build..." \
        rm -rf $CE3D2_DEBUG_BUILD_DIRECTORY
    task "Deleting release build..." \
        rm -rf $CE3D2_RELEASE_BUILD_DIRECTORY
}


# Redirect to target functions.
case $1 in
    "help")
        TARGET_help;;
    "debug")
	TARGET_debug;;
    "release")
        TARGET_release;;
    "clean")
        TARGET_clean;;
    *)
        echo "Invalid target specified."
        TARGET_help;;
esac
