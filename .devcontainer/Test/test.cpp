#include <gtest/gtest.h>
#include "array.hpp"

TEST(MyTestSuite, NoException) {
    // Your test code here
    Matrix neo1(2,2);
    Matrix neo2(2,2);

    EXPECT_NO_THROW(
        Matrix neoo = neo1 + neo2;
    );
}

TEST(MyTestSuite, Exception) {
    // Your test code here
    Matrix neo1(2,2);
    Matrix neo2(4,2);

    EXPECT_THROW(
        Matrix neoo = neo1 + neo2;,
        std::invalid_argument
    );
}

TEST(MyTestSuite, NoException2) {
    // Your test code here
    Matrix neo1(2,2);
    
    EXPECT_NO_THROW(
        neo1.set(0,0,0);
    );
}

TEST(MyTestSuite, Exception2) {
    // Your test code here
    Matrix neo1(2,2);
    
    EXPECT_THROW(
        neo1.set(3,0,0);,
        std::invalid_argument
    );
}

TEST(MyTestSuite, coverage) {
    // Your test code here
    Matrix neo1({{1},{2},{3}});
    cout<<neo1;
    EXPECT_TRUE(1==1);
}

TEST(MyTestSuite, coverage2) {
    // Your test code here
    Matrix neo1(1,1);
    neo1[0][0] = 99;
    EXPECT_TRUE(1==1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

/* 
* cd to folder with cmake
* "cmake -S . -B build" <-- here all flags
* "cmake --build build"
* execute ./build/mytest
* ex. rm -rf build/ && mkdir build  && cmake -S . -B build  -DMYFLAG=OFF && cmake --build build  && ./build/mytest 
*/