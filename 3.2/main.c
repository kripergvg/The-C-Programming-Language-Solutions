#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

void main() {
	char s[MAXLINE];
	char t[MAXLINE] = "\ttest\n\t\n";
	escape(s, t);
	unescape(s, t);
}

void escape(char s[], char t[]) {
	int symbol;
	int sIndex = 0;
	int tIndex = 0;

	while (1)
	{
		symbol = t[tIndex];

		switch (symbol)
		{
			case '\n':
				s[sIndex] = '\\';
				s[sIndex + 1] = 'n';
				sIndex += 2;
				break;
			case '\t':
				s[sIndex] = '\\';
				s[sIndex + 1] = 't';
				sIndex += 2;
				break;
			case '\0':
				s[sIndex] = symbol;
				sIndex++;
				return;
			default:
				s[sIndex] = symbol;
				sIndex++;
				break;
		}

		tIndex++;
	}
}

void unescape(char s[], char t[]) {

	unsigned int index = 0;

	char escape = 0;
	while (1)
	{
		char symbol = s[index];

		switch (symbol)
		{
		case '\0':
			return;
		case '\\':
			escape = 1;
			break;
		default:
			if (escape) {
				switch (symbol)
				{
				case 't':
					t[index] = '\t';
					break;
				case 'n':
					t[index] = '\n';
					break;
				default:
					break;
				}

				escape = 0;
			}
			else {
				t[index] = symbol;
			}

			break;
		}

		index++;
	}
}