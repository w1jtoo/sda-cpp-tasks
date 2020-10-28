/*
 * =====================================================================================
 *
 *       Filename:  love-rust.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/19/2020 07:55:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  w1jtoo
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

int main(void) {
	int& ref = *(int*) nullptr;
	// std::cout << ref << std::endl;
	std::cout << "help me compiler" << std::endl;
}
