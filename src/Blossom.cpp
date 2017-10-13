const int V = 50;   // 圖的點數，編號為0到V-1。
bool adj[50][50];   // adjacency matrix
int p[50];          // 交錯樹
int m[50];          // 記錄各點所配對的點，值為-1為未匹配點。
int d[50];          // 值為-1未拜訪、0偶點、1奇點。
int c1[50], c2[50]; // 記錄花上各奇點所經過的cross edge
int q[50], *qf, *qb;    // queue，只放入偶點。
 
/* disjoint-sets forest */
int pp[50];
int f(int x) {return x == pp[x] ? x : (pp[x] = f(pp[x]));}
// void u(int x, int y) {pp[f(x)] = f(y);}
void u(int x, int y) {pp[x] = y;}
 
/* lowest common ancestor */
int v[50];
 
// 繞一繞花，找出擴充路徑，並擴充。源頭是r，末梢是x。
// 最初以偶點作為末端，每次往回走一條匹配邊加一條未匹配邊，
// 如果遇到花上奇點，就要繞花，以cross edge拆成兩段路徑。
void path(int r, int x)
{
    if (r == x) return;
 
    if (d[x] == 0)          // 還是偶點，繼續往回走。
    {
        path(r, p[p[x]]);
        int i = p[x], j = p[p[x]];
        m[i] = j; m[j] = i;
    }
    else if (d[x] == 1)     // 遇到花上奇點，就要繞花。
    {
        // 往回走會經過cross edge c1[x]-c2[x]
        path(m[x], c1[x]);  // 頭尾要顛倒
        path(r, c2[x]);
        int i = c1[x], j = c2[x];
        m[i] = j; m[j] = i;
    }
}
 
// 邊xy是cross edge，同時一起往上找LCA。
// 找一次的時間複雜度是O(max(x->b, y->b))，
// 不會超過縮花所縮掉的點的兩倍，縮掉的點也不會再算到，
// 故可推得：建一棵交錯樹，算LCA總共只有O(V)。
int lca(int x, int y, int r)
{
    int i = f(x), j = f(y);
    while (i != j && v[i] != 2 && v[j] != 1)
    {
        v[i] = 1; v[j] = 2;
        if (i != r) i = f(p[i]);
        if (j != r) j = f(p[j]);
    }
    int b = i, z = j; if (v[j] == 1) swap(b, z);
 
    for (i = b; i != z; i = f(p[i])) v[i] = -1;
    v[z] = -1;
    return b;
}
 
/*
// 一次就要O(V)的LCA演算法
int lca(int x, int y, int r)
{
    int v[50] = {0};
    v[r] = 1;
    for (x = f(x); x != r; x = f(p[x])) v[x] = 1;
    for (y = f(y); !v[y]; y = f(p[y])) ;
    return y;
}
*/
 
// 找到花時，弄好到達花上各奇點之交錯路徑，並讓奇點變成偶點。
// 只弄半邊。
// 邊xy為cross edge。b為花托。
void contract_one_side(int x, int y, int b)
{
    for (int i = f(x); i != b; i = f(p[i]))
    {
        u(i, b);    // 縮花，花托成為disjoint forest的樹根
        if (d[i] == 1) c1[i] = x, c2[i] = y, *qb++ = i;
    }
}
 
// 給定一個未匹配點r，建立交錯樹。
bool BFS(int r)
{
    for (int i=0; i<V; ++i) pp[i] = i;  // d. f.: init
    memset(v, -1, sizeof(v));           // lca: init
 
    memset(d, -1, sizeof(d));
    d[r] = 0;                           // 樹根是偶點
 
    qf = qb = q;
    *qb++ = r;                          // 樹根放入queue
 
    while (qf < qb)
        for (int x=*qf++, y=0; y<V; ++y)
            // 有鄰點。點存在。縮花成同一點後則不必處理。
            if (adj[x][y] && m[y] != y && f(x) != f(y))
                if (d[y] == -1)         // 沒遇過的點
                    if (m[y] == -1)     // 發現擴充路徑
                    {
                        path(r, x);
                        m[x] = y; m[y] = x;
                        return true;
                    }
                    else                // 延伸交錯樹
                    {
                        p[y] = x; p[m[y]] = y;
                        d[y] = 1; d[m[y]] = 0;
                        *qb++ = m[y];
                    }
                else
                    if (d[f(y)] == 0)   // 形成花
                    {
                        int b = lca(x, y, r);
                        contract_one_side(x, y, b);
                        contract_one_side(y, x, b);
                    }
                    else                // 只需留一條路徑
                        ;
    return false;
}

