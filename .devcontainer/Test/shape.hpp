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
            MyPair<MyPair<double,double>,MyPair<double,double>> border;
            MyPair<double,double> center;
            std::vector<MyPair<double, double>> ddata;
            std::string name;

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

            virtual void computeCircuit() = 0;
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

            void plotShape(std::string sN, MyPair<MyPair<double,double>,MyPair<double,double>> b)
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

            void createData(std::vector<MyPair<double,double>> &data)
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
    };

    class Wheel : public Shape
    {
        private:
            double r;
        public:

            void computeCircuit()
            {
                circuit = 2 * M_PI * r;
            }

            unsigned int getCorners()
            {
                return 0;
            }

            Wheel(double x, const std::string n = "Wheel") : r(x), Shape(n, {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - (ceil(1.5 * r));
                border.x.y = center.y + (ceil(1.5 * r));
                border.y = border.x;
                const unsigned int res = 30;
                MyPair<double, double> tail;;
                for (int i = 0; i < res; ++i) {
                    double angle = (2 * M_PI * i) / res;  // Angle in radians
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
            
    };

    class Rectangle : public Shape
    {
        private:
            double a;
        public:

            void computeCircuit()
            {
                circuit = 4 * a;
            }

            Rectangle(double x, const std::string n = "Rectangle") : a(x),  Shape(n, {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - a;
                border.x.y = center.y + a;
                border.y = border.x;
                MyPair<double, double> c1, c2, c3, c4;
                c1.x = center.x - a/2;
                c1.y = center.y - a/2;
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
            
    };

    class Triangle : public Shape //rownoramienny
    {
        private:
            double a,h;
        public:

            void computeCircuit()
            {
                circuit = a + 2 * sqrt(( (0.5 * a) * (0.5 * a) ) + (h * h));
            }

            Triangle(double x, double y, const std::string n = "Triangle") : a(x), h(y),   Shape(n, {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - a;
                border.x.y = center.x + a;
                border.y.x = center.y - h;
                border.y.y = center.y + 2*h;
                MyPair <double, double> c1, c2, c3;
                c1.x = center.x - a/2;
                c1.y = center.y;
                c2.x = c1.x + a;
                c2.y = c1.y;
                c3.x = c1.x + a/2;
                c3.y = c1.y + h;
                ddata.push_back(c1);
                ddata.push_back(c2);
                ddata.push_back(c3);
                ddata.push_back(c1);

                computeCircuit();
                computeArea();
            }
            
    };
}

#endif