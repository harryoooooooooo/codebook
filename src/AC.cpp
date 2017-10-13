#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

struct node{
    node():parent(),child(),fail(),vrfail(),hitfail(),hit_count(),hit(){};
    int parent;
    char parentc;
    unordered_map<char,int> child;
    int fail;
    vector<int> vrfail;
    int hitfail;
    int hit_count;
    bool hit;
};

vector<node> build_trie(const vector<string>& vs){
    vector<node> v;
    v.push_back(node());
    for(const auto& s:vs){
        int now = 0;
        for(const auto& c:s){
            if(!v[now].child[c]){
                int cid = v.size();
                v.push_back(node());
                v[now].child[c] = cid;
                v[cid].parent=now;
                v[cid].parentc=c;
            }
            now=v[now].child[c];
        }
        v[now].hit=true;
    }
    return v;
}

vector<node> build_ac(const vector<string>& vs){
    auto v = build_trie(vs);
    v[0].fail = 0;
    v[0].hitfail = 0;
    for(size_t i = 1 ; i < v.size() ; i ++){
        int pfail = v[v[i].parent].fail;
        char parc = v[i].parentc;
        while(pfail!=0&&!v[pfail].child[parc])
            pfail=v[pfail].fail;
        if(v[pfail].child[parc]&&v[i].parent!=0)
            v[i].fail=v[pfail].child[parc];
        else
            v[i].fail=pfail;
        v[v[i].fail].vrfail.push_back(i);
        int tfail = v[i].fail;
        while(tfail!=0&&!v[tfail].hit)
            tfail=v[tfail].fail;
        v[i].hitfail = tfail;
    }
    return v;
}

void push_counts(vector<node>& v,int now){
    for(int next:v[now].vrfail){
        push_counts(v,next);
    }
    if(v[now].fail!=now){
        v[v[now].fail].hit_count+=v[now].hit_count;
    }
}

void run_ac(const string& t,vector<node>& v){
    int now = 0;
    for(auto c:t){
        while(now!=0&&!v[now].child[c])
            now=v[now].fail;
        int next;
        if(v[now].child[c])
            next=v[now].child[c];
        else
            next=now;
        now=next;
        v[now].hit_count++;
    }
    push_counts(v,0);
}
int main (){
}
