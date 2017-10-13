#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

vector<int> e[100010];
int t;
int tin[100010];
int tout[100010];
int a[100010][20];
long long d[100010];

void dfs(int now,int p){
    tin[now]=t++;
    a[now][0]=p;
    for(int i = 1 ; i<20 ; i ++)
        a[now][i]=a[a[now][i-1]][i-1];
    for(auto next:e[now])
        if(next!=p){
            dfs(next,now);
        }
    tout[now]=t++;
}

bool is_a(int x,int y){
    return tin[x]<tin[y]&&tout[x]>tout[y];
}

int lca(int x,int y){
    if(is_a(x,y))return x;
    if(is_a(y,x))return y;
    for(int i = 19 ; i >= 0 ; i --)
        if(!is_a(a[x][i],y))
            x=a[x][i];
    return a[x][0];
}
