#include <vector>
#include <algorithm>
using namespace std;

template<class Elem, class Tag, class F, class PushF>
class PerSegTree{
    struct node{
        Elem val;
        Tag tag;
        int range_l, range_r;
        node *trash, *L, *R;
        const node *Lro, *Rro;
        node() = default;
        node(const node& n):val(n.val),tag(n.tag),range_l(n.range_l),
        range_r(n.range_r),trash(),L(),R(),Lro(n.L?n.L:n.Lro),Rro(n.R?n.R:n.Rro){}
        ~node(){delete trash;}
    };
    F f;
    PushF pushTag;
    node* trash;
    vector<node*> root;
    node* getNode(const node& n=node()){
        node* tmp = new node(n);
        tmp->trash = trash;
        return trash = tmp;
    }
    void runPush(node* now){
        if (!now->L) now->L = getNode(*now->Lro);
        pushTag(now->L->val, now->tag);
        pushTag(now->L->tag, now->tag);
        if (!now->R) now->R = getNode(*now->Rro);
        pushTag(now->R->val, now->tag);
        pushTag(now->R->tag, now->tag);
        now->tag = Tag();
    }
    template<class It>
    void build(node*& now, int l, int r, int n, It& it){
        now = getNode();
        now->range_l = l;
        now->range_r = r;
        if (l!=r){
            int mid = (l+r)/2;
            build(now->L, l, mid, n, it);
            build(now->R, mid+1, r, n, it);
            now->val = f(now->L->val, now->R->val);
        }
        else {
            if (!l) now->val = *it;
            else if (l<n) now->val = *(++it);
        }
    }
    void set(int start, int end, const Tag& diff, node* from, node*& now){
        if(from->range_l==start&&from->range_r==end){
            now = getNode(*from);
            pushTag(now->val, diff);
            pushTag(now->tag, diff);
            return;
        }
        runPush(from);
        now = getNode(*from);
        int mid=(now->range_l+now->range_r)/2;
        if (start <= mid) set(start, min(mid,end), diff, from->L, now->L);
        else now->L = from->L;
        if (end >= mid+1) set(max(mid+1,start), end, diff, from->R, now->R);
        else now->R = from->R;
        now->val = f(now->L->val, now->R->val);
    }
    Elem query(int start, int end, node* now){
        if(now->range_l==start&&now->range_r==end)return now->val;
        runPush(now);
        int mid=(now->range_l+now->range_r)/2;
        if (start > mid) return query(max(mid+1,start),end,now->R);
        else if (end < mid+1) return query(start,min(mid,end),now->L);
        else return f(query(start,min(mid,end),now->L),query(max(mid+1,start),end,now->R));
    }
public:
    template<class It>
    PerSegTree(int n, It it):f(), pushTag(),trash(){
        root.push_back(nullptr);
        int bound;
        for(bound=1;bound<n;bound<<=1);
        build(root[0], 0, bound-1, n, it);
    }
    /*
    template<class It>
    void rebuild(int n, It it){
        delete trash;
        trash = nullptr;
        root.clear();
        root.push_back(nullptr);
        int bound;
        for(bound=1;bound<n;bound<<=1);
        build(&root[0], 0, bound-1, n, it);
    }
    */
    ~PerSegTree(){delete trash;}
    Elem query(size_t ver, int start, int end){
        return query(start, end, root[ver]);
    }
    size_t set(size_t ver, int start, int end, const Tag& diff){
        root.push_back(nullptr);
        set(start, end, diff, root[ver], root.back());
        return root.size()-1;
    }
};

struct yee{
    int l, r, m, s;
};

struct inputIterator{
    yee operator*(){return {0,0,0,1};}
    inputIterator operator++(){return *this;}
};

struct mergeType{
    yee operator()(const yee &x, const yee &y)const{
        return {(x.m==x.s)? x.l+y.l : x.l, (y.m==y.s)? y.r+x.r : y.r,
            max({x.m, y.m, x.r+y.l}), x.s+y.s};
    }
};

struct modType{
    void operator()(int, int)const{}
    void operator()(yee &lhs, int rhs)const{
        if (rhs) lhs = {1,1,1,1};
    }
};

int main (){
//    ** it is ZERO BASE **
//    start & end are in [x,y] format (inclusively)
//    PerSegTree<yee, int, mergeType, modType> pst(n, inputIterator());
//    pst.set(start, end, diff);
//    pst.query(start, end);
}
