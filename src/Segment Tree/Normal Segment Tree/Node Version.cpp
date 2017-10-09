#include <algorithm>
using namespace std;

template<class Elem, class Tag, class F, class PushF>
class RealSegTree{
    struct node{
        Elem val;
        Tag tag;
        int range_l, range_r;
        node *L, *R;
        ~node(){delete L; delete R;}
    };
    F f;
    PushF pushTag;
    node* root;
    void runPush(node* now){
        pushTag(now->L->val, now->tag);
        pushTag(now->L->tag, now->tag);
        pushTag(now->R->val, now->tag);
        pushTag(now->R->tag, now->tag);
        now->tag = Tag();
    }
    template<class It>
    void build(node*& now, int l, int r, int n, It& it){
        now = new node;
        now->range_l = l;
        now->range_r = r;
        now->tag = Tag();
        if (l!=r){
            int mid = (l+r)/2;
            build(now->L, l, mid, n, it);
            build(now->R, mid+1, r, n, it);
            now->val = f(now->L->val, now->R->val);
        }
        else {
            now->L = now->R = nullptr;
            if (!l) now->val = *it;
            else if (l<n) now->val = *(++it);
        }
    }
public:
    template<class It>
    RealSegTree(int n, It it):f(), pushTag(){
        int bound;
        for(bound=1;bound<n;bound<<=1);
        build(root, 0, bound-1, n, it);
    }
    /*
    template<class It>
    void rebuild(int n, It it){
        delete root;
        int bound;
        for(bound=1;bound<n;bound<<=1);
        build(&root, 0, bound-1, n, it);
    }
    */
    ~RealSegTree(){delete root;}
    Elem query(int start, int end, node* now=nullptr){
        if (!now) now = root;
        if(now->range_l==start&&now->range_r==end)return now->val;
        runPush(now);
        int mid=(now->range_l+now->range_r)/2;
        if (start > mid) return query(max(mid+1,start),end,now->R);
        else if (end < mid+1) return query(start,min(mid,end),now->L);
        else return f(query(start,min(mid,end),now->L),query(max(mid+1,start),end,now->R));
    }
    void set(int start, int end, const Tag& diff, node* now=nullptr){
        if (!now) now = root;
        if(now->range_l==start&&now->range_r==end){
            pushTag(now->val, diff);
            pushTag(now->tag, diff);
            return;
        }
        runPush(now);
        int mid=(now->range_l+now->range_r)/2;
        if (start <= mid) set(start, min(mid,end), diff, now->L);
        if (end >= mid+1) set(max(mid+1,start), end, diff, now->R);
        now->val = f(now->L->val, now->R->val);
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
//    ** it is ZERO BASE **
//    start & end are in [x,y] format (inclusively)
//    RealSegTree<int, int, minType, addType> stree(n, it);
//    stree.set(start, end, diff);
//    stree.query(start, end);
}
