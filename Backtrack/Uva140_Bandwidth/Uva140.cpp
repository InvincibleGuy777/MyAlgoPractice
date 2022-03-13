/*
Code: Uva140 from 《算法竞赛入门经典》(第二版) Chapter7 eg7_6 
Author: 圣哥
My CSDN blog: https://blog.csdn.net/weixin_42430021
Create Date: 22/02/26
Last update: 22/02/26
*/ 
#include<iostream>
#include<string> 
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<cmath>
//#define DEBUG
using namespace std;

unordered_map<char, vector<char> > G;

int main(){
	string str;
	auto str2Graph = [&](const string& s){
		G.clear();  // 清空上一个图 
		vector<char> a;
		int n = s.length();
		char cur_node = -1;
		int vis[26] = {0};
		for (int i=0; i<n; ++i){
			if(s[i] == ';'){
				cur_node = -1;
			}
			else if(s[i] >= 'A' && s[i] <= 'Z'){
				if(cur_node == -1){
					cur_node = s[i];
				}
				else // 说明是邻接点 
					G[cur_node].push_back(s[i]);
				if(!vis[s[i]-'A']){
					vis[s[i]-'A'] = 1;
					a.push_back(s[i]);
				}
			}
		}
		return a;
	};
	
	
	
	#ifdef DEBUG
		string s = "A:FB;B:GC;D:GC;F:AGH;E:HD";
		str2Graph(s);
		for (auto it=G.begin(); it!=G.end(); ++it){
			cout<<it->first<<": ";
			for (auto& v: it->second){
				cout<<v<<" ";
			}
			cout<<endl;
		}
	#endif
	while (cin >> str && str[0] != '#'){
		int min_bw = 8;
		vector<char> ans;
		// 读取str
		vector<char> arr = str2Graph(str);
		sort(arr.begin(), arr.end());
		auto getminBandWidth = [&](){
			unordered_map<char, int> pos; // 字符在数组中的下标 
			for (int i=0; i<arr.size(); ++i){
				pos[arr[i]] = i;
			}
			// 遍历所有边，确认图的带宽（最大） 
			int cur_bw = 0; // 当前带宽 
			for (auto it=G.begin(); it!=G.end(); ++it){
				char u = it->first;
				// prune1:m个邻接节点依次均匀排列在当前节点两边为最优排列，
				//带宽至少为(m+1)/2
				//若min_bw <= (m+1)/2，则无论如何都不会有更小的带宽了
				int m = (it->second).size();
				if(min_bw <= (m+1) / 2)
					return; 
				for (char& v: it->second){
					cur_bw = max(cur_bw, abs(pos[v]-pos[u]));
					// prune2:带宽超过了最小带宽
					if(cur_bw > min_bw){ 
						return;
					}
				}
			}
			// 找到了更小的带宽，相等带宽由于字典序靠后而不为答案 
			if(min_bw > cur_bw){ 
				min_bw = cur_bw; 
				ans = arr; // 更新最优排列 
			}
		};
		// 枚举字符所有排列
		do{
			#ifdef DEBUG
			for (int i=0; i<arr.size(); ++i){
				cout<<arr[i];
			}
			cout<<endl;
			#endif
			getminBandWidth();
		}while (next_permutation(arr.begin(), arr.end()));
		// output
		for (int i=0; i<ans.size(); ++i){
			if(i > 0)
				cout<<" ";
			cout<<ans[i];
		}
		cout<<" -> "<<min_bw<<endl;
	}
	return 0;
} 
