/*
 * =====================================================================================
 *
 *       Filename:  neighbour.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/15/2020 04:56:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

class Base1 {
public:
    int a;
    int b;
};
class Base2 {
public:
    int x;
    int y;

    void getBase1() {
        auto b = reinterpret_cast<int*>(this);
        auto b1 = reinterpret_cast<Base1*>(b[2]);
        std::cout << "c.a = " << b1->a  << " c.b = " << b1->b << std::endl;
    }
};
class Child : public Base1, public Base2 {
};

int main() {
    Child c;
    c.a = 10;
    c.b = 20;
    c.x = 30;
    c.y = 40;
    c.getBase1();
    return 0;
}
