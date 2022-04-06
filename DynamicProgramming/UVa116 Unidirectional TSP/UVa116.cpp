#include<bits/stdc++.h>
using namespace std;
//#define DEBUG

int A[15][105];  // 可能为负 
int f[15][105];
int n, m;


// print the minimum path (rows) lexicographically 
void printPath(int i, int j){
	if(j > 0)
		printf(" ");
	printf("%d", i+1);
	if(j == m-1){
		printf("\n");
		return; 
	}
	int v = f[i][j];
	// i-1, i, i+1, 注意循环
	int k[3] = {i-1, i, i+1};
	if(i-1 < 0){
		k[0] += n;
	}
	if(i+1 >= n){
		k[2] -= n;
	} 
	sort(k, k+3);
	for (int x=0; x<3; ++x){
		if(v == f[k[x]][j+1] + A[i][j]){
			printPath(k[x]%n, j+1);
			break;
		}
	}
} 

int main(){
	int tCase = 1;
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	#endif 
	while (scanf("%d%d", &n, &m) == 2 && n && m){
		for (int i=0; i<n; ++i){
			for (int j=0; j<m; ++j){
				scanf("%d", &A[i][j]);
			}
		}
		/*
			f[i][j] - 从第j列开始，位于第i行，所能获得的最小路径和 
			BASE: f[i][m-1] = A[i][m-1]
			STE: f[i][j] = min(f[i][j+1], f[(i+1)%n][j+1], 
			f[(i-1+n)%n][j+1]) + A[i][j]
			ANS: min(f[i][0])
		*/
		for (int i=0; i<n; ++i){
			f[i][m-1] = A[i][m-1];
		}
		for (int j=m-2; j>=0; --j){
			for (int i=0; i<n; ++i){
				f[i][j] = min(f[i][j+1], 
				min(f[(i+1)%n][j+1], f[(i-1+n)%n][j+1])) + A[i][j];
			}
		}
		int minn = INT_MAX, min_i;
		for (int i=0; i<n; ++i){
			if(minn > f[i][0]){
				minn = f[i][0];
				min_i = i;
			}
		}
		printPath(min_i, 0);
		printf("%d\n", minn);
	}
	return 0;
}
