/**
 * @file shape.hpp
 * @brief Defines geometric shapes including Wheel, Rectangle, Triangle, and their base class Shape.
 */

#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <math.h>
#include <fstream>
#include <vector>

#define USE_WHEEL_BASE

namespace shape{
    /**
     * @brief Represents a pair of coordinates.
     * 
     * @tparam T1 Type of the first value.
     * @tparam T2 Type of the second value.
     */
    template <typename T1, typename T2>
    struct MyPair {
        T1 x; ///< Custom name for 'first'
        T2 y; ///<  Custom name for 'second'

        /**
         * @brief Constructs a pair with default or provided values.
         * @param first Initial value for x.
         * @param second Initial value for y.
         */
        MyPair(const T1& first = 0, const T2& second = 0) : x(first), y(second) {}
    };

    /**
     * @brief Abstract base class for shapes.
     */
    class Shape
    {
        public:
            double area; ///< The area of the shape.
            double circuit; ///< The circumference of the shape.
            MyPair<MyPair<int,int>,MyPair<int,int>> border; ///< Draw border.
            MyPair<double,double> center; ///< The center coordinates of the shape.
            std::vector<MyPair<double, double>> ddata; ///< Points representing the shape geometry.
            std::string name; ///< Name of the shape.
            double rotationAngle; ///< Rotation angle of the shape.

            /**
             * @brief Calculates the distance between two points.
             * 
             * @tparam T1 Type of the x-coordinates.
             * @tparam T2 Type of the y-coordinates.
             * @param p1 The first point.
             * @param p2 The second point.
             * @return The distance between the two points.
             */
            template <typename T1, typename T2>
            double calculateDistance(const MyPair<T1, T2>& p1, const MyPair<T1, T2>& p2) {
                return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
            }

            /**
             * @brief Computes circumference of the shape.
             */
            void computeCircuit()
            {
                double circumference = 0.0;
                int n = ddata.size();
            
                for (int i = 0; i < n; ++i) {
                    int j = (i + 1) % n; // Wrap around to the first point
                    circumference += calculateDistance(ddata[i], ddata[j]);
                }
            
                circuit = circumference;
            }

            /**
             * @brief Computes the area of the shape.
             */
            void computeArea()
            {
                double a = 0.0;
                int n = ddata.size();
            
                for (int i = 0; i < n; ++i) {
                    int j = (i + 1) % n; // Wrap around to the first point
                    a += ddata[i].x * ddata[j].y - ddata[i].y * ddata[j].x;
                }
            
                area = abs(a) / 2.0; 
            }

            /**
             * @brief Constructs a Shape object.
             * @param n Name of the shape.
             * @param c Center coordinates of the shape.
             */
            Shape(const std::string n, MyPair<int,int> c) : name(n), center(c.x, c.y){}

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
             * @brief Gets the number of corners of the shape.
             * @return The number of corners.
             */
            virtual  unsigned int getCorners() const
            {
                return ddata.size() - 1;
            }

            /**
             * @brief Draws the shape using Gnuplot.
             */
            void drawMe()
            {
                createData(ddata);
                plotShape(name, border);
            }

            /**
             * @brief Generates a Gnuplot script to plot the shape.
             * 
             * @tparam U Type of the coordinates.
             * @param sN Name of the shape.
             * @param b Border coordinates.
             */
            template <typename U>
            void plotShape(std::string sN, MyPair<MyPair<U,U>,MyPair<U,U>> b)
            {
                // Create a Gnuplot script file
                std::ofstream script("shapes.gnuplot");
                script << "set terminal pngcairo size 800,800\n";
                script << "set output '"<<sN<<".png'\n";
                script << "set size ratio -1  # Equal aspect ratio\n";
                script << "set xrange ["<<b.x.x<<":"<<b.x.y<<"]\n";
                script << "set yrange ["<<b.y.x<<":"<<b.y.y<<"]\n";
                script << "set grid\n";
                script << "plot \"points.dat\" using 1:2 with linespoints  pt 7 title \""<<sN<<"\"\n"; // Dummy plot to display objects
                script.close();
            
                // Execute the Gnuplot script
                std::system("gnuplot shapes.gnuplot");
            }

            /**
             * @brief Creates a data file for plotting the shape.
             * 
             * @tparam U Type of the coordinates.
             * @param data Points to be plotted.
             */
            template <typename U>
            void createData(std::vector<MyPair<U,U>> &data)
            {
                std::ofstream file("points.dat");  // Create and open a file
                if (!file.is_open()) {
                    throw std::runtime_error("Failed to open the file.\n");
                }
                else
                {
                    for(const auto &iter : data)
                    {
                        file << iter.x << " " << iter.y  << "\n";
                    }
                }
            }

