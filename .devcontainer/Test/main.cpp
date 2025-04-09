#include "array_vector.hpp"
#include "array_list.hpp"
#include <iostream>
#include <chrono> 

#define VECTOR_ARRAY_MUL

static constexpr int fibo(int n)
{
    int value = 0;
    if(n > 1)
    {
        value =  fibo(n - 1) + fibo(n - 2);
    }
    else
    {
        value = n;
    }

    return value;
}

int main()
{
#ifdef ARRAY_ADD
    Matrix<int> neo1(3,3,0);
    neo1.set(0,0,7);
    neo1.set(1,1,4); 
    cout<<neo1;
    cout<<"+"<<endl;
    Matrix<int> neo2({{0,1,2},{2,3,4},{4,5,6}});
    cout<<neo2;

    try
    {
        Matrix<int> neo3 = neo1 + neo2;
        cout<<"result"<<endl;
        cout << neo3;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
#endif
#ifdef FIBO_TEST  
    constexpr int result = fibo(10);
    cout << "Fibo = "<< result <<", Hex = 0x"<< hex << uppercase << result << endl;
#endif
#ifdef LIST_ARRAY_MUL
    OtherArray<int, 150, 150> list_array;
    list_array.at(0,0) = 1;
    list_array.at(1,1) = 2;
    list_array.at(2,2) = 3;
    list_array.at(3,3) = 4;
    //cout<<"m1:"<<endl<<list_array;

    OtherArray<int, 150, 150> list_array2;//({{0,1},{2,3},{3,4},{4,5}});
    //cout<<"m2:"<<endl<<list_array2;
    auto start = chrono::high_resolution_clock::now();
    OtherArray<int, 150, 150> result = list_array * list_array2;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //cout<<"Result:"<<endl<<result<<endl;
    cout<<"took:"<<duration.count()<<" ms"<<endl;
#endif

#ifdef VECTOR_ARRAY_MUL
    Matrix<int> matA(150, 150);
    Matrix<int> matB(150, 150);

    auto start = chrono::high_resolution_clock::now();
    auto result = matA * matB;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //cout<<"Result:"<<endl<<result<<endl;
    cout<<"took:"<<duration.count()<<" ms"<<endl;


#endif

    return 0;
}