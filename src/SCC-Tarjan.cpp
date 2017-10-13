bool adj[9][9];
int visit[9], low[9], t = 0;
int stack[9], top = 0;  // 堆疊
bool instack[9];        // 記錄DFS forest目前尚存哪些點
int contract[9];        // 每個點收縮到的點
 
void DFS(int i)
{
    visit[i] = low[i] = ++t;
    stack[top++] = i;
    instack[i] = true;
 
    for (int j=0; j<9; ++j)
        if (adj[i][j])
        {
            // tree edge
            if (!visit[j])
                DFS(j);
 
            // tree/back/forward/cross edge
            // 已經遍歷過、但是尚未形成SCC的點
            if (instack[j])
                low[i] = min(low[i], low[j]);
        }
 
    // 形成SCC，從目前的DFS forest移除它。
    // i點會是SCC裡面，最早拜訪的點。
    if (visit[i] == low[i])
    {
        int j;
        do
        {
            j = stack[--top];
            instack[j] = false;
            contract[j] = i;
        } while (j != i);
    }
}
 
void tarjan()
{
    memset(visit, 0, sizeof(visit));
    t = 0;
 
    for (int i=0; i<9; ++i)
        if (!visit[i])
            DFS(i);
}

