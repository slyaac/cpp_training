/**
 * @file test.cpp
 * @brief Execute test cases
 */


#include <gtest/gtest.h>

#include "shape.hpp"
#include <vector>
#include <iomanip>

#if 0
#include "array_vector.hpp"

TEST(MyTestSuite, NoException) {
    // Your test code here
    Matrix<int> neo1(2,2,0);
    Matrix<int> neo2(2,2,0);

    EXPECT_NO_THROW(
        Matrix<int> neoo = neo1 + neo2;
    );
}

TEST(MyTestSuite, Exception) {
    // Your test code here
    Matrix<int> neo1(2,2,0);
    Matrix<int> neo2(4,2,0);

    EXPECT_THROW(
        Matrix<int> neoo = neo1 + neo2;,
        std::invalid_argument
    );
}

TEST(MyTestSuite, NoException2) {
    // Your test code here
    Matrix<int> neo1(2,2,0);
    
    EXPECT_NO_THROW(
        neo1.set(0,0,0);
    );
}

TEST(MyTestSuite, Exception2) {
    // Your test code here
    Matrix<int> neo1(2,2,0);
    
    EXPECT_THROW(
        neo1.set(3,0,0);,
        std::invalid_argument
    );
}

TEST(MyTestSuite, coverage) {
    // Your test code here
    Matrix<int> neo1({1},{2},{3});
    cout<<neo1;
    EXPECT_TRUE(1==1);
}

TEST(MyTestSuite, coverage2) {
    // Your test code here
    Matrix<int> neo1(1,1,0);
    int z = neo1(0,0);
    EXPECT_TRUE(1==1);
}
#endif

#if 1
// Test case for the Wheel class
TEST(ShapeTest, WheelCorners) {
    shape::Wheel<double> wheel(5.0);
    EXPECT_EQ(wheel.getCorners(), 0); // A wheel has 0 corners
}

// Test case for the Rectangle class
TEST(ShapeTest, RectangleCorners) {
    shape::Rectangle<int> rect(10);
    EXPECT_EQ(rect.getCorners(), 4); // A rectangle has 4 corners
}

// Test case for the Triangle class
TEST(ShapeTest, TriangleCorners) {
    shape::Triangle<int> tri(10);
    EXPECT_EQ(tri.getCorners(), 3); // A triangle has 3 corners
}

// Test polymorphic behavior with a vector of Shape pointers
TEST(ShapeTest, Polymorphism) {
    std::vector<std::unique_ptr<shape::Shape>> shapes;
    shapes.push_back(std::make_unique<shape::Wheel<double>>(5.0));
    shapes.push_back(std::make_unique<shape::Rectangle<int>>(10));
    shapes.push_back(std::make_unique<shape::Triangle<int>>(10));

    std::vector<int> expectedCorners = {0, 4, 3};
    for (size_t i = 0; i < shapes.size(); ++i) {
        EXPECT_EQ(shapes[i]->getCorners(), expectedCorners[i]);
    }
}

// Test virtual functions like drawMe and printInfo
TEST(ShapeTest, VirtualFunctions) {
    shape::Rectangle<int> rect(10);
    rect.drawMe();    // Ensure it doesn't crash (visual output may not be testable)
    rect.printInfo(); // Same as above

    SUCCEED(); // If no crash, the test succeeds
}

// Test constructor and resource cleanup
TEST(ShapeTest, ConstructorDestructor) {
    auto wheel = std::make_unique<shape::Wheel<double>>(10.5);
    EXPECT_NO_THROW(wheel.reset()); // Destructor should not throw exceptions
}
#endif

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