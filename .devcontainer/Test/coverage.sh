#!/bin/bash
# This line indicates the script should be run using the Bash shell.

# Run build commands
echo "#### Starting coverage process..."

rm -rf out/
rm -rf *.gcov
rm -rf *.info
gcov test.cpp -o ./build/CMakeFiles/myCode.dir/test.cpp.gcno
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out

# Notify completion
echo "#### Coverage process completed!"