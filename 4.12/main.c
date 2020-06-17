#include <stdio.h>

void main() {
	int number_raw = 6531;
	char number_converted[1024];
	unsigned int symbol_count = itoa(number_raw, number_converted);
	for (unsigned int i = 0; i < symbol_count; i++)
	{
		putchar(number_converted[i]);
	}
}

unsigned int itoa(int number, char *buffer) {
	if (number < 10) {
		*buffer = number + '0';
		return 1;
	}

	int reminder = number % 10;
	number = number / 10;

	unsigned int index = itoa(number, buffer);
	*(buffer + index) = reminder + '0';
	return index + 1;
}