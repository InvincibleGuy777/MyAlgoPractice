#include<bits/stdc++.h>
using namespace std;
#define DEBUG

const int INF = INT_MAX;

const int d[5] = {0, 1, 0, -1, 0};
int R, C;

int dfs(const vector<vector<int> >& h, 
vector<vector<bool> >& vis, int x, int y, vector<vector<bool> >& mark){
	vis[x][y] = true;
	mark[x][y] = true;
	int maxn = 0; 
	for (int k=0; k<4; ++k){
		int mx = x + d[k], my = y + d[k+1];
		if(mx < 0 || mx >= R || my < 0 || my >= C || vis[mx][my])
			continue;
		if(h[mx][my] >= h[x][y])
			continue;
		maxn = max(maxn, dfs(h, vis, mx, my, mark));
	}
	// vis[x][y] = false;
	return maxn + 1;
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
 		priority_queue<pair<int, int> > pque;
		for (int i=0; i<R; ++i){
			for (int j=0; j<C; ++j){
				scanf("%d", &h[i][j]);
				pque.push(make_pair(h[i][j], i*C + j));
			}
		}
		int maxn = 0;
		while (!pque.empty()){
			auto p = pque.top(); pque.pop();
			int x = p.second / C, y = p.second % C;
			if(mark[x][y])
				continue;
			maxn = max(maxn, dfs(h, vis, x, y, mark));
		}
		printf("%d\n", maxn);	
	}
	return 0;
}
