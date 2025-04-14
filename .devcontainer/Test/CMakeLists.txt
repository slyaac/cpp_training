cmake_minimum_required(VERSION 3.18)
project(CPP_TRAINING)

set(CMAKE_CXX_STANDARD 17) # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Ensure the C++17 standard is used

#switch to define if ewe will rin GTEST or no
option(MYFLAG "Enable Google Test" ON)


if(MYFLAG STREQUAL  "ON")
    # Find GTest (if installed system-wide)
    include_directories(${GTEST_INCLUDE_DIRS})
    find_package(GTest REQUIRED)
    # Include Google Test
    enable_testing()
#    message(STATUS "MYFLAG is : ${MYFLAG}")
    # Specify the executable
    add_executable(myCode test.cpp)
    target_compile_options(myCode PUBLIC -fprofile-arcs -ftest-coverage -fconstexpr-ops-limit=536870912)
    target_link_options(myCode PUBLIC -fprofile-arcs -ftest-coverage)
    # Link GTest libraries
    target_link_libraries(myCode ${GTEST_LIBRARIES} pthread -lgcov)
    # Add test cases
    add_test(NAME myCode COMMAND myCode)
endif()

if(MYFLAG STREQUAL  "OFF")
#    message(STATUS "MYFLAG is : ${MYFLAG}")
    add_executable(myCode main.cpp)
    target_link_libraries(myCode ${GTEST_LIBRARIES} pthread)
endif()



set(CMAKE_BUILD_TYPE Debug)
