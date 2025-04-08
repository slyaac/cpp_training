#include "array_vector.hpp"
#include "array_list.hpp"
#include <iostream>

#define ARRAY_MUL

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
    OtherArray<int, 4, 4> list_array;
    list_array.a_set(0,0,1);
    list_array.a_set(1,1,2);
    list_array.a_set(2,2,3);
    list_array.a_set(3,3,4);
    cout<<list_array;

    OtherArray<int, 4, 2> list_array2({{0,1},{2,3},{3,4},{4,5}});
    cout<<list_array2;
    
    return 0;
}