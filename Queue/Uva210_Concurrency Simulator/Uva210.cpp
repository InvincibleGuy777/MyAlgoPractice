/*
Code: Uva210 并行程序模拟 from 《算法竞赛入门经典》(第二版) Chapter6 eg6_1 
Author: 圣哥
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

// 指令代号 
#define ASIGN 0
#define PRINT 1
#define LOCK 2
#define UNLOCK 3
#define END 4
#define MAXN 10  // 程序数目上限 
#define VAR_LIM 100 // 常数最大值+1 

//#define DEBUG // 调试模式 

 
int main(){
	
	int nCase;
	cin >> nCase;
	for (int x=0; x<nCase; ++x){
		// 注意案例之间隔一个空行 
		if(x > 0)
			cout<<endl;
		// 第一行参数输入
		int n, Q; 
		vector<int> t(5);  // t[i] - 第i种语句消耗的时间单元数
		cin >> n;
		for (int i=0; i<5; ++i)
			cin >> t[i];
		cin >> Q;
		// progs[i] 第i个程序  每条指令形式 [ORDER_ID, Data]
		/*
			例如：a = 50 -> [ASIGN, ('a'-'a')*VAR_LIM + 50]
			 print z -> [PRINT, 'z'-'a']
			 LOCK / UNLOCK / END -> [ORDER_ID, -1]
		*/
		vector<vector<pair<int, int> > > progs(n); 
		string tmp;
		int num;
		// 读取程序语句并保存
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
					else{ // end 注意退出循环 
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
		vector<int> vars(26, 0);  // 变量值，默认为0 
		deque<pair<int, int> > dque; // 等待队列   [ID, cur_line_idx]
		queue<pair<int, int> > que;  // 阻止队列 
		// 初始，所有程序进入等待队列 
		for (int i=0; i<n; ++i){
			dque.push_back(make_pair(i, 0)); // 第0行开始，程序id从0开始 
		}
		int id_lock = -1; // 目前独占内存的程序id 
		// 模拟并行过程，直到等待队列清空 
		// 注意：输出时程序id从1开始！ 
		while (!dque.empty()){
			// i - 当前读取的行 
			int prog_id = dque.front().first, i = dque.front().second; 
			dque.pop_front();
			int cur_cost = 0; // 当前消耗的额度
			int m = progs[prog_id].size();  // 程序行数 
			bool isBlocked = false; // 是否因为线程冲突而阻滞 
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
						else if(id_lock != prog_id){ // 当前程序丢入阻止队列 
							que.push(make_pair(prog_id, i)); 
							isBlocked = true;
						}
						break;
					case UNLOCK: // 之前锁的一定是当前程序 
						id_lock = -1;
						// 将阻止队列的队首元素加入到等待队列最前面 
						if(!que.empty()){
							dque.push_front(que.front());
							que.pop();
						}
						break;
					case END:  // 末尾啥也不干 
						break;
				}
				cur_cost += t[opt];
				i++; 
			}
			// 到这里当前读的程序有三种状态：已读完、未读完-正常、 未读完-阻滞  
			if(!isBlocked && i < m){ // 加入等待队列队尾，说明用完了配额，但没读完 
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
