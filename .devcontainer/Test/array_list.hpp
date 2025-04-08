#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <list>

using namespace std;

template <typename U, unsigned int rows, unsigned int cols>
class OtherArray
{
    private:
    U a_data[rows][cols];
    list<list<U>> l_data;  

    public:
    OtherArray() : l_data(rows, list<U>(cols, 0)){}

    /* expansion 
       OtherArray()
       {
            for(size_t i = 0; i<  rows; i++)
            {
                //create list in list
                l_data.emplace_back(list<U>(cols,0));
            }
       }
    */
       friend ostream& operator<<(ostream &os, const OtherArray &oa)
       {
            //get iterator from list begining
            
            for(size_t i = 0; i< oa.l_data.size(); i++)
            {
                //get pointer again to calculate offset properly
                auto rowIt = oa.l_data.begin();
                advance(rowIt,i);

                for(size_t j=0; j< rowIt->size(); j++)
                {
                    auto colIt = rowIt->begin();
                    advance(colIt,j);
                    //get element
                    os << *colIt;
                }
                os<<endl;
            }

            return os;
       }

        void set(unsigned int row, unsigned int col, const U& value) 
        {
            auto rowIt = l_data.begin();
            std::advance(rowIt, row);
            auto colIt = rowIt->begin();
            std::advance(colIt, col);
            *colIt = value;
        }
};



#endif