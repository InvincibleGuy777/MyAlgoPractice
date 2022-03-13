/*
Code: Uva140 from ���㷨�������ž��䡷(�ڶ���) Chapter7 eg7_6 
Author: ʥ��
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
		G.clear();  // �����һ��ͼ 
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
				else // ˵�����ڽӵ� 
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
		// ��ȡstr
		vector<char> arr = str2Graph(str);
		sort(arr.begin(), arr.end());
		auto getminBandWidth = [&](){
			unordered_map<char, int> pos; // �ַ��������е��±� 
			for (int i=0; i<arr.size(); ++i){
				pos[arr[i]] = i;
			}
			// �������бߣ�ȷ��ͼ�Ĵ������ 
			int cur_bw = 0; // ��ǰ���� 
			for (auto it=G.begin(); it!=G.end(); ++it){
				char u = it->first;
				// prune1:m���ڽӽڵ����ξ��������ڵ�ǰ�ڵ�����Ϊ�������У�
				//��������Ϊ(m+1)/2
				//��min_bw <= (m+1)/2����������ζ������и�С�Ĵ�����
				int m = (it->second).size();
				if(min_bw <= (m+1) / 2)
					return; 
				for (char& v: it->second){
					cur_bw = max(cur_bw, abs(pos[v]-pos[u]));
					// prune2:����������С����
					if(cur_bw > min_bw){ 
						return;
					}
				}
			}
			// �ҵ��˸�С�Ĵ�����ȴ��������ֵ��򿿺����Ϊ�� 
			if(min_bw > cur_bw){ 
				min_bw = cur_bw; 
				ans = arr; // ������������ 
			}
		};
		// ö���ַ���������
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
