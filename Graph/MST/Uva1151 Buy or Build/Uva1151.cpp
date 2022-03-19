/*
Code: Uva1151 Buy or Build from ���㷨�������ž��䡷(�ڶ���) Chapter11 eg11_3 
Author: ʥ��
My CSDN blog: https://blog.csdn.net/weixin_42430021
Create Date: 22/03/19
Last update: 22/03/19
*/ 
#include<bits/stdc++.h>
using namespace std;
#define DEBUG

const int maxn = 1005;
const int maxq = 10;

int cost[maxq]; // �����ײͿ��� 

int x[maxn], y[maxn]; // �������� 

vector<int> subnet[maxq];  // subnet[i] ��i�����������Ľڵ� 


class UnionFind{
public:
	int p[maxn];
	int n;
	int cnt; // ��ͨ������Ŀ 
	UnionFind(int _n): n(_n), cnt(_n){
		for (int i=0; i<n; ++i){
			p[i] = i;
		}
	}
	int find(int x){ // Ѱ��x�ĸ��ڵ� 
		return p[x] == x? x: p[x] = find(p[x]); 
	}
	bool Union(int u, int v){
		int x = find(u), y = find(v);
		if(x != y){
			--cnt;
			p[x] = y;
			return true;
		}
		return false;
	}
};

struct Edge{
public:
	int u, v, w;
	Edge(){}
	Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w){}
	bool operator < (const Edge& e) const{
		return w < e.w;
	}
};

long long MST(UnionFind& uf, const vector<Edge>& e, vector<Edge>& need){
	if(uf.cnt == 1)
		return 0;
	need.clear();
	int m = e.size();
	long long res = 0;
	for (int i=0; i<m; ++i){
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if(uf.Union(u, v)){
			res += w;
			need.push_back(e[i]);
			if(uf.cnt == 1)
				break;
		}
	}
	return res;
}


int main(){
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	#endif
	int tCase;
	scanf("%d", &tCase);
	int n, q;
	while (tCase--){
		scanf("%d%d", &n, &q);
		for (int i=0; i<q; ++i){
			int m;
			scanf("%d%d", &m, &cost[i]);
			subnet[i].clear();  // do not forget
			for (int j=0; j<m; ++j){
				int u; 
				scanf("%d", &u);
				subnet[i].push_back(u-1);
			}
		}
		for (int i=0; i<n; ++i){
			scanf("%d%d", &x[i], &y[i]);
		} 
		vector<Edge> e, need;
		for (int i=0; i<n; ++i){
			for (int j=i+1; j<n; ++j){
				int w = (x[i] - x[j]) * (x[i] - x[j])
					+ (y[i] - y[j]) * (y[i] - y[j]);
				e.push_back(Edge(i, j, w));
			}
		}
		UnionFind uf(n);
		sort(e.begin(), e.end());
		long long ans = MST(uf, e, need);  // û������ʱ��MST 
		// ö��������ѡ��
		for (int mask=1; mask<(1<<q); ++mask){
			uf = UnionFind(n);
			long long curcost = 0;
			// �������ײͼ��뵽���鼯 
			for (int i=0; i<q; ++i){
				if(mask & (1 << i)){ // ��i������ѡ���� 
					curcost += cost[i];
					int m = subnet[i].size();
					for (int k=1; k<m; ++k){
						uf.Union(subnet[i][k], subnet[i][0]);
					}
				}
			}
			// ����ʣ����е�MST
			vector<Edge> no_use;
			curcost += MST(uf, need, no_use); 
			ans = min(ans, curcost);
		}
		// print the result
		printf("%lld\n", ans); 
		if(tCase){ // ����֮����Ҫһ�����зָ� 
			printf("\n");
		}
	}
	return 0;
} 
