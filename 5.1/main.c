#include <stdio.h>
#include "getint.h"

#define SIZE 1024

void main() {
	int n, array[SIZE];
	for (n = 0; n < SIZE; n++) {
		int status = getint(&array[n]);
		if (status > 0) {
			printf("%d \n", *(array + n));
		}
	}
}