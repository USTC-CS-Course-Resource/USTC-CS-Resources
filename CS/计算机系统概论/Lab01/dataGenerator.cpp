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
	int* scores = new int(n);
	fprintf(stdout, "\t.ORIG\t\tx3200\n");
	fprintf(f, "\t.ORIG\t\tx3200\n");
	for(int i = 0; i < n; i++){
		temp = rand()%100;
		bool flag = 1;
		while(flag) {
			int j;
			for(j = 0; j < i; j++) {
				if(scores[j] == temp){
					temp = rand()%100;
					break;
				}
			}
			if(j == i)
				flag = 0;
		}
		scores[i] = temp;
		fprintf(stdout, "\t.FILL\t\t#%d\n", temp);
		fprintf(f, "\t.FILL\t\t#%d\n", temp);
	}
	fprintf(f, "\t.END\n");
	fprintf(stdout, "\t.END\n");
	
	int grades[4] = {0};
	sort(scores, scores+n, cmp);
	for(int i = 0; i < n; i++){
		if(scores[i] >= 75) {
			if(scores[i] >= 85 && i < n*0.3)
				grades[0]++;
			else if(i < n*0.5)
				grades[1]++;
		}
		else if(scores[i] < 60)
			grades[3]++;
		else
			grades[2]++;
		printf("%x\n", scores[i]);
	}
	fprintf(f, "; As:%d\tBs:%d\tCs:%d\tDs%d\n", grades[0], grades[1], grades[2], grades[3]);
	fprintf(stdout, "; As:%d\tBs:%d\tCs:%d\tDs%d\n", grades[0], grades[1], grades[2], grades[3]);
	fclose(f);
}
