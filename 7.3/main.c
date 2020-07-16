#include <stdarg.h>
#include <stdio.h>

void minprintf(char* fmt, ...);

void main() {
	int n = 10;
	minprintf("%d %s %c %p", 12, "teststring", 'a', (void*)&n);
}

void minprintf(char* fmt, ...) {
	va_list ap;
	char* p, * sval;
	int ival;
	double dval;
	char charval;
	void* pointerval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++)
	{
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		switch (*++p)
		{
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for (sval= va_arg(ap, char*); *sval; sval++)
			{
				putchar(*sval);
			}
			break;
		case 'c':
			charval = va_arg(ap, char);
			putchar(charval);
			break;
		case 'p':
			pointerval = va_arg(ap, void*);
			printf("%p", pointerval);
			break;
		default:
			putchar(*p);
			break;
		}
	}

	va_end(ap);
}