#include <stdio.h>

#define MAXLINE 1000

void printBinary(int number);
unsigned int setbits(unsigned int replacedNumber, unsigned int start, unsigned int bitsCount, unsigned int replacingFrom);

void main() {
	unsigned int replacedNumber = 4015; //1111_1010_1111
	unsigned int start = 8;
	unsigned int bitsCount = 4;
	unsigned int replacingFrom = 17; //0001_0001
	unsigned int changedNumber = setbits(replacedNumber, start, bitsCount, replacingFrom);
	printBinary(changedNumber);
} 


void printBinary(int number) {
	for (size_t i = 0; i < sizeof(int) * 8; i++)
	{
		printf("%d", (number >> (sizeof(int) * 8 - i - 1)) & 1);
	}

	printf("\n");
}

unsigned int setbits(unsigned int replacedNumber, unsigned int start, unsigned int bitsCount, unsigned int replacingFrom) {
	int clearMask = (~0 << start) | ~((~0 << (start - bitsCount)));
	int clearedNumber = replacedNumber & clearMask;
	int copyMask = (~0 << start - bitsCount) & ~(~0 << start);
	int copyBits = replacingFrom & copyMask;
	return clearedNumber | copyBits;
}