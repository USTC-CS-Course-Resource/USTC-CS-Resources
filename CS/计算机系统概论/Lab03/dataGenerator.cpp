#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int cmp(int a, int b){
	return b < a;
}

int main() {
	FILE* f = fopen("data.asm", "w");
	srand((unsigned)time(NULL)); //将系统时间作为随机种子 
	int n, temp;
	cin >> n;
	fprintf(stdout, "\t.ORIG\t\tx3200\n");
	fprintf(f, "\t.ORIG\t\tx3200\n");
	for(int i = 0; i < n; i++){
		temp = rand()%0x7fff;
		fprintf(stdout, "\t.FILL\t\t#%d\t;%d\n", temp, i);
		fprintf(f, "\t.FILL\t\t#%d\n", temp);
	}
	fprintf(f, "\t.FILL\t\t#-1\n");
	fprintf(stdout, "\t.FILL\t\t#-1\n");
	fprintf(f, "\t.END\n");
	fprintf(stdout, "\t.END\n");
	
	fclose(f);
}
