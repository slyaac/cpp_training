#include <iostream>
#include "array.hpp"

Matrix operator+(const Matrix &a, const Matrix &b)
{
    if((a.columns != b.columns) || (a.rows != b.rows))
    {
        throw invalid_argument("matrix size must match when adding them");
    }

    Matrix new_data(a.rows, a.columns);
    for(size_t i = 0; i < a.rows; i++)
    {
        for(size_t j = 0; j < a.columns; j++)
        {
            new_data.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return new_data;
}

void Matrix::show()
{
    {
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = 0; j < columns; j++)
            {
                cout<<data[i][j]<<"";
            }
            cout <<endl;
        }
    }
}

void Matrix::set(size_t sr, size_t sc, int val)
{
    if((sr > rows) || (sc > columns))
    {
        throw invalid_argument(" out of bound");
    }

    data[sr][sc] = val;
}

Matrix::Matrix(size_t r, size_t c) : rows(r), columns(c)
{
    //rows and columns passed as argument
    data.resize(rows, vector<int>(columns, 0));
}

Matrix::Matrix(const vector<vector<int>> &init) : data(init)
{
    //rows and columns unknown
    rows = data.size();
    columns = data[0].size();
};