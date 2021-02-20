#include<stdio.h>
#include<math.h> 
int main() {
	float d = 300000;
	float p = 6000;
	float r = 0.01;
	float month;
	month = (log(p/(p-d*r)))/log(1 + r) ;
	printf("%.1f月能还清", month);
	return 0; 
} 
