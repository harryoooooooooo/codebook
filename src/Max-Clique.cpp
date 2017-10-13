const int V = 30;
bool adj[V][V]; // adjacency matrix
struct Set {bool s[30]; int size;};
int maximal_clique = 0;
 
Set intersect(Set S, int p)
{
    for (int i=0; i<V; ++i)
        if (S.s[i] && !adj[p][i])
        {
            S.s[i] = false;
            S.size--;
        }
    return S;
}
 
void backtrack(Set R, Set P , Set X)
{
    if (P.size == 0)
    {
        if (X.size == 0)
        {
            maximal_clique++;
            for (int i=0; i<V; ++i)
                if (R[i])
                    cout << i;
        }
        return;
    }
 
    int pivot;
    for (pivot=0; pivot<V; ++pivot)
        if (P.s[pivot] || X.s[pivot])
            break;
//  if (p == V) return;
 
    for (int i=0; i<V; ++i)
        if (P.s[i] && !adj[pivot][i])
        {
            R.s[i] = true; R.size++;
            backtrack(R, intersect(P,i), intersect(X,i));
            R.s[i] = false; R.size--;
            P.s[i] = false; P.size--;
            if (!X.s[i]) {X.s[i] = true; X.size++;}
        }
}
 
void Bron_Kerbosch()
{
    // 刪除自環
    for (int i=0; i<V; ++i) adj[i][i] = false;
 
    Set R, P, X;
    for (int i=0; i<V; ++i) R.s[i] = false;
    for (int i=0; i<V; ++i) P.s[i] = true;
    for (int i=0; i<V; ++i) X.s[i] = false;
    R.size = 0;
    P.size = V;
    X.size = 0;
    backtrack(R, P, X);
}

