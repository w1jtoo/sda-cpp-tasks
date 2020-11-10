/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/28/2020 09:37:25 PM
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
#define TESTS_COUNT 1000000

static int sum = 0;

void stack_array_allocation(void);
void heap_array_allocation(void);
void print_sum(int array[10]);

/* ===== RESULTS =====
 * ** | stack | heap  
 * ---+-------+-------
 * o2 | 3392  | 20084 
 * ---+-------+-------
 * o3 |  278  | 15188 
 */

int main(void) { 
	auto t = clock();
	for (int j=0; j < 1000; ++j) {
		for (int i=0; i < TESTS_COUNT; ++i){
			stack_array_allocation();
		}
	}
	auto t1 = (clock() - t) / 1000;
	printf("First sum %i\n", sum);

	t = clock();
	for (int j = 0; j < 1000; ++j) {
		for (int i=0; i < TESTS_COUNT; ++i){
			heap_array_allocation();
		}
	}
	auto t2 = (clock() - t) / 1000;
	printf("First sum %i\n", sum);

	printf("In took %ld ms to allocate array of 10 int on stack %i times\n", t1, TESTS_COUNT);
	printf("In took %ld ms to allocate array of 10 int on heap %i times\n", t2, TESTS_COUNT);
}

void stack_array_allocation(void) {
	int a[10] = { };
	print_sum(a);
}

inline void heap_array_allocation(void) {
	int* a = new int[10]();
	print_sum(a);
	delete a;
}

inline void print_sum(int array[10]) {
	sum = 0;
	for(int i = 0; i < 10; ++i) { 
		sum += array[i];
	}
}

