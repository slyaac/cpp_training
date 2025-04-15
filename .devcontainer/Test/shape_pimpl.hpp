#ifndef SHAPE_PIMPL_H
#define SHAPE_PIMPL_H
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
#include <memory>


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
            virtual unsigned int getCorners() const;
            void drawMe();
            virtual void printInfo() const;
            void rotate(double degrees);

        protected:
            std::unique_ptr<ShapeImpl> pImpl;
    };

    template <typename U>
    class RectangleImpl;
    
    template <typename U>
    class Rectangle : public Shape {
    public:
        explicit Rectangle(U sideLength, const std::string& name);
        ~Rectangle();

    private:
        std::unique_ptr<RectangleImpl<U>> pImpl; // Pimpl for Rectangle
    };

    template <typename U>
    class TriangleImpl;
    
    template <typename U>
    class Triangle : public Shape {
    public:
        explicit Triangle(U sideLength, const std::string& name);
        ~Triangle();

    private:
        std::unique_ptr<TriangleImpl<U>> pImpl; // Pimpl for Triangle
    };

    template <typename U>
    class WheelImpl;
    
    template <typename U>
    class Wheel : public Shape {
    public:
        explicit Wheel(U sideLength, const std::string& name);
        ~Wheel();
        unsigned int getCorners() const override; // Declaration
        void printInfo() const override;

    private:
        std::unique_ptr<WheelImpl<U>> pImpl; // Pimpl for Wheel
    };

}

#endif