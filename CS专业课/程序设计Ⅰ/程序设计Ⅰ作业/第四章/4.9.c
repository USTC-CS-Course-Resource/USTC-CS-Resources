#include<stdio.h>

int main(){
	int x0, x1, x2, x3, x4, x;
	int n = 0; //表示位数
	printf("请输入一个不多于五位数的正整数： ");
	scanf("%d", &x);
	if(x > 0 && x <100000){
		x4 = x%10;
		x = (x - x4)/10;
		if(x == 0 && n == 0) n = 1;
		x3 = x%10;
		x = (x - x3)/10;
		if(x == 0 && n == 0) n = 2;
		x2 = x%10;
		x = (x - x2)/10;
		if(x == 0 && n == 0) n = 3;
		x1 = x%10;
		x = (x - x1)/10;
		if(x == 0 && n == 0) n = 4;
		x0 = x%10;
		x = (x - x0)/10;
		if(x == 0 && n == 0) n = 5;//将x的个、十、百、千、万位分别赋值到 x4,x3,x2,x1,x0 ; 并且获得位数n 
		
		//①输出位数 
		
		printf("这个数字有 %d 位\n", n); 
		
		//②分别输出每一位的数字 
		switch(n){
			case 5 : printf("该数字万位为： %d\n", x0);
			case 4 : printf("该数字千位为： %d\n", x1);
			case 3 : printf("该数字百位为： %d\n", x2);
			case 2 : printf("该数字十位为： %d\n", x3);
			case 1 : printf("该数字个位为： %d\n", x4);
		}	 
		
		//③按逆序输出各位数字
		printf("按逆序输出各位数字结果应为："); 
		
		switch(n){
			case 5 : printf("%d", x4); printf("%d", x3); printf("%d", x2); printf("%d", x1); printf("%d", x0); break;
			case 4 : printf("%d", x4); printf("%d", x3); printf("%d", x2); printf("%d", x1); break;
			case 3 : printf("%d", x4); printf("%d", x3); printf("%d", x2); break;
			case 2 : printf("%d", x4); printf("%d", x3); break;
			case 1 : printf("%d", x4); break;
		}
		
	}else printf("所输入的数不是不多于5位的正整数");
	return 0;
} 
