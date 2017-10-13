#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char t[1000010];
char w[10010];
int fail[10010];
int tlen;
int wlen;
void buildkmp(){
    fail[0]=-1;
    int now=-1;
    for(int i = 1 ; i < wlen ; i ++){
        while(now!=-1&&w[now+1]!=w[i])now=fail[now];
        if(w[now+1]==w[i])now++;
        fail[i]=now;
    }
}
int main (){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s%s",w,t);
        tlen=strlen(t);
        wlen=strlen(w);
        buildkmp();
        int cnt=0;
        int now=-1;
        for(int i = 0 ; i < tlen ; i ++){
            while(now!=-1&&w[now+1]!=t[i])now=fail[now];
            if(w[now+1]==t[i])now++;
            if(now==wlen-1){
                cnt++;
                now=fail[now];
            }
        }
        printf("%d\n",cnt);
    }
}

