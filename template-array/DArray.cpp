/*
 * =====================================================================================
 *
 *       Filename:  DArray.cpp
 *
 *        Version:  1.0
 *        Created:  11/28/2020 08:19:54 PM
 *       Compiler:  gcc
 *
 *         Author:  w1jtoo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include MAX_SIZE 


template <class T>
class DArray {
public:
    DArray(size_t size);
    DArray(const DArray& other);
    ~DArray();
    
    ??? operator[](size_t index) const;
    T& operator[](size_t index);
private:
    // ...
};
