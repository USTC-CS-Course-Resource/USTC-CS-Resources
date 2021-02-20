#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int cmp(int a, int b){
	return b < a;
}

int main() {
	FILE* f = fopen("table.asm", "w");
	//fprintf(stdout, "\t.ORIG\t\tx4000\n");
	fprintf(f, "\t.ORIG\t\tx4000\n");
	for(long i = 0; i < 0x8000; i++){
		//fprintf(stdout, "\t.FILL\t\t0x%x\n", i>>1);
		fprintf(f, "\t.FILL\t\t0x%x\n", i>>1);
	}
	//fprintf(stdout, "\t.END\n");
	fprintf(f, "\t.END\n");
	
	fclose(f);
}
