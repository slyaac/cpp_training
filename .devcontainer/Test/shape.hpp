#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <math.h>
#include <fstream>
#include <vector>

namespace shape{

    template <typename T1, typename T2>
    struct MyPair {
        T1 x; // Custom name for 'first'
        T2 y; // Custom name for 'second'

        MyPair(const T1& first = 0, const T2& second = 0) : x(first), y(second) {}
    };
    
    class Shape
    {
        public:
            double area;
            double circuit;
            MyPair<MyPair<int,int>,MyPair<int,int>> border;
            MyPair<double,double> center;
            std::vector<MyPair<double, double>> ddata;
            std::string name;
            double rotationAngle;

            template <typename T1, typename T2>
            double calculateDistance(const MyPair<T1, T2>& p1, const MyPair<T1, T2>& p2) {
                return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
            }
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

            Shape(const std::string n, MyPair<int,int> c) : name(n), center(c.x, c.y){}

            double getArea()
            {
                return area;
            }

            double getCircuit()
            {
                return circuit;
            }

            virtual  unsigned int getCorners()
            {
                return ddata.size() - 1;
            }

            void drawMe()
            {
                createData(ddata);
                plotShape(name, border);
            }
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

            void printInfo()
            {
                std::cout <<"Name = "<<getName()<<", area = "<<getArea()<<", circiut = "<<getCircuit()<<", corners = "<<getCorners()<<std::endl;
            }

            std::string getName()
            {
                return name;
            }


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


            // Destructor - Rule of Three Point 1
            // Responsible for releasing resources when the object is destroyed.
            virtual ~Shape() {
                // Example cleanup code (if required): dynamic memory or file handles
            }
            // Copy Constructor - Rule of Three Point 2
            // Creates a new object as a copy of an existing object.
            Shape(const Shape& other)
            : area(other.area), circuit(other.circuit),
            border(other.border), center(other.center),
            ddata(other.ddata), name(other.name) {}

            // Copy Assignment Operator - Rule of Three Point 3
            // Handles assignment between objects, ensuring proper cleanup and copying.
            
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

    template <typename U>
    class Wheel : public Shape
    {
        private:
            U r;
            unsigned int res;
        public:

            unsigned int getCorners()
            {
                return 0;
            }

            Wheel(U x, unsigned int res = 30, const std::string n = "Wheel") : res(res), r(x), Shape(n, {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - (ceil(1.5 * r));
                border.x.y = center.y + (ceil(1.5 * r));
                border.y = border.x;
                double offset = 0;// M_PI / 4; //90 // initial draw of firtst point is always (r,0)
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
            /* rules */
            // Destructor (Inherited and Virtual)
            ~Wheel() override {}

            // Copy Constructor
            Wheel(const Wheel<U>& other) 
                : shape::Shape(other), r(other.r) {}

            // Copy Assignment Operator
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
    template <typename U>
    class Rectangle : public Shape
    {
        private:
            U a;
        public:

            Rectangle(U x, const std::string n = "Rectangle") : a(x),  Shape(n, {0,0})
            {
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
                
                computeCircuit();
                computeArea();
            }
            //rules
            // Destructor
            ~Rectangle() override {}

            // Copy Constructor
            Rectangle(const Rectangle<U>& other)
                : shape::Shape(other), a(other.a) {}

            // Copy Assignment Operator
            Rectangle<U>& operator=(const Rectangle<U>& other) 
            {
                if (this == &other) return *this; // Self-assignment check
                shape::Shape::operator=(other);  // Call base class copy assignment
                a = other.a;
                return *this;
            }
    };

    template <typename U>
    class Triangle : public Shape //rownoramienny
    {
        private:
            U a,h;
        public:

            Triangle(U x, U y, const std::string n = "Triangle") : a(x), h(y),   Shape(n, {0,0})
            {
                //assumption we are starting draw at center
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

                computeCircuit();
                computeArea();
            }
            //rules
            // Destructor
            ~Triangle() override {}

            // Copy Constructor
            Triangle(const Triangle<U>& other)
                : shape::Shape(other), a(other.a), h(other.h) {}

            // Copy Assignment Operator
            Triangle<U>& operator=(const Triangle<U>& other) 
            {
                if (this == &other) return *this; // Self-assignment check
                shape::Shape::operator=(other);  // Call base class copy assignment
                a = other.a;
                h = other.h;
                return *this;
            }
            
    };
}

#endif