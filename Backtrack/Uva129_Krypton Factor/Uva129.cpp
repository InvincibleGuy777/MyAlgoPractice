/*
Code: Uva129 from ���㷨�������ž��䡷(�ڶ���) Chapter7 eg7_5 
Author: ʥ��
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
	// ��ʽ��ӡ���� 
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
	
	// ��buf[len]�������ַ����Ƿ��ܱ�֤��׺�Ӵ��������ظ� 
	auto check = [&](int len){
		// ���ż�����ȵĴ������Ƿ�ǰ��=��� 
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
	
	// ������ǰL�ַ���ɵĵ�k�����Ѵ�����ǰΪ��cur��������Ϊlen 
	std::function<void(int, int, int&, int)> dfs;
	dfs = [&](int L, int k, int& cur, int len){
		if(cur == k){
			printBuf(len);
			printf("\n%d\n", len);
			return;
		}
		// ���һ���ַ�'A'+i��buf[len]
		for (int i=0; i<L; ++i){
			buf[len] = 'A' + i;
			if(check(len)){
				// dfs(L, k, cur+1, len+1); // ע�⣬���ﲻ�ܶ����ñ�������ʹ�ñ��ʽ 
				cur++;
				dfs(L, k, cur, len+1);
				if(cur == k) // ����ȱ�� 
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
