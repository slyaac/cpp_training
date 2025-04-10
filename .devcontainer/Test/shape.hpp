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

            virtual void computeArea() = 0;
            virtual void computeCircuit() = 0;
            virtual double getArea() = 0;
            virtual double getCircuit() = 0;
            virtual unsigned int getCorners() = 0;
            virtual string getName() = 0;
            virtual void drawMe() = 0;

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
    };

    class Wheel : public Shape
    {
        private:
            double r;
            string name;
            string type;
            std::pair<int,int> center;
            string command;
        public:
            void computeArea()
            {
                area = r * r * M_PI;
            }

            void computeCircuit()
            {
                circuit = 2 * M_PI * r;
            }

            double getArea()
            {
                return area;
            }

            double getCircuit()
            {
                return circuit;
            }

            unsigned int getCorners()
            {
                return 0;
            }

            string getName()
            {
                return name;
            }

            void drawMe()
            {
                plotShape(name,type,border,command);
            }

            Wheel(double x) : r(x), name("Wheel"), type("circle"), center(0,0)
            {
                //assumption we are starting draw at center
                border.first = 0 - static_cast<unsigned int>(ceil(1.5 * r));
                border.second = 0 + static_cast<unsigned int>(ceil(1.5 * r));
                command = " at 0,0 size " + std::to_string(r);
                computeArea();
                computeCircuit();
            }
            
    };
}

#endif