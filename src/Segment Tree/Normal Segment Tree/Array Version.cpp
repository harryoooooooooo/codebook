#include <vector>
#include <algorithm>
using namespace std;

template<class Elem, class Tag, class F, class PushF>
class SegTree{
    F f;
    PushF pushTag;
    int base;
    vector<Elem> v;
    vector<Tag> tag;
    pair<int,int> range(int x)const{
        int h=0;
        for(int t=1<<base;t>x;t>>=1)h++;
        int b=1<<(base-h);
        return {(1<<h)*(x-b),(1<<h)*(x-b+1)-1};
    }
    void runPush(int now){
        pushTag(v[now*2], tag[now]);
        pushTag(tag[now*2], tag[now]);
        pushTag(v[now*2+1], tag[now]);
        pushTag(tag[now*2+1], tag[now]);
        tag[now] = Tag();
    }
public:
    template<class It>
    SegTree(int n, It it):f(), pushTag(){
        for(base=0;(1<<base)<n;base++);
        v.resize(1<<(base+1));
        tag.resize(1<<(base+1));
        copy_n(it, n, v.begin()+(1<<base));
        for(int i = (1<<base)-1 ; i>0 ; i --)
            v[i] = f(v[i*2], v[i*2+1]);
    }
    /*
    template<class It>
    void rebuild(int n, It it){
        for(base=0;(1<<base)<n;base++);
        v.resize(1<<(base+1));
        tag.resize(1<<(base+1));
        fill(tag.begin(), tag.end(), Tag());
        copy_n(it, n, v.begin()+(1<<base));
        for(int i = (1<<base)-1 ; i>0 ; i --)
            v[i] = f(v[i*2], v[i*2+1]);
    }
    */
    Elem query(int start, int end, int now=1){
        auto r=range(now);
        if(r.first==start&&r.second==end)return v[now];
        runPush(now);
        int mid=(r.first+r.second)/2;
        if (start > mid) return query(max(mid+1,start),end,now*2+1);
        else if (end < mid+1) return query(start,min(mid,end),now*2);
        else return f(query(start,min(mid,end),now*2),query(max(mid+1,start),end,now*2+1));
    }
    void set(int start, int end, const Tag& diff, int now=1){
        auto r=range(now);
        if(r.first==start&&r.second==end){
            pushTag(v[now], diff);
            pushTag(tag[now], diff);
            return;
        }
        runPush(now);
        int mid=(r.first+r.second)/2;
        if (start <= mid) set(start, min(mid,end), diff, now*2);
        if (end >= mid+1) set(max(mid+1,start), end, diff, now*2+1);
        v[now] = f(v[now*2], v[now*2+1]);
    }
};

struct minType{
    int operator()(int x, int y)const{
        return min(x, y);
    }
};

struct addType{
    void operator()(int &lhs, const int &rhs)const{
        lhs += rhs;
    }
};

int main (){
//    start & end are in [x,y] format (inclusively)
//    RealSegTree<int, int, minType, addType> stree(n, it);
//    stree.set(start, end, diff);
//    stree.query(start, end);
}
