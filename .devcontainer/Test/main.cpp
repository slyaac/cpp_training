/**
 * @file main.cpp
 * @brief Execute test code
 */

//#include "array_vector.hpp"
//#include "array_list.hpp"
#include <iostream>
#include <chrono> 
#include "shape.hpp"
#include <vector>
#include <iomanip>
#include <thread>
#include <atomic>

using namespace std;

atomic<bool> running(true);
atomic<int> rangle(0);

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
template <typename... Args>
std::vector<std::unique_ptr<shape::Shape>> makeVector(Args&&... args) {
    std::vector<std::unique_ptr<shape::Shape>> vec;
    (vec.push_back(std::forward<Args>(args)), ...);
    return vec;
}

void checkInput() {
    string s_inpput;
    while (running) {
        std::cin  >> s_inpput;
        if (s_inpput == "x") {
            running = false; // End the loop gracefully
        }
        else
        {
            try {
                rangle = std::stoi(s_inpput); // Convert string to integer
        
                // Perform actions with the integer value here
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            }
        }
    }
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

#ifdef VEC_ARRAY_MUL
    Matrix<int> matA(150, 150);
    Matrix<int> matB(150, 150);

    auto start = chrono::high_resolution_clock::now();
    auto result = matA * matB;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //cout<<"Result:"<<endl<<result<<endl;
    cout<<"150 took:"<<duration.count()<<" ms"<<endl;

    Matrix<int> matC(500, 500);
    Matrix<int> matD(500, 500);

    start = chrono::high_resolution_clock::now();
    auto result2 = matC * matD;
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //cout<<"Result:"<<endl<<result<<endl;
    cout<<"500 took:"<<duration.count()<<" ms"<<endl;


#endif

#ifdef SHAPE_POINTERS
    shape::Wheel<double> wheel(1.5);
    shape::Rectangle<int> rect(10);
    shape::Triangle<int> tri(7);

    vector<shape::Shape *> vptr = { &wheel, &rect, &tri};

    auto uptr = makeVector(
        std::make_unique<shape::Wheel<int>>(2),
        std::make_unique<shape::Rectangle<int>>(5),
        std::make_unique<shape::Triangle<int>>(3)
    );

    vector<shape::Shape*> nptr = {
        new shape::Wheel<double>(3),
        new shape::Rectangle<int>(4),
        new shape::Triangle<int>(5)
    };

    for(auto& obj : vptr)
    {
        obj->drawMe();
        obj->printInfo();
    }

    for(auto& obj : uptr)
    {
        obj->drawMe();
        obj->printInfo();
    }

    for(auto& obj : nptr)
    {
        obj->drawMe();
        obj->printInfo();
        delete obj;
    }
#endif

    // shape rotation
    // generates hexagon
    shape::Wheel<double> poly(4,6,"hexagon");
    poly.printInfo();
    poly.drawMe();

    std::thread inputThread(checkInput);

    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); //wait
        poly.rotate(rangle);
        poly.drawMe();
    }

    inputThread.join(); // Ensure the input thread is finished

    return 0;
}