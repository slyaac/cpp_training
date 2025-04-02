#!/bin/bash
# This line indicates the script should be run using the Bash shell.

# Run build commands
echo "#### Starting build process..."

rm -rf build/ 
mkdir build  
cmake -S . -B build  -DMYFLAG=ON
cmake --build build 
./build/myCode

# Notify completion
echo "#### Build process completed!"