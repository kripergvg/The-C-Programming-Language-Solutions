#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define OPERATION '1'

double lastPrinted;

int getop(char[]);
void push(double);
double pop(void);
void print();
void swap();
void clear();

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
		case OPERATION: {
			if (strcmp(s, "sin") == 0) {
				push(sin(pop()));
			}
			if (strcmp(s, "exp") == 0) {
				push(exp(pop()));
			}
			if (strcmp(s, "pow") == 0) {
				int power = pop();
				push(pow(pop(), power));
			}
			else if (strcmp(s, "swap") == 0) {
				swap();
			}
			else if (strcmp(s, "clear") == 0) {
				clear();
			}
			else if (strcmp(s, "print") == 0) {
				print();
			}
			else if (strcmp(s, "+") == 0) {
				push(pop() + pop());
			}
			else if (strcmp(s, "*") == 0) {
				push(pop() * pop());
			}
			else if (strcmp(s, "-") == 0) {
				op2 = pop();
				push(pop() - op2);
			}
			else if (strcmp(s, "/") == 0) {
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				}
				else {
					printf("error: zero division\n");
				}
			}
			else if (strcmp(s, "%") == 0) {
				op2 = pop();
				if (op2 != 0.0) {
					push(fmod(pop(), op2));
				}
				else {
					printf("error: zero division\n");
				}
			}
			else if (strcmp(s, "\n") == 0) {
				printf("\t%.8g\n", pop());
			}
			else if (s[0] == '$') {
				if (s[1] == 'l') {
					push(lastPrinted);
				}
			}
			break;
		}

		default:
			printf("error: unknown command\n");
		}
	}

	return 0;
}

#define MAXVAL 100
int stackPointer = 0;
double stack[MAXVAL];

void push(double f) {
	if (stackPointer < MAXVAL) {
		stack[stackPointer++] = f;
	}
	else {
		printf("error: stack is full\n");
	}
}

double pop(void) {
	if (stackPointer > 0) {
		return stack[--stackPointer];
	}
	else {
		printf("error: stack is empty\n");
		return 0;
	}
}

void print() {
	if (stackPointer > 0) {
		lastPrinted = stack[stackPointer - 1];
		printf("%g \n", lastPrinted);
	}
}

void swap() {
	if (stackPointer == 2) {
		double temp = stack[0];
		stack[0] = stack[1];
		stack[1] = temp;
	}
}

void clear() {
	stackPointer = 0;
}

int getch(void);
void ungetch(int);
/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t');

	i = 0;
	if (!isdigit(c) && c != '.') {
		if (c == EOF) {
			return EOF;
		}else if (c == '-') {
			int nextChar = getch();
			if (!isdigit(nextChar)) {

				ungetch(nextChar);
				return OPERATION; /* not a number */
			}
			else {
				// negative number
				s[++i] = nextChar;
			}
		}
		else {
			while (!isdigit(c) && c != ' ' && c != EOF && c!= '\n') {
				s[++i] = c = getch();
			}
			ungetch(c);
			s[i] = '\0';
			return OPERATION; /* not a number */
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

void ungets(char s[]) {
	char symbol;
	while ((symbol = getchar()) != '\0')
	{
		ungetch(symbol);
	}
}