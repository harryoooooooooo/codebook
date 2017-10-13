//i*2 false i*2+1 true
vector<int> e[2010];
vector<int> re[2010];
stack<int> s;
int cnt;
bool visited[2010];
int scc[2010];
void dfs1(int x){
    if(visited[x])return;
    visited[x]=true;
    for(auto next:e[x]){
        dfs1(next);
    }
    s.push(x);
}
void dfs2(int x){
    if(visited[x])return;
    visited[x]=true;
    scc[x]=cnt;
    for(auto next:re[x]){
        dfs2(next);
    }
}
int main (){
    for(int i = 0 ; i < p ; i ++){
        for(int j = i + 1 ; j < p ; j ++){
            e[2*i].push_back(2*j+1);
            e[2*i+1].push_back(2*j);
            e[2*j].push_back(2*i+1);
            e[2*j+1].push_back(2*i);
        }
    }
    fill(visited,visited+2010,false);
    for(int i = 0 ; i < 2*p ; i ++){
        if(!visited[i]){
            dfs1(i);
        }
    }
    fill(visited,visited+2010,false);
    while(!s.empty()){
        int now = s.top();
        s.pop();
        if(visited[now])continue;
        dfs2(now);
        cnt++;
    }
    bool fail=false;
    for(int i = 0 ; i < p ; i ++){
        if(scc[i*2]==scc[i*2+1])fail=true;
    }
    if(fail)printf("impossible\n");
    else printf("possible\n");
}
