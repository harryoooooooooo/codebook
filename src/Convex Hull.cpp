#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<double,double> pdd;

vector<pdd> v;
int ch[1000];
int m;

double cross(const pdd &o,const pdd &a,const pdd &b){
    return (a.first-o.first)*(b.second-o.second)-(b.first-o.first)*(a.second-o.second);
}
int main (){
    v.clear();
    m=0;
    v.push_back({0,0});
    v.push_back({0,1});
    v.push_back({1,0});
    sort(v.begin(),v.end());
    //run
    for(size_t i = 0 ; i < v.size() ; i ++){
        while(m>=2&&cross(v[ch[m-2]],v[ch[m-1]],v[i])<=0)m--;
        ch[m++]=i;
    }
    for(int i=v.size()-2,t=m+1 ; i>=0 ; i --){
        while(m>=t&&cross(v[ch[m-2]],v[ch[m-1]],v[i])<=0)m--;
        ch[m++]=i;
    }
    //print ans
    for (int i=0;i<m;i++)
        printf("%f %f\n", v[ch[i]].first, v[ch[i]].second);
}
