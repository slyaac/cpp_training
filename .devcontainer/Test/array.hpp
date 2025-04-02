#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

using namespace std;

class Matrix
{
    private:
        //2d vector
        vector<vector<int>> data;
        size_t rows, columns;

    public:

        Matrix(size_t r, size_t c);
        Matrix(const vector<vector<int>> &init);

        void show();
        void set(size_t sr, size_t sc, int val);
        //workaround to have two arguments...
        friend Matrix operator+(const Matrix &a, const Matrix &b);

};

#endif