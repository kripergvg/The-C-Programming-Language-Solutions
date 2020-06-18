#include <stdio.h>

char strend(char* s, char* t);

void test1() {
	char s[] = "abcd";
	char t[] = "cd";
	char result = strend(s, t);
	printf("%d \n", result);
}

void test2() {
	char s[] = "abcd";
	char t[] = "dc";
	char result = strend(s, t);
	printf("%d \n", result);
}

void main() {
	test1();
	test2();
}

char strend(char* s, char* t) {
	char* sSymbol = s;
	while (*sSymbol) {
		sSymbol++;
	}
	int sCount = sSymbol + 1 - s;

	char* tSymbol = t;
	while (*tSymbol)	{
		tSymbol++;
	}
	int tCount = tSymbol + 1 - t;

	int processedCount = 0;
	while (sCount - processedCount > 0 && tCount - processedCount > 0)
	{
		if (*sSymbol != *tSymbol) {
			return 0;
		}

		tSymbol--;
		sSymbol--;
		processedCount++;
	}

	return 1;
}