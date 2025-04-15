/**
 * @file shape.hpp
 * @brief Defines geometric shapes including Wheel, Rectangle, Triangle, and their base class Shape.
 */

#ifndef SHAPE_CRTP_H
#define SHAPE_CRTP_H
#include <string>
#include <math.h>
#include <fstream>
#include <vector>

namespace shapeCrtp{

    /**
     * @brief Abstract base class for shapes.
     */
    template <typename Derived>
    class Shape
    {
        public:
            double area; ///< The area of the shape.
            double circuit; ///< The circumference of the shape.
            std::string name; ///< Name of the shape.

            void computeCircuit() {
                static_cast<Derived*>(this)->computeCircuitImpl();
            }
        
            void computeArea() {
                static_cast<Derived*>(this)->computeAreaImpl();
            }
        
            unsigned int getCorners() const {
                return static_cast<const Derived*>(this)->getCornersImpl();
            }

            /**
             * @brief Constructs a Shape object.
             * @param n Name of the shape.
             * @param c Center coordinates of the shape.
             */
            Shape(const std::string n) : name(n) {}

            /**
             * @brief Gets the area of the shape.
             * @return The computed area.
             */
            double getArea() const
            {
                return area;
            }

            /**
             * @brief Gets the circumference of the shape.
             * @return The computed perimeter.
             */
            double getCircuit() const
            {
                return circuit;
            }


            /**
             * @brief Prints information about the shape.
             */
            void printInfo() const
            {
                std::cout <<"Name = "<<name 
                          <<", area = "<<area 
                          <<", circiut = "<<circuit 
                          <<", corners = "<<getCorners()<<std::endl;
            }

            /**
             * @brief Gets the name of the shape.
             * @return The name of the shape.
             */
            std::string getName() const
            {
                return name;
            }
    };

    /**
     * @brief Represents a circular shape (Wheel).
     * 
     * @tparam U Type of the radius.
     */
    template <typename U>
    class Wheel : public Shape<Wheel<U>>
    {
        private:
            U r; ///< Radius of the wheel.
        public:

            /**
             * @brief Constructs a Wheel object.
             * @param x Radius of the wheel.
             * @param n Name of the wheel.
             */
            Wheel(U x, const std::string n = "Wheel") :  r(x), Shape<Wheel<U>>(n)
            {
                this->name = n;
                this->computeCircuit();
                this->computeArea();
            }    

            void computeCircuitImpl() 
            {
                this->circuit = 2 * M_PI * r; 
            }
        
            void computeAreaImpl() 
            {
                this->area = M_PI * r * r;
            }
        
            unsigned int getCornersImpl() const
            {
                return 0;
            }
    };

    /**
     * @brief Represents a rectangle.
     * 
     * @tparam U Type of the side length.
     */
    template <typename U>
    class Rectangle : public Shape<Rectangle<U>>
    {
        private:
            U a; ///< Side length of the rectangle.
        public:
            /**
             * @brief Constructs a Rectangle object.
             * @param x Side length of the rectangle.
             * @param n Name of the rectangle.
             */
            Rectangle(U x, const std::string n = "Rectangle") : a(x), Shape<Rectangle<U>>(n)
            {
                this->name = n;
                this->computeCircuit();
                this->computeArea();   
            }

            void computeCircuitImpl() 
            {
                this->circuit = 4 * a;
            }
        
            void computeAreaImpl() 
            {
                this->area = a * a;
            }
        
            unsigned int getCornersImpl() const
            {
                return 4;
            }     
    };

    /**
     * @brief Represents an equilateral triangle.
     * 
     * @tparam U Type of the side length.
     */
    template <typename U>
    class Triangle : public Shape<Triangle<U>>
    {
        private:
            U a, h; ///< Side length of the triangle.
        public:

            /**
             * @brief Constructs a Triangle object.
             * @param x Side length of the triangle.
             * @param n Name of the triangle.
             */
            Triangle(U x, const std::string n = "Triangle") : a(x), Shape<Triangle<U>>(n)
            {
                this->name = n;
                this->h = (sqrt(3)/2) * a;
                this->computeCircuit();
                this->computeArea(); 
            }  
            
            void computeCircuitImpl() 
            {
                this->circuit = 3 * a;
            }
        
            void computeAreaImpl() 
            {
                this->area =  0.5 * a * h;
            }
        
            unsigned int getCornersImpl() const
            {
                return 3;
            }
    };
}

#endif