#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <list>
#include <iomanip>

using namespace std;

template <typename U, unsigned int rows, unsigned int cols>
class OtherArray
{
    private:
    list<list<U>> data;  

    public:
    OtherArray() : data(rows, list<U>(cols, 1)){}
    //brace initial
    OtherArray(const initializer_list<initializer_list<U>> init) : data(rows, list<U>(cols, 0))
    {
        //todo errors
        size_t i = 0, j = 0;
        for(const auto& row : init)
        {
            j = 0;
            for(const auto& element : row)
            {
                //cout<< element<<" "<<i<<" "<<j<<endl;
                this->at(i,j) = element;
                j++;
            }
            i++;
        }
    }

    /* expansion 
       OtherArray()
       {
            for(size_t i = 0; i<  rows; i++)
            {
                //create list in list
                data.emplace_back(list<U>(cols,0));
            }
       }
    */
       friend ostream& operator<<(ostream &os, const OtherArray &oa)
       {
            //get iterator from list begining
            
            for(size_t i = 0; i< oa.data.size(); i++)
            {
                //get pointer again to calculate offset properly
                auto rowIt = oa.data.begin();
                advance(rowIt,i);

                for(size_t j=0; j< rowIt->size(); j++)
                {
                    auto colIt = rowIt->begin();
                    advance(colIt,j);
                    //get element
                    os <<setfill('0')<<setw(2)<< *colIt<<" ";
                }
                os<<endl;
            }

            return os;
       }
       U& at(unsigned int row, unsigned int col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("OtherArray::at:W Index out of range.");
        }
        auto rowIt = data.begin();
        std::advance(rowIt, row);  // Advance to the desired row.
        auto colIt = rowIt->begin();
        std::advance(colIt, col);  // Advance to the desired column.
        return *colIt;
    }

    // Const overload of at(): uses cbegin() to work on const data.
    const U& at(unsigned int row, unsigned int col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("OtherArray::at:R Index out of range.");
        }
        auto rowIt = data.cbegin();  // Use const iterator.
        std::advance(rowIt, row);
        auto colIt = rowIt->cbegin();  // Use const iterator for the inner list.
        std::advance(colIt, col);
        return *colIt;
    }

    template <unsigned int otherCols>
    OtherArray<U, rows, otherCols> operator*(const OtherArray<U, cols, otherCols>& other) const 
    {
        if(data.size() != cols)
        {
            throw runtime_error("invalid size");
        }
        else
        {
            OtherArray<U, rows, otherCols> result;

            // Multiply each element (i, j) of the result.
            for (unsigned int i = 0; i < rows; ++i) 
            {
                for (unsigned int j = 0; j < otherCols; ++j) 
                {
                    U sum = 0;
                    for (unsigned int k = 0; k < cols; ++k) 
                    {
                        // Use our at() functions, which in a const context call the const overload.
                        sum += this->at(i, k) * other.at(k, j);
                    }
                    result.at(i, j) = sum;
                }
            }
            return result;
        }
    }
};



#endif