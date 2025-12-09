#!/bin/bash
# PROLO-G Release Packaging Script
# This script builds a release version and packages it for distribution

set -e  # Exit on error

echo "=========================================="
echo "PROLO-G Release Packaging"
echo "=========================================="
echo ""

# Get version from CMakeLists.txt
VERSION=$(grep "project(PROLO-G VERSION" CMakeLists.txt | sed 's/.*VERSION \([0-9.]*\).*/\1/')
RELEASE_NAME="PROLO-G-v${VERSION}-Windows"
RELEASE_DIR="releases/${RELEASE_NAME}"

echo "Version: ${VERSION}"
echo "Release directory: ${RELEASE_DIR}"
echo ""

# Step 1: Configure Release build
echo "[1/4] Configuring Release build..."
cmake --preset prolo-g_release

# Step 2: Build Release
echo ""
echo "[2/4] Building Release..."
cmake --build out/build/prolo-g_release --config Release

# Step 3: Create release directory structure
echo ""
echo "[3/4] Creating release package..."
rm -rf "${RELEASE_DIR}"
mkdir -p "${RELEASE_DIR}"

# Copy executable
cp out/build/prolo-g_release/prolog.exe "${RELEASE_DIR}/"

# Copy assets
cp -r out/build/prolo-g_release/assets "${RELEASE_DIR}/"

# Copy DLLs (should already be in build directory from CMake)
cp out/build/prolo-g_release/sfml-graphics-2.dll "${RELEASE_DIR}/" 2>/dev/null || echo "Warning: sfml-graphics-2.dll not found"
cp out/build/prolo-g_release/sfml-window-2.dll "${RELEASE_DIR}/" 2>/dev/null || echo "Warning: sfml-window-2.dll not found"
cp out/build/prolo-g_release/sfml-system-2.dll "${RELEASE_DIR}/" 2>/dev/null || echo "Warning: sfml-system-2.dll not found"
cp out/build/prolo-g_release/libgcc_s_seh-1.dll "${RELEASE_DIR}/" 2>/dev/null || echo "Warning: libgcc_s_seh-1.dll not found"
cp out/build/prolo-g_release/libstdc++-6.dll "${RELEASE_DIR}/" 2>/dev/null || echo "Warning: libstdc++-6.dll not found"

# Create README for release
cat > "${RELEASE_DIR}/README.txt" << EOF
PROLO-G v${VERSION}
===================

A dungeon exploration game built with C++ and SFML.

HOW TO RUN:
-----------
1. Extract all files to a folder
2. Run prolog.exe

SYSTEM REQUIREMENTS:
--------------------
- Windows 7 or later
- 64-bit system

CONTENTS:
---------
- prolog.exe: Main executable
- assets/: Game assets (textures, fonts, levels)
- *.dll: Required runtime libraries

For more information, visit: https://github.com/Osteriux/PROLO-G_sfml

Enjoy the game!
EOF

# Copy license if it exists
if [ -f "LICENSE" ]; then
    cp LICENSE "${RELEASE_DIR}/"
fi

# Step 4: Create zip archive
echo ""
echo "[4/4] Creating zip archive..."
cd releases
tar acvf "${RELEASE_NAME}.zip" "${RELEASE_NAME}" > /dev/null
cd ..

echo ""
echo "=========================================="
echo "Release package created successfully!"
echo "=========================================="
echo ""
echo "Location: ${RELEASE_DIR}"
echo "Archive: releases/${RELEASE_NAME}.zip"
echo ""
echo "Package contents:"
ls -lh "${RELEASE_DIR}"
echo ""
echo "Archive size:"
ls -lh "releases/${RELEASE_NAME}.zip"
echo ""
