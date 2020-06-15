#include <math.h>
#include <stdio.h>

double atof(char s[]);

void main() {
	printf("%f\n", atof("123.45e-6"));
	printf("%f\n", atof("123.45"));
	printf("%f\n", atof("123.45E+6"));
}

double atof(char s[])
{
	double val, power;
	int i, sign;
	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}

	double result = sign * val / power;

	if (s[i] == 'E' || s[i] == 'e') {
		i++;

		char eSign = (s[i] == '-') ? -1 : 1;
		i++;

		int eValue = 1;
		for (eValue = 0; isdigit(s[i]); i++)
			eValue = 10.0 * eValue + (s[i] - '0');

		double ePower = pow(10, eValue);

		if (eSign > 0) {
			result = result * ePower;
		}
		else {
			result = result / ePower;
		}
	}

	return result;
}