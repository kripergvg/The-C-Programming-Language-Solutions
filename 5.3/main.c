#include <stdio.h>

void strcat(char* s, char* t);

void main() {

	char input[1000] = "AAA";
	char contactable[] = "BBBB";
	strcat(input, contactable);
	printf("%s", input);
	
}

void strcat(char* s, char* t) {

	while (*s!='\0')
	{
		s++;
	}

	while (*s++ = *t++);
}