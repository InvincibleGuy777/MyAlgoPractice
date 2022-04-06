#include<bits/stdc++.h>
using namespace std;
//#define DEBUG

const int maxn = 55;

int A[maxn];
int f[maxn][maxn*180 + 680];
int ti[maxn][maxn*180 + 680];

int main(){
	int tCase = 1;
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	#endif
	scanf("%d", &tCase);
	int T = 1; 
	while (T<=tCase){
		int n, t;
		scanf("%d%d", &n, &t);
		for (int i=0; i<n; ++i){
			scanf("%d", &A[i]);
		}
		/*
			f[i][t] - 从i个曲目起，剩余时间t，能唱的最大曲目数
			ti[i][t] - 对应的总时间 
			BASE: f[i][0] = 0, f[n][j] = 1, j > 0
			STE: f[i][t] = max(f[i+1][t], f[i+1][t-A[i]] + 1)
			ANS: f[0][t], ti[0][t]
		*/
		memset(f, 0, sizeof(f));
		memset(ti, 0, sizeof(ti));
		for (int j=1; j<=t; ++j){
			f[n][j] = 1;
			ti[n][j] = 678;	
		}
		for (int i=n-1; i>=0; --i){
			for (int j=1; j<=t; ++j){
				f[i][j] = f[i+1][j];
				ti[i][j] = ti[i+1][j];
				if(j >= A[i]){
					if(f[i+1][j-A[i]] + 1 > f[i][j]){
						f[i][j] = f[i+1][j-A[i]] + 1;
						ti[i][j] = ti[i+1][j-A[i]] + A[i];
					}
					else if(f[i+1][j-A[i]] + 1 == f[i][j]){
						if(ti[i+1][j-A[i]] + A[i] > ti[i][j]){
							ti[i][j] = ti[i+1][j-A[i]] + A[i];
						}
					}
				}
			}
		}
		// TODO: print
		printf("Case %d: %d %d\n", T, f[0][t], ti[0][t]);
		T++;
	}
	return 0;
}
