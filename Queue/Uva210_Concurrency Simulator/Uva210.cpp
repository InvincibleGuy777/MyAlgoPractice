/*
Code: Uva210 ���г���ģ�� from ���㷨�������ž��䡷(�ڶ���) Chapter6 eg6_1 
Author: ʥ��
My CSDN blog: https://blog.csdn.net/weixin_42430021
Create Date: 22/02/23
Last update: 22/02/23
*/ 
#include<iostream>
#include<queue>
#include<deque>
#include<vector>
#include<string>
using namespace std;

// ָ����� 
#define ASIGN 0
#define PRINT 1
#define LOCK 2
#define UNLOCK 3
#define END 4
#define MAXN 10  // ������Ŀ���� 
#define VAR_LIM 100 // �������ֵ+1 

//#define DEBUG // ����ģʽ 

 
int main(){
	
	int nCase;
	cin >> nCase;
	for (int x=0; x<nCase; ++x){
		// ע�ⰸ��֮���һ������ 
		if(x > 0)
			cout<<endl;
		// ��һ�в�������
		int n, Q; 
		vector<int> t(5);  // t[i] - ��i��������ĵ�ʱ�䵥Ԫ��
		cin >> n;
		for (int i=0; i<5; ++i)
			cin >> t[i];
		cin >> Q;
		// progs[i] ��i������  ÿ��ָ����ʽ [ORDER_ID, Data]
		/*
			���磺a = 50 -> [ASIGN, ('a'-'a')*VAR_LIM + 50]
			 print z -> [PRINT, 'z'-'a']
			 LOCK / UNLOCK / END -> [ORDER_ID, -1]
		*/
		vector<vector<pair<int, int> > > progs(n); 
		string tmp;
		int num;
		// ��ȡ������䲢����
		for (int i=0; i<n; ++i){
			while (true){
				cin >> tmp;
				if(tmp.size() == 1){ // var = constant
					int ich = tmp[0] - 'a';
					cin >> tmp;	
					cin >> num;
					progs[i].push_back(make_pair(ASIGN, ich*VAR_LIM+num));
				}
				else{
					if(tmp[0] == 'p'){ // print
						cin >> tmp;
						int ich = tmp[0] - 'a';
						progs[i].push_back(make_pair(PRINT, ich));
					}
					else if(tmp[0] == 'l'){ // lock
						progs[i].push_back(make_pair(LOCK, -1));
					}
					else if(tmp[0] == 'u'){ // unlock
						progs[i].push_back(make_pair(UNLOCK, -1));
					}
					else{ // end ע���˳�ѭ�� 
						progs[i].push_back(make_pair(END, -1));
						break;
					}
				}
			}
		}
		#ifdef DEBUG
		for (int i=0; i<n; ++i){
			int m = progs[i].size();
			for (int j=0; j<m; ++j){
				cout<<progs[i][j].first<<", "<<progs[i][j].second<<endl;
			}
			cout<<"===============\n";
		}
		#endif
		vector<int> vars(26, 0);  // ����ֵ��Ĭ��Ϊ0 
		deque<pair<int, int> > dque; // �ȴ�����   [ID, cur_line_idx]
		queue<pair<int, int> > que;  // ��ֹ���� 
		// ��ʼ�����г������ȴ����� 
		for (int i=0; i<n; ++i){
			dque.push_back(make_pair(i, 0)); // ��0�п�ʼ������id��0��ʼ 
		}
		int id_lock = -1; // Ŀǰ��ռ�ڴ�ĳ���id 
		// ģ�Ⲣ�й��̣�ֱ���ȴ�������� 
		// ע�⣺���ʱ����id��1��ʼ�� 
		while (!dque.empty()){
			// i - ��ǰ��ȡ���� 
			int prog_id = dque.front().first, i = dque.front().second; 
			dque.pop_front();
			int cur_cost = 0; // ��ǰ���ĵĶ��
			int m = progs[prog_id].size();  // �������� 
			bool isBlocked = false; // �Ƿ���Ϊ�̳߳�ͻ������ 
			while (cur_cost < Q && i < m && !isBlocked){
				int opt = progs[prog_id][i].first;
				int val = progs[prog_id][i].second; 
				switch(opt){
					case ASIGN:
						vars[val/VAR_LIM] = val % VAR_LIM;
						break;
					case PRINT:
						cout << prog_id + 1 << ": "<< vars[val]<<endl;	
						break;
					case LOCK:
						if(id_lock == -1){
							id_lock = prog_id;
						}
						else if(id_lock != prog_id){ // ��ǰ��������ֹ���� 
							que.push(make_pair(prog_id, i)); 
							isBlocked = true;
						}
						break;
					case UNLOCK: // ֮ǰ����һ���ǵ�ǰ���� 
						id_lock = -1;
						// ����ֹ���еĶ���Ԫ�ؼ��뵽�ȴ�������ǰ�� 
						if(!que.empty()){
							dque.push_front(que.front());
							que.pop();
						}
						break;
					case END:  // ĩβɶҲ���� 
						break;
				}
				cur_cost += t[opt];
				i++; 
			}
			// �����ﵱǰ���ĳ���������״̬���Ѷ��ꡢδ����-������ δ����-����  
			if(!isBlocked && i < m){ // ����ȴ����ж�β��˵������������û���� 
				dque.push_back(make_pair(prog_id, i));
			} 
		}
	}
	#ifdef DEBUG	
	cin.get();
	cin.get();
	#endif
	return 0;
}
