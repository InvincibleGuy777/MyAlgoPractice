#include<bits/stdc++.h>
using namespace std;
//#define DEBUG

int n, m, p;
typedef long long LL;
const int maxn = 1e5 + 5;

int a[maxn];

struct tree{
	int l, r;
	LL sumv, mlz, plz;
	tree(): sumv(0), mlz(1), plz(0){}
	tree(int _l, int _r): l(_l), r(_r), sumv(0), mlz(1), plz(0){} 
};

tree T[maxn<<2];

inline void pushup(int o){
	T[o].sumv = (T[o<<1].sumv + T[o<<1|1].sumv)	% p;
}

inline void build(int o, int L, int R){
	T[o].l = L, T[o].r = R;
	if(L == R){
		T[o].sumv = a[L] % p;
		return;
	}
	int M = (L + R) >> 1;
	build(o<<1, L, M);
	build(o<<1|1, M+1, R);	
	pushup(o);	
}

inline void pushdown(int o){
	int L = T[o].l, R = T[o].r, M = (L + R) >> 1;
	T[o<<1].sumv = (T[o<<1].sumv * T[o].mlz + T[o].plz * (M - L + 1)) % p;
	T[o<<1|1].sumv = (T[o<<1|1].sumv * T[o].mlz + T[o].plz * (R - M)) % p;	
	// update lazytag
	T[o<<1].mlz = T[o<<1].mlz * T[o].mlz % p;
	T[o<<1|1].mlz = T[o<<1|1].mlz * T[o].mlz % p;
	T[o<<1].plz = (T[o<<1].plz * T[o].mlz + T[o].plz) % p;
	T[o<<1|1].plz = (T[o<<1|1].plz * T[o].mlz + T[o].plz) % p;
	// clear
	T[o].mlz = 1, T[o].plz = 0;
}

void add(int o, int ql, int qr, int k){
	int L = T[o].l, R = T[o].r;
	if(ql <= L && R <= qr){
		T[o].plz = (T[o].plz + k) % p;
		T[o].sumv = (T[o].sumv + 1LL * k * (R - L + 1)) % p;		
		return;
	}
	pushdown(o);
	int M = (L + R) >> 1;	
	if(ql <= M){
		add(o<<1, ql, qr, k);
	}	
	if(qr > M){
		add(o<<1|1, ql, qr, k);
	}
	pushup(o);
}

void mul(int o, int ql, int qr, int k){
	int L = T[o].l, R = T[o].r;
	if(ql <= L && R <= qr){
		T[o].mlz = T[o].mlz * k % p;
		T[o].plz = T[o].plz * k % p;
		T[o].sumv = T[o].sumv * k % p;		
		return;
	}
	pushdown(o);
	int M = (L + R) >> 1;	
	if(ql <= M){
		mul(o<<1, ql, qr, k);
	}	
	if(qr > M){
		mul(o<<1|1, ql, qr, k);
	}
	pushup(o);
}

LL query(int o, int ql, int qr){
	int L = T[o].l, R = T[o].r;
	if(ql <= L && R <= qr){			
		return T[o].sumv;
	}
	pushdown(o);
	int M = (L + R) >> 1;
	LL res = 0;	
	if(ql <= M){
		res = query(o<<1, ql, qr);
	}	
	if(qr > M){		
		res = (res + query(o<<1|1, ql, qr)) % p;
	}	
	return res;
}

int main(){
	#ifdef DEBUG
	freopen("data.txt", "r", stdin);
	#endif
	
	scanf("%d%d%d", &n, &m, &p);
	for (int i=1; i<=n; ++i){
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	for (int i=0; i<m; ++i){
		int op, ql, qr, k;
		scanf("%d%d%d", &op, &ql, &qr);
		if(op == 1){
			scanf("%d", &k);
			mul(1, ql, qr, k);
		}
		else if(op == 2){
			scanf("%d", &k);
			add(1, ql, qr, k);
		}
		else if(op == 3){
			LL ans = query(1, ql, qr);
			printf("%lld\n", ans);
		}
	}
	return 0;
} 
