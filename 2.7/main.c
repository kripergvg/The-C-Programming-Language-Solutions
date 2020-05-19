#include <stdio.h>

int invert(int number, int start, int bitsCount);
void printBinary(int number);

void main() {
	int number = 0xA6A; // 1010 0110 1010
	int start = 8;
	int bitsCount = 4;
	int inverted = invert(number, start, bitsCount);
	printBinary(inverted);
}

int invert(int number, int start, int bitsCount) {
	int invertedBits = ~number & ~(~0 << start) & (~0 << (start - bitsCount));
	int clearedNumber = number & ((~0 << start) | ~(~0 << start - bitsCount));
	return clearedNumber | invertedBits;
}


void printBinary(int number) {
	for (size_t i = 0; i < sizeof(int) * 8; i++)
	{
		printf("%d", (number >> (sizeof(int) * 8 - i - 1)) & 1);
	}

	printf("\n");
}