/*
Code: Uva11235 频繁出现的数值 from 《算法竞赛入门经典训练指南》Chapter3 eg8 
Author: 圣哥
My CSDN blog: https://blog.csdn.net/weixin_42430021
Create Date: 22/03/13
Last update: 22/03/13
*/ 
#include<iostream>
#include<algorithm>
#include<vector>
#define DEBUG
#define MAXN 100005
using namespace std;

int A[MAXN];
int n, q;
vector<int> num, lefts, rights, value, cnts;
void solve();

int main(){	
	#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout); 
	#endif
	while (scanf("%d", &n) == 1 && n && scanf("%d", &q) == 1 && q){
		for (int i=1; i<=n; ++i){
			scanf("%d", &A[i]);
		}
		// 预处理 
		value.clear(), cnts.clear();
		value.push_back(A[1]);
		cnts.push_back(1);
		// 游程编码  RunLengthEncoding 
		for (int i=2; i<=n; ++i){
			if(A[i] == value.back()){
				cnts.back()++;
			}
			else{
				value.push_back(A[i]);
				cnts.push_back(1);
			}
		}
		// num[i] A[i]位于哪一段中
		// lefts[i] A[i]所在段的左边界下标  rights[i] A[i]所在段的右边界下标 
		num = lefts = rights = vector<int>(n+1);
		int p = 1;
		for (int k=0; k<value.size(); ++k){
			for (int i=p; i<p+cnts[k]; ++i){
				num[i] = k;
				lefts[i] = p;
				rights[i] = p+cnts[k]-1;
			}
			p += cnts[k];
		}
		
		solve();
	}
	
	return 0;
} 

void solve(){
	// RMQ  M - MAX
	int m = value.size();
	vector<vector<int> > dp(m, vector<int>(20)); // dp[i][j] cnts[i, i+2^j-1]中的最大值
	// dp[i][j] = max(dp[i][j-1], dp[i+2^(j-1)][j-1]) 
	// 初始化  dp[i][0] = cnts[i]
	for (int i=0; i<m; ++i){
		dp[i][0] = cnts[i];
	}
	for (int j=1; (1 << j) <= m; j++){
		for (int i=0; i + (1 << j) - 1 < m; ++i){
			dp[i][j] = max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
		}
	}
	auto RMQ = [&](int l, int r){
		if(l > r)
			return 0;
		int k = 0;
		while ((1<<(k+1)) <= r-l+1) k++; // 2^(k+1) <= r-l+1
		return max(dp[l][k], dp[r-(1<<k)+1][k]);	
	};
	// 以上全为预处理过程，下面正式开始解决查询问题
	while (q--){
		int L, R;
		scanf("%d%d", &L, &R);
		/* [L, R]中的众数的出现次数 <=> 
		max(rights[L]-L+1, R-lefts[R]+1, RMQ(num[L]+1, num[R]-1))
		*/
		if(num[R] == num[L]){ // 位于同一段 
			//printf("%d, %d\n", L, R);
			printf("%d\n", R-L+1);
		}
		else{
			printf("%d\n", max(RMQ(num[L]+1, num[R]-1), 
			max(rights[L]-L+1, R-lefts[R]+1)));
		}
	}
}
