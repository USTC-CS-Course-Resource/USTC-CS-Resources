#include<stdio.h>

int main(){
	char encrypt(char c);
	char c1 = 'C';
	char c2 = 'h';
	char c3 = 'i';
	char c4 = 'n';
	char c5 = 'a';
	printf("用putchar输出的结果：\t"); 
	putchar(encrypt(c1));
	putchar(encrypt(c2));
	putchar(encrypt(c3));
	putchar(encrypt(c4));
	putchar(encrypt(c5));
	printf("\n用printf输出的结果：\t%c%c%c%c%c", encrypt(c1), encrypt(c2), encrypt(c3), encrypt(c4), encrypt(c5));
	return 0;
} 

char encrypt(char c) {
	if(c >=65 && c <= 90){
		return (c - 64 + 4) % 26 + 64;
	}else if(c >= 97 && c <= 122){
		return (c - 97 + 4) % 26 + 97;
	}else{
		return c;
	}
}//传入一个英文字母，返回它的加密结果 ;若不是英文字母，则返回它本身 
