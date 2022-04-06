#include<bits/stdc++.h>
using namespace std;
#define DEBUG

const int INF = INT_MAX;

const int d[5] = {0, 1, 0, -1, 0};
int R, C;

void dfs(const vector<vector<int> >& h, int x, int y, 
vector<vector<bool> >& mark, vector<vector<int> >& dp){
	mark[x][y] = true;
	for (int k=0; k<4; ++k){
		int mx = x + d[k], my = y + d[k+1];
		if(mx < 0 || mx >= R || my < 0 || my >= C)
			continue;
		if(h[mx][my] >= h[x][y])
			continue;
		dp[mx][my] = max(dp[mx][my], dp[x][y] + 1);
		dfs(h, mx, my, mark, dp);
	}
}

int main(){
	int tCase = 1;
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	#endif	
	while (tCase--){
		scanf("%d%d", &R, &C);
		vector<vector<int> > h(R, vector<int>(C, 0));
		vector<vector<bool> > vis(R, vector<bool>(C, 0)), mark(R, vector<bool>(C, 0));
		vector<vector<int> > dp(R, vector<int>(C, 0));
 		priority_queue<pair<int, int> > pque;
		for (int i=0; i<R; ++i){
			for (int j=0; j<C; ++j){
				scanf("%d", &h[i][j]);
				pque.push(make_pair(h[i][j], i*C + j));
			}
		}
		while (!pque.empty()){
			auto p = pque.top(); pque.pop();
			int x = p.second / C, y = p.second % C;
			if(mark[x][y])
				continue;
			dp[x][y] = 1;
			dfs(h, x, y, mark, dp);
		}
		int maxn = 0;
		for (int i=0; i<R; ++i){
			for (int j=0; j<C; ++j){
				maxn = max(maxn, dp[i][j]);
			}
		}
		printf("%d\n", maxn);	
	}
	return 0;
}
