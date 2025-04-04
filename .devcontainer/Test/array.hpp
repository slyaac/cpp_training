#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
    private:
    /* todo listy */
        //2d vector
        vector<vector<int>> data;
        size_t rows, columns;

    public:

        Matrix(size_t r, size_t c);
        Matrix(const vector<vector<int>> &init);

        void set(size_t sr, size_t sc, int val);
        //workaround to have two arguments...
        friend Matrix operator+(const Matrix &a, const Matrix &b);
        vector<int>& operator[](const int index);
        friend ostream& operator<<(ostream& os, const Matrix &a);
};

#endif