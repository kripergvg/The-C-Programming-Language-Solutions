#include <stdio.h>

int rightrot(int number, unsigned int bitCount);
void printBinary(int number);

void main() {
	int number = 0xA6A; // 1010 0110 1010
	unsigned int bitCount = 4;
	printBinary(rightrot(number, bitCount));
}

int rightrot(int number, unsigned int bitCount) {
	int dropped_bits = number & ~(~0 << bitCount);
	int shifted_bits = dropped_bits << (sizeof(unsigned int) * 8 - bitCount);
	return (number >> bitCount) | shifted_bits;
}

void printBinary(int number) {
	for (size_t i = 0; i < sizeof(int) * 8; i++)
	{
		printf("%d", (number >> (sizeof(int) * 8 - i - 1)) & 1);
	}

	printf("\n");
}