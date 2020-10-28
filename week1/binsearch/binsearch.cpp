/*
 * =====================================================================================
 *
 *       Filename:  binsearch.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/18/2020 05:34:46 PM
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

size_t binsearch(int array[], size_t len, int target){
	size_t low = 0;
	size_t high = len - 1;

	while (low <= high) { 
		const size_t middle = ((high - low) / 2) + low;
		if (middle >= len || middle < 0)
			break;

		if (array[middle] == target)
			return middle;

		if (array[middle] < target)
			low = middle + 1;

		if (array[middle] > target)
			high = middle - 1;
	}

	return len;
}

int main(void) {
	int array[] = {1, 3 ,6};
	std::cout << "binsearch on {1, 3,6}" << std::endl;
	std::cout << binsearch(array, 3, 1) << std::endl;
	std::cout << binsearch(array, 3, 3) << std::endl;
	std::cout << binsearch(array, 3, 6) << std::endl;
	std::cout << binsearch(array, 3, -1) << std::endl;
	std::cout << binsearch(array, 3, 2) << std::endl;
	std::cout << binsearch(array, 3, 5) << std::endl;
	std::cout << binsearch(array, 3, 7) << std::endl;
	
	int array1[] = {1, 2, 4, 6};
	std::cout << "binsearch on {1, 2, 4 ,6}" << std::endl;
	std::cout << binsearch(array1, 4, 1) << std::endl;
	std::cout << binsearch(array1, 4, 4) << std::endl;
	std::cout << binsearch(array1, 4, 7) << std::endl;
}
