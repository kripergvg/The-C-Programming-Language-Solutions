#include<stdio.h>

void strncpy(char* destination, char* source, int count);
void strncat(char* destination, char* source, int count);
int strncmp(char* comparable1, char* comparable2, int count);

void main() {
	char copySource[] = "abcdef";
	char copyDestination[] = "xxxxxxx";
	strncpy(copyDestination, copySource, 3);
	printf("%s \n", copyDestination);

	char catSource[] = "ef";
	char catDestination[1000] = "abcd";
	strncat(catDestination, catSource, 2);
	printf("%s \n", catDestination);

	char* comparable1 = "abcdAAAA";
	char* comparable2 = "abcdBBBB";
	char result1 = strncmp(comparable1, comparable2, 4);
	char result2 = strncmp(comparable1, comparable2, 5);
	printf("%d %d\n", result1, result2);
}

void strncpy(char* destination, char* source, int count) {
	for (int i = 0; i < count; i++)
	{
		*(destination + i) = *(source + i);
	}
}

void strncat(char* destination, char* source, int count) {
	char* lastDestinationSymbol = destination;
	while (*lastDestinationSymbol) {
		lastDestinationSymbol++;
	}

	for (int i = 0; i < count; i++)
	{
		*(lastDestinationSymbol + i) = *(source + i);
	}
}

int strncmp(char* comparable1, char* comparable2, int count) {

	for (int i = 0; i < count; i++)
	{
		if (*(comparable1 + i) != *(comparable2 + i)) {
			int diff = *(comparable1 + i) - *(comparable2 + i);
			if (diff > 0) {
				return 1;
			}
			else {
				return-1;
			}
		}
	}

	return 0;
}