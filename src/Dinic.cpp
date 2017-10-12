#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct edge{
	int t,c,ri;
};

const int max_node = 550;
const int src  = max_node-1;
const int sink = max_node-2;

vector<edge> ad[max_node];
int d[max_node];
bool inq[max_node];

bool bfs(){
	fill(inq,inq+max_node,false);
	inq[src]=true;
	queue<pair<int,int>> q;
	q.push({0,src});
	while(!q.empty()){
		int nowd=q.front().first;
		int now=q.front().second;
		q.pop();
		d[now]=nowd;
		for(const auto& e:ad[now]){
			if(!inq[e.t]&&e.c>0){
				q.push({nowd+1,e.t});
				inq[e.t]=true;
			}
		}
	}
	if(!inq[sink])return false;
	return true;
}
bool vis[max_node];
int dfs(int now,int mf,int t){
	if(now==t)return mf;
	if(mf==0)return 0;
	if(vis[now])return 0;
	vis[now]=true;
	for(auto &e:ad[now]){
		if(e.c>0&&d[now]==d[e.t]-1){
			int f=dfs(e.t,min(e.c,mf),t);
			if(f>0){
				e.c-=f;
				ad[e.t][e.ri].c+=f;
				return f;
			}
		}
	}
	return 0;
}

int flow(){
	while(bfs()){
        do fill(vis,vis+max_node,false);
        while (dfs(src,1000000000,sink));
	}
	int mf = 0;
	for(const auto& e:ad[sink])
		mf += e.c;
	return mf;
}

void set_edge(int from, int to, int cap){
	int r1=ad[from].size();
	int r2=ad[to].size();
	ad[from].push_back({to,cap,r2});
	ad[to].push_back({from,0,r1});
}

int main (){
	//use set_edge() to set edge
	//flow() return max flow
	//max_node means max # of nodes
	//be careful that the last two node is s, t
}
