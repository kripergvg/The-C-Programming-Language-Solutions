#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

void main() {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)
	{
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;

		case '+':
			push(pop() + pop());
			break;

		case '*':
			push(pop() * pop());
			break;

		case '-':
			op2 = pop();
			push(pop() - op2);
			break;

		case '/':
			op2 = pop();
			if (op2 != 0.0) {
				push(pop() / op2);
			}
			else {
				printf("error: zero division\n");
			}

			break;

		case '%':
			op2 = pop();
			if (op2 != 0.0) {				
				push(fmod(pop(), op2));
			}
			else {
				printf("error: zero division\n");
			}
			break;

		case '\n':
			printf("\t%.8g\n", pop());
			break;

		default:
			printf("error: unknown command\n");
		}
	}

	return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	}
	else {
		printf("error: stack is full\n");
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	}
	else {
		printf("error: stack is empty\n");
		return 0;
	}
}

int getch(void);
void ungetch(int);
/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	i = 0;
	if (!isdigit(c) && c != '.') {
		if (c == '-') {
			int nextChar = getch();
			if (!isdigit(nextChar)) {

				ungetch(nextChar);
				return c; /* not a number */
			}
			else {
				// negative number
				s[++i] = nextChar;
			}
		}
		else {
			return c; /* not a number */
		}
	}

	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()));
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetc: too many");
	}
	else {
		buf[bufp++] = c;
	}
}