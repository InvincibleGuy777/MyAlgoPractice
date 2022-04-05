#include<bits/stdc++.h>
//#define DEBUG
using namespace std;

int N;
int A[25];
vector<int> G[25];

int f[25];
int s[25];  // s[i] - 从i出发时最优路径的下一个地窖标号 
int main(){
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	#endif
	scanf("%d", &N);
	for (int i=1; i<=N; ++i){
		scanf("%d", &A[i]);
	}
	for (int i=1; i<=N-1; ++i){
		for (int j=i+1; j<=N; ++j){
			int num;
			scanf("%d", &num);
			if(num){
				G[i].push_back(j);
			}
		}
	}
	memset(f, 0, sizeof(f));
	memset(s, -1, sizeof(s));
	/*
		f[i] - 从i出发最多挖的地雷数目
		BASE: f[N] = A[N]
		STE: f[i] = max(f[j]) + A[i]  if hasEdge(i, j)
		ANS: max(f[i])
	*/
	f[N] = A[N]; 
	for (int u=N-1; u>=1; --u){
		f[u] = A[u];
		for (auto v: G[u]){
			if(f[v] + A[u] > f[u]){
				f[u] = f[v] + A[u];
				s[u] = v;
			}
		}
	}
	int ans = 0;
	int j = 0;
	for (int i=1; i<=N; ++i){
		if(ans < f[i]){
			ans = f[i];
			j = i;
		}
	}
	printf("%d", j);
 	while (s[j] != -1){
		printf(" %d", s[j]);
		j = s[j];
	}
	printf("\n");
	printf("%d\n", ans);
	return 0;
}
