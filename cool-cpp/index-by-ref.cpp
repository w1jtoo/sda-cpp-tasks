/*
 * =====================================================================================
 *
 *		 Filename:	index-by-ref.cpp
 *
 *	  Description:	
 *
 *		  Version:	1.0
 *		  Created:	10/19/2020 08:08:30 PM
 *		 Revision:	none
 *		 Compiler:	gcc
 *
 *		   Author:	w1jtoo
 *	 Organization:	
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

void getIndices(int array[][3], const int &element, int &i, int &j) {
	const int *ref   = (int *) &element;
	const int *first = (int *) array;
	const ptrdiff_t res = ref - first;

	j = res % 3;
	i = res / 3;
}

int main() {
	int      array[5][3];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			int ci = -1;
			int cj = -1;
			getIndices(array, array[i][j], ci, cj);
			std::cout
					<< "(" << i << ", " << j << ") "
					<< "(" << ci << ", " << cj << ") "
					<< ((i == ci) && (j == cj))
					<< std::endl;
		}
	}
	return 0;
}
