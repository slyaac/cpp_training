#include "array.hpp"
#include <iostream>


int main()
{
    cout << "Docker?" << endl;

    Matrix neo1(2,2);
    //neo1.show();
    neo1.set(0,0,7);
    neo1.set(1,1,4);
    neo1.show();
    cout<<"+"<<endl;
    Matrix neo2({{0,1},{2,3}});
    neo2.show();


    try
    {
        Matrix neo3 = neo1 + neo2;
        cout<<"result"<<endl;
        neo3.show();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}