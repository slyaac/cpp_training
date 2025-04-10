#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <math.h>
#include <fstream>

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
            std::string name;
            std::string type;
            std::string command;

            Shape(const std::string n, const std::string t, MyPair<int,int> c) : name(n), type(t), center(c.x, c.y){}

            virtual void computeArea() = 0;
            virtual void computeCircuit() = 0;
            double getArea()
            {
                return area;
            }

            double getCircuit()
            {
                return circuit;
            }
            virtual unsigned int getCorners() = 0;
            void drawMe()
            {
                plotShape(name,type,border,command);
            }

            void plotShape(std::string sN, std::string tN, MyPair<MyPair<double,double>,MyPair<double,double>> b,std::string sCmd)
            {
                // Create a Gnuplot script file
                std::ofstream script("shapes.gnuplot");
                script << "set terminal pngcairo size 800,800\n";
                script << "set output '"<<sN<<".png'\n";
                script << "set xrange ["<<b.x.x<<":"<<b.x.y<<"]\n";
                script << "set yrange ["<<b.y.x<<":"<<b.y.y<<"]\n";
                script << "unset key\n";
                script << "set object 1 "<<tN;
                script << sCmd;
                script << " fillcolor rgb 'blue' fillstyle solid border lc rgb 'black'\n";
                script << "set grid\n";
                script << "plot NaN\n"; // Dummy plot to display objects
                script.close();
            
                // Execute the Gnuplot script
                std::system("gnuplot shapes.gnuplot");
            }

            void printInfo()
            {
                std::cout <<"Name = "<<getName()<<", area = "<<getArea()<<", circiut = "<<getCircuit()<<", corners = "<<getCorners()<<std::endl;
            }

            std::string getName()
            {
                return name;
            }

            std::string p2s(MyPair<double,double> p)
            {
                std::string text = std::to_string(p.x) + "," +  std::to_string(p.y);
                return text;
            }
    };

    class Wheel : public Shape
    {
        private:
            double r;
        public:
            void computeArea()
            {
                area = r * r * M_PI;
            }

            void computeCircuit()
            {
                circuit = 2 * M_PI * r;
            }

            unsigned int getCorners()
            {
                return 0;
            }

            Wheel(double x, const std::string n = "Wheel") : r(x), Shape(n,"circle", {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - (ceil(1.5 * r));
                border.x.y = center.y + (ceil(1.5 * r));
                border.y = border.x;
                command = " at "+ p2s(center) +" size " + std::to_string(r) + " ";
                computeArea();
                computeCircuit();
            }
            
    };

    class Rectangle : public Shape
    {
        private:
            double a;
        public:
            void computeArea()
            {
                area = a * a;
            }

            void computeCircuit()
            {
                circuit = 4 * a;
            }

            unsigned int getCorners()
            {
                return 4;
            }

            Rectangle(double x, const std::string n = "Rectangle") : a(x),  Shape(n,"rectangle", {0,0})
            {
                //assumption we are starting draw at center
                border.x.x = center.x - a;
                border.x.y = center.y + a;
                border.y = border.x;
                MyPair <double, double> c1, c2;
                c1.x = center.x - a/2;
                c1.y = center.y - a/2;
                c2.x = c1.x + a;
                c2.y = c1.y + a;
                command = " from " + p2s(c1) + " to " + p2s(c2) + " ";
                computeArea();
                computeCircuit();
            }
            
    };

    class Triangle : public Shape //rownoramienny
    {
        private:
            double a,h;
        public:
            void computeArea()
            {
                area = 0.5 * a * h;
            }

            void computeCircuit()
            {
                circuit = a + 2 * sqrt(( (0.5 * a) * (0.5 * a) ) + (h * h));
            }

            unsigned int getCorners()
            {
                return 3;
            }

            Triangle(double x, double y, const std::string n = "Triangle") : a(x), h(y),   Shape(n,"polygon", {0,0})
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
                command = " from " + p2s(c1) + " to "\
                        + p2s(c2) + " to "\
                        + p2s(c3) + " to "\
                        + p2s(c1);

                computeArea();
                computeCircuit();
            }
            
    };
}

#endif