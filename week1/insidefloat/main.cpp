/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/18/2020 08:36:55 PM
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
#include <iomanip>
#include <bitset>
#include <climits>

#define SIZE sizeof(float) * CHAR_BIT
#define EXP_SIZE 8
#define MATISA 23

static union {
	float input;
	int output;
	struct {
		unsigned int mantisa : 23;
		unsigned int exponent: 8;
		unsigned int sign: 1;
	} parts;
} data;

int* get_bits(float number) { 
	std::bitset<SIZE> bits(data.output);
	static int array[SIZE];
	for (long unsigned i=0; i < SIZE; ++i)
		array[i] = bits[SIZE - i - 1];

	return array;
}

int get_sign(int bits[]) {
	return bits[0] ? -1 : 1;
}

float get_mantisa(int bits[]) {
	float result = .0f;
	float inter = 1.f / 2;
	for (int i = EXP_SIZE + 1; i < 1 + EXP_SIZE + MATISA; ++i){
		result += bits[i] * inter;
		inter /= 2;
	}

	return 1 + result;
}

bool is_little_edian() {
	short int word = 0x001;
	char* b = (char *)&word;
	return b[0];
}

int main(void) {
	// std::cout << is_little_edian() << std::endl; is true to my machine

	float number;
	std::cin >> number;

	data.input = number;
	int* bits = get_bits(number);

	// prints formated number
	std::cout << bits[0] << "|";

	for (int i=1; i < EXP_SIZE + 1; ++i)
		std::cout << bits[i]; // prints sign
	std::cout << "|";
	for (int i=EXP_SIZE + 1; i < EXP_SIZE + MATISA + 1; ++i)
		std::cout << bits[i];
	std::cout << std::endl;

	if (number == .0f){
		std::cout << 0 << std::endl
				<< -126 << std::endl
				<< std::setprecision(2) << .0f << std::endl;
		return 0;
	}

	// print sign
	std::cout << 1 - data.parts.sign << std::endl;

	// print exponent
	std::cout << (data.parts.exponent - 127) << std::endl;

	// print matisa
	std::cout << get_mantisa(bits) << std::endl;

	return 0;
}
