#include<stdio.h>
#include<stdlib.h>

struct dates{
	int year;
	int month;
	int day;
};
typedef struct dates dates;
int days( dates *date);

int main()
{
	dates *date = malloc(sizeof(dates));
	printf("输入年:");
	scanf("%d", &(date->year));
	printf("输入月:");scanf("%d", &(date->month));
	printf("输入日:");	scanf("%d", &(date->day));
	printf("计算结果为：%d", days(date));
	return 0;
} 

int days(dates *date)
{

	int alldays;
	if(date->month < 8)
	{
		if(date->month % 2 == 0)
			alldays = 61*(date->month/2) - 30 + date->day;
		else
			alldays = 61*(date->month-1)/2 + date->day;
	}
	else
	{
		if(date->month % 2 == 0)
			alldays = 214 + 61*((date->month-8)/2) + date->day;
		else
			alldays = 214 + 61*((date->month-7)/2) - 30 + date->day;
	}
	if(date->month >= 2)
	{
		if((date->year%400 == 0) || (date->year%4 == 0 && date->year%100 != 0))
			alldays -= 1;
		else
			alldays -= 2;
	}
	return alldays;
}


