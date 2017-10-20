const int X = 9, Y = 9;
bool adj[9][9]; // adjacency matrix
bool mx[9], my[9];
int cx[9], cy[9];
bool ix[9], iy[9];  // independent set

bool match(int x)
{
    for (int y=0; y<Y; ++y)
        if (adj[x][y] && !my[y])
        {
            my[y] = true;
            if (cy[y] == -1 || match(cy[y]))
            {
                cx[x] = y; cy[y] = x;
                return true;
            }
        }
    return false;
}

int maximum_cardinality_bipartite_matching()
{
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));

    int c = 0;
    for (int x=0; x<X; ++x)
    {
        memset(my, false, sizeof(my));
        if (match(x)) c++;
    }
    return c;
}

void DFSx(int x)
{
    ix[x] = true;   // even distance vertex
    for (int y=0; y<Y; ++y)
        if (adj[x][y] && !my[y])
        {
            my[y] = true;
            if (cy[y] != -1) DFSx(cy[y]);
        }
}

void DFSy(int y)
{
    iy[y] = true;   // even distance vertex
    for (int x=0; x<X; ++x)
        if (adj[x][y] && !mx[x])
        {
            mx[x] = true;
            if (cx[x] != -1) DFSy(cx[x]);
        }
}

void maximum_independent_set()
{
    maximum_cardinality_bipartite_matching();

    // 建立X側未匹配點的交錯樹們
    memset(ix, false, sizeof(ix));
    memset(my, false, sizeof(my));
    for (int x=0; x<X; ++x)
        if (cx[x] == -1)
            DFSx(x);

    // 建立Y側未匹配點的交錯樹們
    memset(iy, false, sizeof(iy));
    memset(mx, false, sizeof(mx));
    for (int y=0; y<Y; ++y)
        if (cy[y] == -1)
            DFSy(y);

    // X側未匹配點的交錯樹們＋層層疊疊的交錯環們
    for (int x=0; x<X; ++x)
        if (ix[x] || (cx[x] != -1 && !mx[x] && !my[cx[x]]))
            cout << "選中X側的第" << x << "點";

    // Y側未匹配點的交錯樹們
    for (int y=0; y<Y; ++y)
        if (iy[y])
            cout << "選中Y側的第" << y << "點";
}
