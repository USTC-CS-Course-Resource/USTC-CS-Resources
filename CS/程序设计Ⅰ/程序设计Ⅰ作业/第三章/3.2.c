#include<stdio.h>
#include<math.h>
int main(){
	float total;
	printf("1000元，存5年\n存款方式有：\n1.一次存5年期； \n");
	printf("2.先存2年期，到期后将本息再存3年期 \n");
	printf("3.存3年期，到期后将本息再存2年期 \n");
	printf("4.存一年期，到期后将本息再存1年期，连续存5次 \n");
	printf("5.存活期存款。活期利息每季度结算一次 \n\n");
	
	total = 1000 * (1 + 5*0.0414);
	printf("通过方式1存款，5年后本息和为：%f; 其中利息为：%f\n", total, total -1000);
	total = 1000 * (1 + 2*0.0468) * (1 + 3*0.054);
	printf("通过方式2存款，5年后本息和为：%f; 其中利息为：%f\n", total, total -1000);
	total = 1000 * (1 + 3*0.054) * (1 + 2*0.0468);
	printf("通过方式3存款，5年后本息和为：%f; 其中利息为：%f\n", total, total -1000);
	total = 1000 * pow(1 + 1*0.0414, 5);
	printf("通过方式4存款，5年后本息和为：%f; 其中利息为：%f\n", total, total -1000);
	total = 1000 * pow(1 + 0.0072/4, 4*5);
	printf("通过方式5存款，5年后本息和为：%f; 其中利息为：%f\n", total, total -1000);
	return 0; 
}

/*int main() {
	int choice;
	float total;
	printf("1000元，存5年\n存款方式有：\n1.一次存5年期； \n"); 
	printf("2.先存2年期，到期后将本息再存3年期； \n");
	printf("3.存3年期，到期后将本息再存2年期； \n");
	printf("4.存一年期，到期后将本息再存1年期，连续存5次； \n");
	printf("5.存活期存款。活期利息每季度结算一次。 \n\n");
	printf("请输入存款方式代号：");
	scanf("%d", &choice);
	switch(choice){
		case 1: total = 1000 * (1 + 5*0.0414); break;
		case 2: total = 1000 * (1 + 2*0.0468) * (1 + 3*0.054); break;
		case 3: total = 1000 * (1 + 3*0.054) * (1 + 2*0.0468); break;
		case 4: total = 1000 * pow(1 + 1*0.0414, 5); break;
		case 5: total = 1000 * pow(1 + 0.0072/4, 4*5); break;
		default: printf("存款方式选择错误"); 
	}
	printf("通过方式%d存款，5年后本息和为：%f; 其中利息为：%f\n", choice, total, total - 1000);
	man();
	return 0;
}
*/
