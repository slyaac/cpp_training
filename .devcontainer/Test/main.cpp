#include "array.hpp"
#include <iostream>
#include <list>

using namespace std;

template <typename U, unsigned int rows, unsigned int cols>
class OtherArray
{
    private:
    U a_data[rows][cols];
    list<list<U>> l_data;  

    public:
    OtherArray() : l_data(rows, list<U>(cols, 0)){}

    /* expansion 
       OtherArray()
       {
            for(size_t i = 0; i<  rows; i++)
            {
                //create list in list
                l_data.emplace_back(list<U>(cols,0));
            }
       }
    */
       friend ostream& operator<<(ostream &os, const OtherArray &oa)
       {
            //get iterator from list begining
            
            for(size_t i = 0; i< oa.l_data.size(); i++)
            {
                //get pointer again to calculate offset properly
                auto rowIt = oa.l_data.begin();
                advance(rowIt,i);

                for(size_t j=0; j< rowIt->size(); j++)
                {
                    auto colIt = rowIt->begin();
                    advance(colIt,j);
                    //get element
                    os << *colIt;
                }
                os<<endl;
            }

            return os;
       }

        void set(unsigned int row, unsigned int col, const U& value) 
        {
            auto rowIt = l_data.begin();
            std::advance(rowIt, row);
            auto colIt = rowIt->begin();
            std::advance(colIt, col);
            *colIt = value;
        }
};

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
    
    constexpr int result = fibo(10);
    cout << "Fibo = "<< result <<", Hex = 0x"<< hex << uppercase << result << endl;

    OtherArray<int, 4, 4> list_array;
    list_array.set(0,0,1);
    list_array.set(1,1,2);
    list_array.set(2,2,3);
    list_array.set(3,3,4);
    cout<<list_array;


    return 0;
}