// 847.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <bits/stdc++.h>
using namespace std;

template<class T1, class T2>
void is_gid_in_waiting_queue(T1& GID_FOUND, map<T2, list<int>>& readyqueue, pair<T2,T2>& pcb) {
	auto gid_iterator = readyqueue.find(pcb.second);
	int pid = pcb.first;
	if ( readyqueue.end() != gid_iterator )  
		GID_FOUND = true;
}

int main()
{
	int _process  , _task ;
	scanf_s("%d", &_process);  
	scanf_s("%d", &_task);
	
	typedef int gid;
	typedef int pid;
	pair<pid, gid> pid_pair;
	map<gid , list<pid> > ready_queue;
	queue<gid> group_queue;
	vector<pair<pid, gid>> pcb; // first pid  second gid
	int buf;
	pcb.push_back(make_pair(-1, -1));
	for (int i = 0; i < _process; i++) {
		scanf_s("%d", &buf);
		
		pcb.push_back(make_pair(i+1,buf));
		
	}
	bool gid_found;
	bool pid_found;
	vector<bool> appear;
	appear.assign(_process+1 , false);
	while (_task--) {
		scanf_s("%d", &buf); // operation
		if (buf == 1) {
			scanf_s("%d", &buf); // pid of process
			gid_found = false;
			pid_found = false;
			pid_pair = pcb.at(buf);
			
			is_gid_in_waiting_queue(gid_found , ready_queue , pid_pair);
			pid_found = appear.at(pid_pair.first);

			if (!pid_found) { // if not in queue
				if (!gid_found) {// group not found
					group_queue.push(pid_pair.second);
					ready_queue[pid_pair.second].push_back(pid_pair.first);
				}
				else {
					ready_queue[pid_pair.second].push_front( pid_pair.first);
				}
				appear.at(pid_pair.first) = true ;
				printf("Successful\n");
			}
			else { // ignore
				printf("Ignore\n");
			}
		}
		else {
			if (group_queue.empty()) 
				printf("0\n");
			else {
				gid pop_group = group_queue.front();
				pid pop_process = ready_queue[pop_group].front();
				ready_queue[pop_group].pop_front();
				if (ready_queue[pop_group].empty()) {
					ready_queue.erase(pop_group);
					group_queue.pop();
				}
				appear.at(pop_process) = false;
				printf("%d\n", pop_process);
			}
		}
	}
}

