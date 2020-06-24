#include <stdio.h>

#define YEAR_TYPE_COUNT 2
#define MONTH_COUNT 12

static char daytab[YEAR_TYPE_COUNT][MONTH_COUNT + 1] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int* pmonth, int* pday);

void main() {
	int day = day_of_year(2020, 06, 20);
	int month, month_of_day;
	month_day(2020, 172, &month, &month_of_day);

	printf("%d\n", day);
	printf("%d\n", month);
	printf("%d\n", month_of_day);
}


char get_year_type(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int get_max_days_count(int year) {
	static char inited = 0;
	static int days_count[2];

	if (!inited) {
		for (int year_type_index = 0; year_type_index < YEAR_TYPE_COUNT; year_type_index++)
		{
			for (int month_index = 0; month_index < MONTH_COUNT + 1; month_index++)
			{
				days_count[year_type_index] += daytab[year_type_index][month_index];
			}
		}
	}

	char leap = get_year_type(year);
	return days_count[leap];
}

int day_of_year(int year, int month, int day) {
	if (month < 1 || month>MONTH_COUNT) {
		return -1;
	}

	char leap = get_year_type(year);
	char days_count = daytab[leap][month];
	if (day > days_count) {
		return -1;
	}

	for (int i = 1; i < month; i++)
	{
		day += daytab[leap][i];
	}

	return day;
}

void month_day(int year, int yearday, int* pmonth, int* pday) {
	char leap = get_year_type(year);
	int max_days_count = get_max_days_count(year);
	if (yearday > max_days_count) {
		return -1;
	}

	int i;
	for (i = 1; yearday > daytab[leap][i]; i++)
	{
		yearday -= daytab[leap][i];
	}

	*pmonth = i;
	*pday = yearday;
}


char* month_name(int n)
{
	static char name[][2000] = {
	"Illegal month",
	"January", "February", "March",
	"April", "May", "June",
	"July", "August", "September",
	"October", "November", "December"
	};
	return (n < 1 || n > 12) ? name[0] : name[n];
}