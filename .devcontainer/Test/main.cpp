#include "array.hpp"
#include <iostream>


int main()
{
    cout << "Docker!" << endl;

    Matrix neo1(3,3);
    neo1.set(0,0,7);
    neo1.set(1,1,4);
    cout<<neo1;
    cout<<"+"<<endl;
    Matrix neo2({{0,1,2},{2,3,4},{4,5,6}});
    cout<<neo2;


    try
    {
        Matrix neo3 = neo1 + neo2;
        cout<<"result"<<endl;
        cout << neo3;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}