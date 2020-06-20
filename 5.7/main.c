#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char* lineptr[MAXLINES];
char* lines_storage[MAXLINES * MAXLEN];

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);

void qsort(char* lineptr[], int left, int right);

int main() {
	int nlines = readlines(lineptr, MAXLINES, lines_storage);
	if (nlines >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

int getline(char*, int);
char* alloc(int);

int readlines(char* lineptr[], int maxlines, char* lines_storage) {
	int len;
	int nlines;

	char line[MAXLEN];

	nlines = 0;
	len = getline(line, MAXLEN);
	while (len > 0)
	{
		if (nlines >= maxlines) {
			return -1;
		}
		else {
			line[len - 1] = '\0';
			strcpy(lines_storage, line);
			lineptr[nlines++] = lines_storage;
			lines_storage += len;
		}

		len = getline(line, MAXLEN);
	}

	return nlines;
}

void writelines(char* lineptr[], int nlines) {
	for (int i = 0; i < nlines; i++)
	{
		printf("%s\n", lineptr[i]);
	}
}

void qsort(char* v[], int left, int right) {
	int i, last;
	void swap(char* v[], int i, int j);

	if (left >= right) {
		return;
	}

	swap(v, left, (left + right) / 2);
	last = left;

	for (int i = left+1; i <= right; i++)
	{
		if (strcmp(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}

	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void swap(char* v[], int i, int j) {
	char* temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}