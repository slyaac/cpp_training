#!/bin/bash
# This line indicates the script should be run using the Bash shell.

# Run build commands
echo "#### Starting coverage process..."

rm -rf cov/
mkdir cov
cd cov
gcov ../test.cpp -o ../build/CMakeFiles/myCode.dir/test.cpp.gcno
lcov --capture --directory ../ --output-file coverage.info
genhtml coverage.info --output-directory out
cd ..
# Notify completion
echo "#### Coverage process completed!"