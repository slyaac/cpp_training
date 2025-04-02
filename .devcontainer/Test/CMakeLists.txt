cmake_minimum_required(VERSION 3.18)
project(gtest)

#switch to define if ewe will rin GTEST or no
option(MYFLAG "Enable Google Test" ON)

# Include Google Test
enable_testing()

# Find GTest (if installed system-wide)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(MYFLAG STREQUAL  "ON")
#    message(STATUS "MYFLAG is : ${MYFLAG}")
    # Specify the executable
    add_executable(myCode array.cpp test.cpp)
    # must be after exec definition
    #target_compile_definitions(myCode PRIVATE ENABLE_GTEST)
endif()

if(MYFLAG STREQUAL  "OFF")
#    message(STATUS "MYFLAG is : ${MYFLAG}")
    add_executable(myCode array.cpp main.cpp)
endif()

# Link GTest libraries
target_link_libraries(myCode ${GTEST_LIBRARIES} pthread)

# Add test cases
add_test(NAME myCode COMMAND myCode)