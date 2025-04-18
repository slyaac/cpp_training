/**
 * @file shape_pimpl.cpp
 * @brief Execute test cases
 */

#include <iostream>
#include "shape_pimpl.hpp"


namespace shape_pimpl {

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

    class ShapeImpl{

        public:
            double area; ///< The area of the shape.
            double circuit; ///< The circumference of the shape.
            MyPair<MyPair<int,int>,MyPair<int,int>> border; ///< Draw border.
            MyPair<double,double> center; ///< The center coordinates of the shape.
            std::vector<MyPair<double, double>> ddata; ///< Points representing the shape geometry.
            std::string name; ///< Name of the shape.
            double rotationAngle; ///< Rotation angle of the shape.

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

            ShapeImpl(const std::string& name) : name(name) {}

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

    };

    Shape::Shape(const std::string& name) : pImpl(std::make_unique<ShapeImpl>(name)) {}
    Shape::~Shape() = default;


    void Shape::computeCircuit() {
        pImpl->computeCircuit();
    }
    
    void Shape::computeArea() {
        pImpl->computeArea();
    }
    
    double Shape::getArea() const {
        return pImpl->area;
    }
    
    double Shape::getCircuit() const {
        return pImpl->circuit;
    }
    
    unsigned int Shape::getCorners() const {
        return pImpl->getCorners();
    }
    
    void Shape::rotate(double degrees) {
        pImpl->rotate(degrees);
    }
    
    void Shape::printInfo() const {
        pImpl->printInfo();
    }
    
    void Shape::drawMe() {
        pImpl->drawMe();
    }

    // Rectangle Implementation
    template <typename U>
    class RectangleImpl 
    {
        public:
            explicit RectangleImpl(U side) : sideLength(side) {}

            double sideLength;
            
            void generatePoints(ShapeImpl& shapeImpl) 
            {
                double half = sideLength / 2;
                std::vector<MyPair<double, double>>  points =
                {
                    { half,  - half},
                    { half,  - half},
                    { half,  half},
                    { - half,  half},
                    { - half,  - half} // Closing the rectangle
                };

                shapeImpl.ddata = points;
            }
    };

    template <typename U>
    Rectangle<U>::Rectangle(U sideLength, const std::string& name)
        : Shape(name), pImpl(std::make_unique<RectangleImpl<U>>(sideLength)) 
        {
            pImpl->generatePoints(*Shape::pImpl);
            computeCircuit(); 
            computeArea();  
        }

    template <typename U>
    Rectangle<U>::~Rectangle() = default;

    // Triangle Implementation
    template <typename U>
    class TriangleImpl
    {
        public:
            explicit TriangleImpl(U side) : sideLength(side) {}

            double sideLength;
            
            void generatePoints(ShapeImpl& shapeImpl) 
            {
                double baseHalf = sideLength / 2.0; // Half the base length
                double height = std::sqrt(3.0) / 2.0 * sideLength; // Height of an equilateral triangle
                std::vector<MyPair<double, double>>  points =
                {
                    { - baseHalf,  - height / 2},
                    { baseHalf,  - height / 2},
                    { 0,   height / 2},
                    { - baseHalf,  - height / 2}
                };

                shapeImpl.ddata = points;
            }
    };

    template <typename U>
    Triangle<U>::Triangle(U sideLength, const std::string& name)
        : Shape(name), pImpl(std::make_unique<TriangleImpl<U>>(sideLength)) 
        {
            pImpl->generatePoints(*Shape::pImpl);
            computeCircuit(); 
            computeArea();  
        }

        template <typename U>
        Triangle<U>::~Triangle() = default;

        // Wheel Implementation
    template <typename U>
    class WheelImpl
    {
        public:
            explicit WheelImpl(U r) : r(r) {}

            double r;
            
            void generatePoints(ShapeImpl& shapeImpl) 
            {
                double offset = 0;
                const unsigned int res = 30;
                //initial point offset to make sure base of shape is  parallel to x axis
                (res % 2) == 0 ? offset = (M_PI / (res)) : offset = (M_PI / 2) ; 
                MyPair<double, double> tail;
                for (int i = 0; i < res; ++i) 
                {
                    double angle = ((2 * M_PI * i) / res) + offset;  // Angle in radians
                    MyPair<double, double> p;
                    p.x = r * cos(angle);
                    p.y = r * sin(angle);
                    shapeImpl.ddata.push_back(p);
                    i ? 0 : tail = p;
                }
                shapeImpl.ddata.push_back(tail);
            }

            unsigned int getCorners() const 
            {
                return 0;
            }

    };

        template <typename U>
        Wheel<U>::Wheel(U r, const std::string& name)
            : Shape(name), pImpl(std::make_unique<WheelImpl<U>>(r)) 
        {
            pImpl->generatePoints(*Shape::pImpl);
            computeCircuit(); 
            computeArea();  
        }

        template <typename U>
        Wheel<U>::~Wheel() = default;


        template <typename U>
        unsigned int Wheel<U>::getCorners() const {
            return pImpl->getCorners(); // Uses WheelImpl's implementation
        }

        template <typename U>
        void Wheel<U>::printInfo() const {
            std::cout << "Name: Wheel, "
                    << "Radius: " << pImpl->r << ", "
                    << "Corners: " << getCorners() << std::endl; // Use overridden getCorners
        }
            }

void testCode()
{
    shape_pimpl::Rectangle<double> rect(5,"kwa");
    shape_pimpl::Triangle<double> tri(10,"tri");
    shape_pimpl::Wheel<double> whe(15,"whe");

    rect.printInfo();
    tri.printInfo();
    whe.printInfo();
}