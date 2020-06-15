#include <stdio.h>

int strindex(char string[], char pattern[]);
int getline(char s[], int lim);

void main() {
	char inputText[1000];
	getline(inputText, 1000);

	char pattern[1000];
	getline(pattern, 1000);

	printf("%d", strindex(inputText, pattern));
}

int strindex(char string[], char pattern[]) {
	unsigned int inputIndex = 0;
	int patternIndex = 0;
	unsigned int lastMatchIndex = 0;
	unsigned int fullMatchIndex = -1;
	char symbol;
	while ((symbol = string[inputIndex]) != '\0')
	{
		if (symbol == pattern[patternIndex]) {
			if (patternIndex == 0) {
				lastMatchIndex = inputIndex;
			}
			else if (pattern[patternIndex + 1] == '\0')
			{
				fullMatchIndex = lastMatchIndex;
			}

			patternIndex++;
		}
		else {
			patternIndex = 0;
		}

		inputIndex++;
	}

	return fullMatchIndex;
}

int getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}