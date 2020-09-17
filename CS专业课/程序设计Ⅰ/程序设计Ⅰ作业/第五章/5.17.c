#include<stdio.h>

int main()
{
	int a = 0, b = 0, c = 0, flag = 0; //用i, j, k 表示A, B, C；用0, 1, 2 表示X, Y, Z 
	for(a = 0; a < 3; a++)
	{//遍历6种情况 
		for(b = 0; b < 3; b++)
		{
		//	if(a == b) break;
			c = 3-a-b;
			if(a != b && a != c && b != c)
			{
				if(a != 0 && c != 0 && c != 2) 
				{//题目的条件 
					flag = 1;
					break;
				}
			}
		}
		if(flag == 1) {
			printf("A对%c\n", 'X' + a);
			printf("B对%c\n", 'X' + b);
			printf("C对%c\n", 'X' + c);
			flag = 0;
		} 
	}
	

} 






























/*
char add(char x);

int main(){
	char A, B, C;
	int flag = 0;
	for(A = 'X';; A++){
		for(B = add(A); B != A; B = add(B)){
			C = 'X' + 'Y' + 'Z' - A - B; //通过循环语句对A, B, C分别赋值为A, B, C的所有排列 
			if(A != 'X' && C != 'X' && C != 'Z') flag = 1;
			if(flag == 1) break;
		}
		if(flag == 1) break;
	}
	if(flag == 1){
		printf("A对%c\n", A);
		printf("B对%c\n", B);
		printf("C对%c\n", C);
	}else printf("没有找到合适的结果");
	return 0;
} 

char add(char x){
	return x == 'Z' ? 'X' : (x+1);
}
*/
//傻逼方法 
