cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)
project(PROLO-G VERSION 0.1.0 LANGUAGES C CXX)

set(SFML_ROOT "C:/Program Files/SFML-2.6.2")
set(SFML_DIR ${SFML_ROOT}/lib/cmake/SFML)
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_ROOT}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(prolog prolog.cpp ${SOURCES})
target_link_libraries(prolog sfml-graphics sfml-window sfml-system)

# Specify the assets directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

# Copy assets to the build directory
add_custom_command(
    TARGET prolog POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} $<TARGET_FILE_DIR:prolog>/assets
)