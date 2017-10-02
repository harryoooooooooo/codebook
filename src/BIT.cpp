#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int bit[200010];
//get sum of 1~x
int query(int x){
    int tmp=0;
    for(;x>0;x-=x&-x){
        tmp+=bit[x];
    }
    return tmp;
}
//set now to x
void set(int now,int x){
    int diff=query(now)-query(now-1);
    diff=x-diff;
    for(;now<=n;now+=now&-now){
        bit[now]+=diff;
    }
}
int main (){
    scanf("%d",&n);
	//left bit[0] zero is necessary
    fill(bit,bit+200010,0);
    for(int i = 1 ; i <= n ; i ++){
        int tmp;
        scanf("%d",&tmp);
        set(i,tmp);
    }
}
