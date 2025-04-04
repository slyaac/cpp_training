#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Matrix
{
    private:
    /* todo listy */
        vector<vector<T>> data;

    public:

    Matrix(size_t r, size_t c, const T& defaultValue)
    {
        //rows and columns passed as argument
        data.resize(r); // Resize the number of rows
        for (size_t i = 0; i < r; ++i) {
            data[i].resize(c, defaultValue); // Resize each row and set default value
        }
    }
    Matrix(const vector<vector<T>> &init) : data(init){};

    void set(size_t sr, size_t sc,const  T& val)
    {
        if((sr > data.size()) || (sc > data[0].size()))
        {
            throw invalid_argument(" out of bound");
        }

        data[sr][sc] = val;
    }
    
    //workaround to have two arguments...
    Matrix<T> operator+(const Matrix<T> &a)
    {

        if((a.data[0].size() != data[0].size()) || (a.data.size() != data.size()))
        {
            throw invalid_argument("matrix size must match when adding them");
        }
    
        Matrix<T> new_data(a.data.size(), a.data[0].size(), 0);
        for(size_t i = 0; i < a.data.size(); i++)
        {
            for(size_t j = 0; j < a.data[0].size(); j++)
            {
                new_data.data[i][j] = a.data[i][j] + data[i][j];
            }
        }
    
        return new_data;

    }

   T operator()(const int row, const int col)
   {
    return data[row][col]; 
   }

   friend ostream& operator<<(ostream& os, const Matrix<T> &a)
   {
    int temp = a.data[0].size()*2 - 1;
    while (temp > 0)
    {
        os<<"-";
        temp--;
    };
    os<<endl;

    //for(const auto& row : a.data)
    for(size_t i = 0; i< a.data.size(); i++)
    {
        //for(const auto& element : row)
        for(size_t j = 0; j< a.data[i].size(); j++)
        {
            //os<<element<<" ";
            os<<a.data[i][j]<<" ";
        }
        os <<endl;
    }

    temp = a.data[0].size()*2 - 1;
    while (temp > 0)
    {
        os<<"-";
        temp--;
    };
    os<<endl;

    return os;
   }
   
};



#endif