
#include "array.hpp"
/*
4) zamiast show przeładować operator <<
5) Rozmiar macierzy ma być niezmienny
6) Klasa Matrix ma działać na szablonach
*/
/* statyczna implementacja + T */
vector<int>& Matrix::operator[](const int index)
{
    return data[index]; 
    /*
    int Matrix::operator[](wiersz, col) //[3,3]
    return data[weirsz][col]
     */
}/* readonly */

Matrix operator+(const Matrix &a, const Matrix &b)
{
    
    if((a.data[0].size() != b.data[0].size()) || (a.data.size() != b.data.size()))
    {
        throw invalid_argument("matrix size must match when adding them");
    }

    Matrix new_data(a.data.size(), a.data[0].size());
    for(size_t i = 0; i < a.data.size(); i++)
    {
        for(size_t j = 0; j < a.data[0].size(); j++)
        {
            new_data.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return new_data;
}

void Matrix::set(size_t sr, size_t sc, int val)
{
    if((sr > data.size()) || (sc > data[0].size()))
    {
        throw invalid_argument(" out of bound");
    }

    data[sr][sc] = val;
}

Matrix::Matrix(size_t r, size_t c)
{
    //rows and columns passed as argument
    data.resize(r, vector<int>(c, 0));
}

Matrix::Matrix(const vector<vector<int>> &init) : data(init){};

ostream& operator<<(ostream& os, const Matrix &a)
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