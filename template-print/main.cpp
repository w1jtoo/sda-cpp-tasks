/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *        Version:  1.0
 *        Created:  11/28/2020 08:33:39 PM
 *       Compiler:  gcc
 *
 *         Author:  w1jtoo 
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

template <class F, class... Args> 
void for_each_argument(F f, Args&&... args) {
    [](...){}((f(std::forward<Args>(args)), 0)...);
}

template<class... Args>
void print(Args... args) {
        const size_t nargs = sizeof...(args);
    X x_array[nargs];

    X *x = x_array;
    int unused[]{(f(*x++, args), 1)...};
    std::cout << std::endl;
}

int main(void) {
    print(1, 2, 3);
    print(1, 2);
    print(1);
    print();
}