            /**
             * @brief Prints information about the shape.
             */
            void printInfo() const
            {
                std::cout <<"Name = "<<getName()<<", area = "<<getArea()<<", circiut = "<<getCircuit()<<", corners = "<<getCorners()<<std::endl;
            }

            /**
             * @brief Gets the name of the shape.
             * @return The name of the shape.
             */
            std::string getName() const
            {
                return name;
            }

            /**
             * @brief Rotates the shape by a specified angle.
             * @param degrees The rotation angle in degrees.
             */
            void rotate(double degrees) {
                rotationAngle = degrees;
        
                // Ensure rotationAngle stays within the range of 0–360 degrees
                if (rotationAngle >= 360.0) rotationAngle -= 360.0;
                if (rotationAngle < 0.0) rotationAngle += 360.0;
        
                double radians = rotationAngle * M_PI / 180.0; // Convert to radians
        
                // Rotate all points
                for (auto& point : ddata) {
                    double xNew = point.x * cos(radians) - point.y * sin(radians);
                    double yNew = point.x * sin(radians) + point.y * cos(radians);
                    point.x = xNew;
                    point.y = yNew;
                }
            }


            /* Rule of Three Point 1 */
            /**
             * @brief Destructor for the Shape class.
             */
            virtual ~Shape() {
                // Example cleanup code (if required): dynamic memory or file handles
            }
            /* Rule of Three Point 2 */
            /**
             * @brief Copy constructor for the Shape class.
             * @param other The object to copy from.
             */
            Shape(const Shape& other)
            : area(other.area), circuit(other.circuit),
            border(other.border), center(other.center),
            ddata(other.ddata), name(other.name) {}

            /* Rule of Three Point 3 */
            /**
             * @brief Copy assignment operator for the Shape class.
             * @param other The object to assign from.
             * @return The updated object.
             */
            Shape& operator=(const Shape& other) 
            {
                if (this == &other) {  // Self-assignment check
                    return *this;
                }
                // Copy all members from the source object
                area = other.area;
                circuit = other.circuit;
                border = other.border;
                center = other.center;
                ddata = other.ddata;
                name = other.name;
                return *this;
            }
    };

    /**
     * @brief Represents a circular shape (Wheel).
     * 
     * @tparam U Type of the radius.
     */
    template <typename U>
    class Wheel : public Shape
    {
        private:
            U r; ///< Radius of the wheel.
            unsigned int res; ///< Resolution (number of points).
        public:

            /**
             * @brief Gets the number of corners of the wheel.
             * @return Always returns 0 as a wheel has no corners.
             */
            unsigned int getCorners() const override
            {
                return 0;
            }

            /**
             * @brief Constructs a Wheel object.
             * @param x Radius of the wheel.
             * @param res Number of points for the resolution.
             * @param n Name of the wheel.
             */
            Wheel(U x, unsigned int res = 30, const std::string n = "Wheel") : res(res), r(x), Shape(n, {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - (ceil(1.5 * r));
                border.x.y = center.y + (ceil(1.5 * r));
                border.y = border.x;
                double offset = 0;
                //initial point offset to make sure base of shape is  parallel to x axis
                (res % 2) == 0 ? offset = (M_PI / (res)) : offset = (M_PI / 2) ; 
                MyPair<double, double> tail;;
                for (int i = 0; i < res; ++i) {
                    double angle = ((2 * M_PI * i) / res) + offset;  // Angle in radians
                    MyPair<double, double> p;
                    p.x = r * cos(angle) + center.x;
                    p.y = r * sin(angle) + center.y;
                    ddata.push_back(p);
                    i ? 0 : tail = p;
                }
                ddata.push_back(tail);
                computeCircuit();
                computeArea();
            }
            /**
             * @brief Destructor for the Wheel class.
             */
            ~Wheel() override {}

            /**
             * @brief Copy constructor for the Wheel class.
             * @param other The object to copy from.
             */
            Wheel(const Wheel<U>& other) 
                : shape::Shape(other), r(other.r) {}

            /**
             * @brief Copy assignment operator for the Wheel class.
             * @param other The object to assign from.
             * @return The updated object.
             */
            Wheel<U>& operator=(const Wheel<U>& other) 
            {
                if (this == &other) {
                    return *this; // Self-assignment check
                }
                shape::Shape::operator=(other); // Base class copy
                r = other.r;
                return *this;
            }
            
    };

