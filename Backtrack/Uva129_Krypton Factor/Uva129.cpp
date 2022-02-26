/*
Code: Uva129 from 《算法竞赛入门经典》(第二版) Chapter7 eg7_5 
Author: 圣哥
My CSDN blog: https://blog.csdn.net/weixin_42430021
Create Date: 21/02/26
Last update: 21/02/26
*/ 
#include<iostream>
#include<cstdio>
#include<functional> 
#define min(a, b) ((a) < (b)? (a): (b))
using namespace std;


int main(){
	int n, L;
	char buf[85];
	// 格式打印函数 
	auto printBuf = [&](int len){
		for (int i=0; i<len; i+=4){
			if(i)
				i%64==0? printf("\n"): printf(" ");
			int n = min(i+4, len);
			for (int j=i; j<n; ++j){
				printf("%c", buf[j]);
			}
		}	
	};
	
	// 在buf[len]处加入字符后是否能保证后缀子串不连续重复 
	auto check = [&](int len){
		// 检查偶数长度的串，看是否前半=后半 
		for (int k=2; k<=len+1; k+=2){ // (len-k, len]
			bool flag = true;
			for (int i=len; i>len-k/2; --i){
				if(buf[i] != buf[i-k/2]){
					flag = false;
				}
			}
			if(flag)
				return false;
		}
		return true;
	};
	
	// 回溯找前L字符组成的第k个困难串，当前为第cur个，长度为len 
	std::function<void(int, int, int&, int)> dfs;
	dfs = [&](int L, int k, int& cur, int len){
		if(cur == k){
			printBuf(len);
			printf("\n%d\n", len);
			return;
		}
		// 添加一个字符'A'+i至buf[len]
		for (int i=0; i<L; ++i){
			buf[len] = 'A' + i;
			if(check(len)){
				// dfs(L, k, cur+1, len+1); // 注意，这里不能对引用变量传参使用表达式 
				cur++;
				dfs(L, k, cur, len+1);
				if(cur == k) // 不可缺少 
					return;
			}
		} 
	};
	
	while (scanf("%d%d", &n, &L) == 2 && n && L){
		int cur = 0;
		dfs(L, n, cur, 0);
	}
	return 0;
}
