#include <stdio.h>

void main() {
	unsigned int x = 0xA; //1010
	printf("%d", bitscount(x));
}

int bitscount(unsigned int x) {
	unsigned int bit_count = 0;
	while (x != 0)
	{
		x &= x - 1;
		bit_count++;
	}

	return bit_count;
}