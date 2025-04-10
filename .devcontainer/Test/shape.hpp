#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <math.h>

namespace shape{

    class Shape
    {
        public:
            double area;
            double circuit;

            virtual void computeArea() = 0;
            virtual void computeCircuit() = 0;
            virtual double getArea() = 0;
            virtual double getCircuit() = 0;
            virtual unsigned int getCorners() = 0;
            virtual string getName() = 0;
    };

    class Wheel : public Shape
    {
        private:
            unsigned int r;
            string name;
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

            Wheel(double x) : r(x), name("Wheel")
            {
                computeArea();
                computeCircuit();
            }
            
    };
}

#endif