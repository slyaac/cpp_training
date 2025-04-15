#ifndef SHAPE_PIMPL_H
#define SHAPE_PIMPL_H
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
#include <memory>

#define USE_WHEEL_BASE

namespace shape_pimpl{
 
    // Forward declaration of the implementation class
    class ShapeImpl;

    class Shape
    {
        public:
            Shape(const std::string& name);
            ~Shape();
      
            void computeCircuit();
            void computeArea();
            double getArea() const;
            double getCircuit() const;
            unsigned int getCorners() const;
            void drawMe();
            void printInfo() const;
            void rotate(double degrees);

        private:
            std::unique_ptr<ShapeImpl> pImpl;
    };

    class RectangleImpl;
    
    template <typename U>
    class Rectangle : public Shape
    {
        private:
            U a; ///< Side length of the rectangle.
        public:

            Rectangle(U x, const std::string n = "Rectangle") : a(x),  Shape(n, {0,0}){}
            ~Rectangle();

            unsigned int getCorners() const override;

        private:
            std::unique_ptr<RectangleImpl> pImpl; // Pointer to the private implementation
    };
}

#endif