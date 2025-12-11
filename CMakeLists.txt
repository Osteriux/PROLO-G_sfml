cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)
project(PROLO-G VERSION 0.2.0 LANGUAGES C CXX)

set(SFML_ROOT "C:/Program Files/SFML-2.6.2")
set(SFML_DIR ${SFML_ROOT}/lib/cmake/SFML)
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_ROOT}/include)

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Exclude folders starting with _ in Release builds (debug/dev code)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    foreach(SOURCE ${SOURCES})
        if(SOURCE MATCHES "/_[^/]+/")
            list(REMOVE_ITEM SOURCES ${SOURCE})
        endif()
    endforeach()
endif()

add_executable(prolog prolog.cpp ${SOURCES})
target_link_libraries(prolog sfml-graphics sfml-window sfml-system)

# Specify the assets directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

# Define preprocessor macro for Release builds to exclude devTools
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(RELEASE_BUILD TRUE)
    
    # Define _DEV_MODE macro for Release builds
    target_compile_definitions(prolog PRIVATE _DEV_MODE)

    message("Building in release mode")
else()
    set(RELEASE_BUILD FALSE)
    message("Building in debug mode")
endif()

# Copy assets to the build directory
add_custom_command(
    TARGET prolog POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} $<TARGET_FILE_DIR:prolog>/assets
    COMMENT "Copying assets to build directory"
)

# Copy SFML DLLs to the build directory (Windows only)
if(WIN32)
    # Find the SFML bin directory
    set(SFML_BIN_DIR "${SFML_ROOT}/bin")
    
    # Determine which DLL suffix to use based on build type
    if(RELEASE_BUILD)
        set(DLL_SUFFIX "-2.dll")
    else()
        set(DLL_SUFFIX "-d-2.dll")
    endif()
    
    # Copy SFML DLLs after build (Debug or Release versions)
    add_custom_command(
        TARGET prolog POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_BIN_DIR}/sfml-graphics${DLL_SUFFIX}"
        "${SFML_BIN_DIR}/sfml-window${DLL_SUFFIX}"
        "${SFML_BIN_DIR}/sfml-system${DLL_SUFFIX}"
        $<TARGET_FILE_DIR:prolog>
        COMMENT "Copying SFML DLLs (${CMAKE_BUILD_TYPE}) to build directory"
    )
    
    # Also copy MinGW runtime DLLs for distribution
    set(MINGW_BIN_DIR "C:/ProgramData/mingw64/mingw64/bin")
    add_custom_command(
        TARGET prolog POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
        "${MINGW_BIN_DIR}/libstdc++-6.dll"
        $<TARGET_FILE_DIR:prolog>
        COMMENT "Copying MinGW runtime DLLs to build directory"
    )
endif()