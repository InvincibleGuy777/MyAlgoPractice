/*
Code: Uva1395 苗条的生成树 from 《算法竞赛入门经典》(第二版) Chapter11 eg11_2 
Author: 圣哥
My CSDN blog: https://blog.csdn.net/weixin_42430021
Create Date: 22/03/19
Last update: 22/03/19
*/ 
#include<bits/stdc++.h>
using namespace std;
#define DEBUG
const int maxn = 105;
const int INF = 1000000000;

class UnionFind{
public:
	int p[maxn];
	int n;
	int cnt; // 连通分量数目 
	UnionFind(int _n): n(_n), cnt(_n){
		for (int i=1; i<=n; ++i){
			p[i] = i;
		}
	}
	int find(int x){ // 寻找x的根节点 
		return p[x] == x? x: p[x] = find(p[x]); 
	}
	void Union(int u, int v){
		int x = find(u), y = find(v);
		if(x != y){
			--cnt;
			p[x] = y;
		}
	}
};

struct Edge{
public:
	int u, v, w;
	Edge(){}
	Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w){}
};



int main(){
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	#endif
	int n, m;	
	while (scanf("%d%d", &n, &m) == 2 && n){
		vector<Edge> e; // 输入 
		for (int i=1; i<=m; ++i){
			int _u, _v, _w;
			scanf("%d%d%d", &_u, &_v, &_w);
			e.push_back(Edge(_u, _v, _w));
		}
		sort(e.begin(), e.end(), [](const Edge& e1, const Edge& e2){
			return e1.w < e2.w;
		});
		int ans = INF;
		for (int L=0; L<m; ++L){
			UnionFind uf(n);
			for (int R=L; R<m; ++R){
				int u = e[R].u, v = e[R].v;
				uf.Union(u, v);
				if(uf.cnt == 1){ // 全连通 
					ans = min(ans, e[R].w - e[L].w);
					break;
				}
			}
		} 
		printf("%d\n", ans == INF? -1: ans);
	}
	return 0;
} 
