//本题算法来源 https://wenku.baidu.com/view/08325b1652d380eb62946d59.html 

#include<stdio.h>

void PrintSquare(int N);
void Change(int* x, int* y);
void OddNumSolution(int n, int a[n][n], int from);

int main(){
	int N;
	printf("请输入想计算的幻方阶数： ");
	scanf("%d", &N);
	PrintSquare(N);
} 

void PrintSquare(int N){
	//打印结果 
	int a[N][N];
	int b[N*N]; 
	int i, j, index = N*N-1;
	int m = ((N/2)-1)/2;
	//处理奇数阶
	if(N % 2 == 1) OddNumSolution(N, a, 1);
	//处理单偶数阶
	else if((N/2) % 2 == 1){
		int A[N/2][N/2]; OddNumSolution(N/2, A, 1);
		int B[N/2][N/2]; OddNumSolution(N/2, B, N*N/4 + 1);
		int C[N/2][N/2]; OddNumSolution(N/2, C, 2*N*N/4 + 1);
		int D[N/2][N/2]; OddNumSolution(N/2, D, 3*N*N/4 + 1);
		
		for(i = 0; i < N/2; i++){
			for(j = 0; j < m; j++){
				Change(&A[i][j], &D[i][j]);
			}
			j = 0;
		}
		Change(&A[m][0], &D[m][0]);
		Change(&A[m][m], &D[m][m]);
		
		for(i = 0; i < N/2; i++){
			for(j = N/2-1; j > N/2-m; j--){
				Change(&A[i][j], &D[i][j]);
			}
			j = 0;
		}
		
		for(i = 0; i < N/2; i++){
			for(j = 0; j < N/2; j++){
				a[i][j] = A[i][j];
			}
		}
		for(i = 0; i < N/2; i++){
			for(j = 0; j < N/2; j++){
				a[i+N/2][j+N/2] = B[i][j];
			}
		}
		for(i = 0; i < N/2; i++){
			for(j = 0; j < N/2; j++){
				a[i][j+N/2] = C[i][j];
			}
		}
		for(i = 0; i < N/2; i++){
			for(j = 0; j < N/2; j++){
				a[i+N/2][j] = D[i][j];
			}
		}
		
	}
	//处理双偶数阶
	else if((N/2) % 2 == 0){
		//步骤② 
		for(i = 0; i < N/2; i++){
			a[i][i] = -1;
			a[i][N/2-1-i] = -1;
		}
		for(i = 0; i < N/2; i++){
			a[i][i+N/2] = -1;
			a[i][N-i-1] = -1;
		}
		for(i = 0; i < N/2; i++){
			a[i+N/2][i] = -1;
			a[i+N/2][N/2-1-i] = -1;
		
		}
		for(i = 0; i < N/2; i++){
			a[i+N/2][i+N/2] = -1;
			a[i+N/2][N-1-i] = -1;
		}
		//步骤③ 
		for(i = 1; i <= N*N; i++){
			b[i-1] = i;
		}
		for(i = 1; i <= N*N; i++){
			if(a[i/N][i%N-1] != -1){
				b[i-1] = 0;
				a[i/N][i%N-1] = i;
			}
		}
		//步骤④ 
		for(i = 1; i <= N*N; i++){
			if(a[i/N][i%N-1] == -1){
				while(b[index] == 0){
					index--;
				}
				a[i/N][i%N-1] = b[index];
				index--;
			}
		}
		
	}
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d\t", a[i][j]);
		}
		j = 0;
		printf("\n\n");
	}
}

//奇数阶处理
void OddNumSolution(int n, int a[n][n], int from){
	int i = n-1, j = (n-1)/2, k = from;
	for(; k <= n*n + from - 1; k++){
		if((k % n) != 1){
			i--; j++;
			if(i < 0) i += n; 
			if(j > n-1) j -= n; 
			a[i][j] = k;
		}else{
			i++;
			if(i > n-1) i -= n; 
			if(j > n-1) j -= n; 
			a[i][j] = k;
		}
	}
}	

void Change(int* x, int* y){
	int k = *x;
	*x = *y;
	*y = k;
}
