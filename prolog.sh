#!/bin/bash
# PR0L0-G Commands script
# Commands :
#     help    : display this help
#     clean   : clean build files
#     build   : build the dev build
#     run     : run the dev build
#     package : build and package the release version
#     release : run the release build
#     doxy    : generate documentation with Doxygen

set -e  # Exit on error
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

function display_help() {
    echo "PR0L0-G Commands Script"
    echo ""
    echo "Usage: $0 [command]"
    echo ""
    echo "Commands:"
    echo "  help       Display this help message"
    echo "  clean      Clean build files"
    echo "  build      Build the development version"
    echo "  run        Run the development version"
    echo "  package    Build and package the release version"
    echo "  release    Run the release version"
    echo ""
}

function clean_build() {
    rm -rf out/build/prolo-g_preset
    echo "Build files cleaned."
}

function build_dev() {
    echo -e "Running CMake configuration for development build...\n"
    cmake --preset prolo-g_preset
    echo -e "\n\nRunning build for development version...\n"
    cmake --build out/build/prolo-g_preset --config Debug
    echo -e "\n\nDevelopment build completed."
}

function run_dev() {
    ./out/build/prolo-g_preset/prolog.exe
}

function package_release() {
    bash "${SCRIPT_DIR}/package_release.sh"
}

function run_release() {
    ./out/build/prolo-g_release/prolog.exe
}

function generate_doxygen() {
    if ! command -v doxygen &> /dev/null; then
        echo "Doxygen could not be found. Please install Doxygen to generate documentation."
        exit 1
    fi

    if [ ! -f "${SCRIPT_DIR}/Doxyfile" ]; then
        echo "Doxyfile not found in script directory."
        exit 1
    fi

    doxygen "${SCRIPT_DIR}/Doxyfile"
    echo "Documentation generated in the 'docs' directory."
}

if [ $# -eq 0 ]; then
    display_help
    exit 0
fi

case $1 in
    help)
        display_help
        ;;
    clean)
        clean_build
        ;;
    build)
        build_dev
        ;;
    run)
        run_dev
        ;;
    package)
        package_release
        ;;
    release)
        run_release
        ;;
    doxy)
        generate_doxygen
        ;;
    *)
        echo "Unknown command: $1"
        display_help
        exit 1
        ;;
esac