    /**
     * @brief Represents a rectangle.
     * 
     * @tparam U Type of the side length.
     */
    template <typename U>
    class Rectangle : public Shape
    {
        private:
            U a; ///< Side length of the rectangle.
        public:
            /**
             * @brief Constructs a Rectangle object.
             * @param x Side length of the rectangle.
             * @param n Name of the rectangle.
             */
            Rectangle(U x, const std::string n = "Rectangle") : a(x),  Shape(n, {0,0})
            {
#ifdef USE_WHEEL_BASE
                double r = (a/2) * sqrt(2);
                shape::Wheel<U> poly(r,4);
                //workaround
                ddata = poly.ddata; // Copy Wheel's data to Rectangle's data
                border = poly.border; // Optionally copy other information
                center = poly.center;
#else
                //assumption we are starting draw at center
                border.x.x = center.x - a;
                border.x.y = center.y + a;
                border.y = border.x;
                MyPair<double, double> c1, c2, c3, c4;
                c1.x = center.x - static_cast<double>(a)/2;
                c1.y = center.y - static_cast<double>(a)/2;
                c2.x = c1.x + a;
                c2.y = c1.y;
                c3.x =  c2.x;
                c3.y = c2.y + a;
                c4.x = c1.x;
                c4.y = c1.y + a;
                ddata.push_back(c1);
                ddata.push_back(c2);
                ddata.push_back(c3);
                ddata.push_back(c4);
                ddata.push_back(c1);
#endif             
                computeCircuit();
                computeArea();

            }
            //rules
            /**
             * @brief Destructor for the Rectangle class.
             */
            ~Rectangle() override {}

            /**
             * @brief Copy constructor for the Rectangle class.
             * @param other The object to copy from.
             */
            Rectangle(const Rectangle<U>& other)
                : shape::Shape(other), a(other.a) {}

            /**
             * @brief Copy assignment operator for the Rectangle class.
             * @param other The object to assign from.
             * @return The updated object.
             */
            Rectangle<U>& operator=(const Rectangle<U>& other) 
            {
                if (this == &other) return *this; // Self-assignment check
                shape::Shape::operator=(other);  // Call base class copy assignment
                a = other.a;
                return *this;
            }
    };

    /**
     * @brief Represents an equilateral triangle.
     * 
     * @tparam U Type of the side length.
     */
    template <typename U>
    class Triangle : public Shape
    {
        private:
            U a; ///< Side length of the triangle.
        public:

            /**
             * @brief Constructs a Triangle object.
             * @param x Side length of the triangle.
             * @param n Name of the triangle.
             */
            Triangle(U x, const std::string n = "Triangle") : a(x),   Shape(n, {0,0})
            {
#ifdef USE_WHEEL_BASE
                //calculate h based on a 
                double h = (((sqrt(3)/2) * a) * 2 ) / 3; 
                //calculate r based on a and h
                double r = sqrt(pow(a/2,2) + pow(h/2,2));
                shape::Wheel<U> poly(r,3);
                //workaround
                ddata = poly.ddata; // Copy Wheel's data to Rectangle's data
                border = poly.border; // Optionally copy other information
                center = poly.center;
                computeCircuit(); //update data
                computeArea();
#else
                //assumption we are starting draw at center
                U h = (sqrt(3)/2) * a;
                border.x.x = center.x - a;
                border.x.y = center.x + a;
                border.y.x = center.y - h;
                border.y.y = center.y + 2*h;
                MyPair <double, double> c1, c2, c3;
                c1.x = center.x - static_cast<double>(a)/2;
                c1.y = center.y;
                c2.x = c1.x + a;
                c2.y = c1.y;
                c3.x = c1.x + static_cast<double>(a)/2;
                c3.y = c1.y + h;
                ddata.push_back(c1);
                ddata.push_back(c2);
                ddata.push_back(c3);
                ddata.push_back(c1);
#endif
                computeCircuit();
                computeArea();
            }
            //rules
            /**
             * @brief Destructor for the Triangle class.
             */
            ~Triangle() override {}

            /**
             * @brief Copy constructor for the Triangle class.
             * @param other The object to copy from.
             */
            Triangle(const Triangle<U>& other)
                : shape::Shape(other), a(other.a) {}

            /**
             * @brief Copy assignment operator for the Triangle class.
             * @param other The object to assign from.
             * @return The updated object.
             */
            Triangle<U>& operator=(const Triangle<U>& other) 
            {
                if (this == &other) return *this; // Self-assignment check
                shape::Shape::operator=(other);  // Call base class copy assignment
                a = other.a;
                return *this;
            } 
    };
}

#endif