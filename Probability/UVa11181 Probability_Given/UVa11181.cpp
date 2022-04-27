#include<bits/stdc++.h>
using namespace std;
#define DEBUG

const int maxn = 25;

typedef double elem;
elem p[maxn];
elem sumv[maxn];
int N, r;

void dfs(int i, int j, int mask, elem& tot){
	if(i >= N){
		if(j == r){
			elem cur = 1;
			for (int i=0; i<N; ++i){
				if(mask & (1<<i)){
					cur *= p[i];				
				}
				else{
					cur *= 1.0 - p[i];
				}
			}
			tot += cur;
			for (int i=0; i<N; ++i){
				if(mask & (1<<i)){
					sumv[i] += cur;
				}
			}	
			//cout<<"tot: "<<tot<<endl;
		}
		return;
	}
	else if(j > r || N - i < r - j)
		return;
	dfs(i+1, j, mask, tot);  // µÚiÈË²»¹ºÂò
	dfs(i+1, j+1, mask | 1<<i, tot);
}

void solve(){
	elem tot = 0;
	for (int i=0; i<N; ++i){
		sumv[i] = 0;
	}
	dfs(0, 0, 0, tot);
	
	// output
	for (int i=0; i<N; ++i){
		printf("%.6f\n", sumv[i] / tot);
	}
}

int main(){	
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	int tCase = 1;
	while (scanf("%d%d", &N, &r) == 2 && (N || r)){
		printf("Case %d:\n", tCase++);
		for (int i=0; i<N; ++i){
			scanf("%lf", &p[i]);
		}
		solve();
	}
	return 0;
} 
