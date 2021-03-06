#include<cstdio>
#include<cassert>
using namespace std;
struct Node
{
    Node *green,*edge[26];
    int max_len;
    Node(const int _max_len):green(NULL),max_len(_max_len){for(int i=0;i<26;i++)edge[i]=NULL;}
}*ROOT,*LAST;
void Extend(const int c)
{
    Node *cursor=LAST;LAST=new Node((LAST->max_len)+1);
    for(;cursor&&!cursor->edge[c];cursor=cursor->green)cursor->edge[c]=LAST;//添加LAST所有的黑色字串 
    if(!cursor)LAST->green=ROOT;//其實圖上沒有畫綠色邊的點，代表著它的綠色邊是直接指向「代表空串的根結點」
    else
    {
        Node *potential_green=cursor->edge[c];//找出最長的綠色字串(為了要讓LAST代表所有後綴組成的字串集合，要決定綠色邊連到哪)，在圖上會走到哪個節點 
        if((potential_green->max_len)==(cursor->max_len+1))LAST->green=potential_green;//剛剛好potential_green代表的字串全部都是LAST的後綴，可以直接利用綠色邊連到potential_green，添加LAST所有的綠色字串 
        else
        {
            assert((potential_green->max_len)>(cursor->max_len+1));//potential_green代表的字串集合中有些不是LAST的後綴
            Node *wish=new Node((cursor->max_len)+1);//從potential_green分離出想要的節點，恰好代表LAST所有的綠色字串 
            for(;cursor&&cursor->edge[c]==potential_green;cursor=cursor->green)cursor->edge[c]=wish;//添加wish所有的黑色字串，同時可能搶走部分potential_green代表的字串集合 
            for(int i=0;i<26;i++)wish->edge[i]=potential_green->edge[i];//讓wish接管原本potential_green黑色邊的功能(防止potential_green下游的節點代表的字串集合中的一些黑色字串，因為potential_green丟掉一些黑色字串而遺失)
wish->green=potential_green->green;//利用綠色邊添加wish所有的綠色字串 
potential_green->green=wish;//利用綠色邊修復potential_green代表的字串集合 
            LAST->green=wish;//利用綠色邊添加LAST所有的綠色字串 
        }
    }
}
char S[10000001],A[10000001];
int N;
int main()
{
    scanf("%d%s",&N,S);
    ROOT=LAST=new Node(0);//SAM的根結點代表空串，max_len當然是0 
    for(int i=0;S[i];i++)Extend(S[i]-'a');
    while(N--)
    {
        scanf("%s",A);
        Node *cursor=ROOT;
        bool ans=true;
        for(int i=0;A[i];i++)
        {
            cursor=cursor->edge[A[i]-'a'];
            if(!cursor){ans=false;break;}//圖上沒有路可以走了，A不是S的子字串 
        }
        puts(ans?"Yes":"No");
    }
    return 0;
}
