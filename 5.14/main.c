#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

char* lineptr[MAXLINES];

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);

void qsort(void* lineptr[], int left, int right, int(*comp)(void*, void*));

int numcpm(char*, char*);
char* alloc(int);
int getline(char s[], int lim);

main(int arg_count, char* args[]) {
	int nlines;
	int numeric = 0;
	int reverse = 0;

	if (arg_count > 1 ) {

		for (int i = 1; i < arg_count; i++)
		{
			if (strcmp(args[i], "-n") == 0) {
				numeric = 1;
			}
			else if (strcmp(args[i], "-r") == 0) {
				reverse = 1;
			}
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1, (int(*) (void*, void*)) (numeric ? numcpm : strcmp), reverse);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char* allocp = allocbuf; /* next free position */

char* alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}
void afree(char* p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

void writelines(char* lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

#define MAXLEN 1000
int readlines(char* lineptr[], int maxlines)
{
	int len, nlines;
	char* p, line[MAXLEN];
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

int getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void qsort(char* v[], int left, int right, int (*comp)(void*, void*), int reverse) {
	int i, last;
	void swap(char* v[], int, int);

	if (left >= right) {
		return;
	}

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
	{
		if (reverse) {
			if ((*comp)(v[i], v[left]) > 0) {
				swap(v, ++last, i);
			}
		}
		else {
			if ((*comp)(v[i], v[left]) < 0) {
				swap(v, ++last, i);
			}
		}
	}

	swap(v, left, last);
	qsort(v, left, last - 1, comp, reverse);
	qsort(v, last + 1, right, comp, reverse);
}

void swap(char* v[], int i, int j) {
	char* temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int numcpm(char* s1, char* s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2) {
		return -1;
	}
	else if (v1 > v2) {
		return 1;
	}
	else {
		return 0;
	}
}