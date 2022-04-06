#include<bits/stdc++.h>
using namespace std;
//#define DEBUG

const int maxn = 105;
const int d[5] = {0, 1, 0, -1, 0};
int R, C;

int dp[maxn][maxn];
int h[maxn][maxn];
vector<int> G[maxn*maxn];

// 从x,y出发的最大长度 
int memo(int x, int y){
	int& ans = dp[x][y];
	if(ans > 0)
		return ans;
	int u = x * C + y;
	ans = 1; 
	for (int v: G[u]){
		int mx = v / C, my = v % C;
		ans = max(ans, memo(mx, my) + 1);
	} 
	return ans;
}

int main(){
	int tCase = 1;
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	#endif	
	while (tCase--){
		scanf("%d%d", &R, &C);
		memset(h, 0, sizeof(h));
		for (int i=0; i<R; ++i){
			for (int j=0; j<C; ++j){
				scanf("%d", &h[i][j]);
			}
		}
		// build graph
		for (int i=0; i<R; ++i){
			for (int j=0; j<C; ++j){
				int idx = i * C + j;
				for (int k=0; k<4; ++k){
					int mx = i + d[k], my = j + d[k+1];
					if(mx < 0 || mx >= R || my < 0 || my >= C){
						continue;
					}
					if(h[i][j] > h[mx][my]){
						G[idx].push_back(mx * C + my);	
					}										
				}
			}
		}
		memset(dp, 0, sizeof(dp));
		int maxn = 0;
		for (int i=0; i<R; ++i){
			for (int j=0; j<C; ++j){
				maxn = max(maxn, memo(i, j));
			}
		}	
		printf("%d\n", maxn);	
	}
	return 0;
}
