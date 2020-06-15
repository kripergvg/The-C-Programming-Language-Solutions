#include <stdio.h> 

char convertToSymbol(int number);
void itob(int number, char converted[], unsigned int base);

void main() {
	char buffer[1000];
	itob(10, buffer, 16);
}

void itob(int number, char converted[], unsigned int base) {
	unsigned int index = 0;

	while (number >=base)
	{
		int remainder = number % base;
		number /= base;

		converted[index] = convertToSymbol(remainder);
		index++;
	}

	converted[index] = convertToSymbol(number);
	for (int i = index; i >= 0; i--)
	{
		putchar(converted[i]);
	}
}

char convertToSymbol(int number) {
	char bigDigigts[] = "ABCDEF";

	if (number <= 9) {
		return number + '0';
	}
	else {
		int bigDigigtsIndex = number - 10;
		return bigDigigts[bigDigigtsIndex];
	}
}