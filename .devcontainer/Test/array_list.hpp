#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <list>
#include <iomanip>
#include <thread>
#include <stdexcept>
#include <vector>

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

       U& at(unsigned int row, unsigned int col) 
       {
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
        const U& at(unsigned int row, unsigned int col) const 
        {
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

                cout<<"normal"<<endl;
                auto compute_rows = [&](unsigned int start_row, unsigned int end_row) 
                {
                    for (unsigned int row = start_row; row < end_row; ++row) 
                    {
                        for (unsigned int col = 0; col < otherCols; ++col) 
                        {
                            U sum = 0;
                            for (unsigned int k = 0; k < cols; ++k) 
                            {
                                sum += this->at(row, k) * other.at(k, col);
                            }
                            result.at(row, col) = sum;
                        }
                    }
                };
#if 0
                // Multiply each element (i, j) of the result.
                compute_rows(0, rows);
#else
                cout<<"Threads"<<endl;
                std::vector<std::thread> threads;
                const size_t num_of_threads = ((rows * otherCols) < std::thread::hardware_concurrency()) ? (rows * otherCols) : (std::thread::hardware_concurrency());
                const size_t rows_per_thread = (rows / num_of_threads) + 1;
                threads.reserve(num_of_threads);
                std::cout << "Reserved space in vector for " << threads.capacity() << " threads!" << std::endl;
                // Divide rows across threads
                
                size_t row_start = 0;
                size_t row_end = rows_per_thread;
    
                while (row_end - row_start > 0)
                {
                    threads.push_back(std::thread(compute_rows, row_start, row_end));
                    row_start = row_end;
                    row_end += rows_per_thread;
                    row_end = row_end < rows ? row_end : rows;
                }
    
        
                // Join all threads
                for (auto& t : threads) 
                {
                    t.join();
                }
#endif
            return result;
        }
    }
};



#endif