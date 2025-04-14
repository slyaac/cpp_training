/**
 * @file array_vector.hpp
 * @brief vector array methods
 */

#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

#include <vector>
#include <iostream>
#include <thread>

using namespace std;

template <typename T>
class Matrix
{
    private:
    /* todo listy */
        vector<vector<T>> data;

    public:

    int rows() const { return data.size(); }
    int cols() const { return data[0].size(); }

    std::vector<int>& operator[](int row) { return data[row]; }
    const std::vector<int>& operator[](int row) const { return data[row]; }

    Matrix(int rows, int cols) : data(rows, std::vector<T>(cols, 0)) {}

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

   Matrix<T> operator*(const Matrix& other) const {
    if (cols() != other.rows()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication!");
    }

    Matrix result(rows(), other.cols());
    std::vector<std::thread> threads;

    // Lambda for row-wise multiplication
    auto multiplyRow = [&](int row) {
        for (int j = 0; j < other.cols(); ++j) {
            result[row][j] = 0;
            for (int k = 0; k < cols(); ++k) {
                result[row][j] += data[row][k] * other[k][j];
            }
        }
    };
#if 1
    cout <<"threads"<<endl;
    // Create threads for each row
    for (int i = 0; i < rows(); ++i) {
        threads.push_back(std::thread(multiplyRow, i));
    }

    // Join all threads
    for (auto& th : threads) {
        th.join();
    }
#else
    cout <<"normal"<<endl;
    for (int i = 0; i < rows(); ++i) 
    {
        multiplyRow(i);
    }
#endif
    return result;
}
   
};



#endif