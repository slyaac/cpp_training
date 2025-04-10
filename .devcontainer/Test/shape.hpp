#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <math.h>
#include <fstream>

namespace shape{

    class Shape
    {
        public:
            double area;
            double circuit;
            std::pair<int,int> border;
            std::pair<int,int> center;
            string name;
            string type;
            string command;

            Shape(const string n, const string t, pair<int,int> c) : name(n), type(t), center(c){}

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

            void plotShape(string sN, string tN, pair<int,int> b,string sCmd)
            {
                // Create a Gnuplot script file
                std::ofstream script("shapes.gnuplot");
                script << "set terminal pngcairo size 800,800\n";
                script << "set output '"<<sN<<".png'\n";
                script << "set xrange ["<<b.first<<":"<<b.second<<"]\n";
                script << "set yrange ["<<b.first<<":"<<b.second<<"]\n";
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
                cout <<"Name = "<<getName()<<", area = "<<getArea()<<", circiut = "<<getCircuit()<<", corners = "<<getCorners()<<endl;
            }

            string getName()
            {
                return name;
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

            Wheel(double x, const string n = "Wheel") : r(x), Shape(n,"circle", make_pair(0,0))
            {
                //assumption we are starting draw at center
                border.first = center.first - static_cast<unsigned int>(ceil(1.5 * r));
                border.second = center.second + static_cast<unsigned int>(ceil(1.5 * r));
                command = " at "+ to_string(center.first) + "," + to_string(center.second) +" size " + std::to_string(r) + " ";
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

            Rectangle(double x, const string n = "Rectangle") : a(x),  Shape(n,"rectangle", make_pair(0,0))
            {
                //assumption we are starting draw at center
                border.first = center.first - a;
                border.second = center.second + a;
                double c1 = center.first - a/2;
                double c2 = center.second + a/2;
                command = " from " + std::to_string(c1) + "," + std::to_string(c2) + " to "\
                        + std::to_string(c1+a) + "," + std::to_string(c2-a) + " ";
                computeArea();
                computeCircuit();
            }
            
    };
}

#endif