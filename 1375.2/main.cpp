#include <iostream>
#include <cstdio>
#include <cstring>
#define LL long long
#define FOR(i,low,high) for(int i=low;i<=high;++i)
#define RFOR(i,low,high) for(int i=high;i>=low;--i)
#define FORStep(i,low,high,step) for(int i=low;i<=high;i+=step)
#define RFORStep(i,low,high,step) for(int i=high;i>=low;i-=step)
#define SCInt(x) scanf("%d",&x)
#define SCAInt(a,i) scanf("%d",&a[i])
#define SCAAInt(a,i,j) scanf("%d",&a[i][j])
#define ENTER printf("\n")
#define SPACE printf(" ")
#define PRInt(x) printf("%d",x)
#define PRIntS(x) printf("%d ",x)
#define PRAInt(a,i) printf("%d",a[i])
#define PRAIntS(a,i) printf("%d ",a[i])
#define PRAAInt(a,i,j) printf("%d",a[i][j])
#define PRfloat(x) printf("%f",x)
#define MSET(a,i) memset(a,i,sizeof(a))
#define SWAP(a,b) {a=a^b;b=a^b;a=a^b;}
using namespace std;
const int maxn = 40000+5;
struct edge
{
    int to;
    int next;
};
int head[maxn],n,root;
edge edges[maxn];
int father[maxn][16],vis[maxn],deep[maxn];
int sb[16];
int tmp=0;
void add(int a,int b)
{
    edges[tmp].to = b;
    edges[tmp].next = head[a];
    head[a] = tmp;
    ++tmp;
}
void read()
{
    int a,b;
    SCInt(n);
    FOR(i,0,n-1) {
        SCInt(a);SCInt(b);
        if(a==-1)
            root = b;
        else if(b==-1)
            root = a;
        else {add(a,b); add(b,a);}
    }
}
void bfs()
{
    int q[maxn],tmp = 0,tail = 1;
    q[0] = root;
    deep[root] = 0;
    vis[root] = 1;
    while(tmp<tail)
    {
        int cur = q[tmp++];
        int p = head[cur];
        for(int i=1;i<=15;++i)
        {
            if(sb[i]<=deep[cur])
                father[cur][i] = father[father[cur][i-1]][i-1];
            else break;
        }
        while(p!=0)
        {
            if(!vis[edges[p].to])
            {
                int t = edges[p].to;
                deep[t] = deep[p]+1;
                father[t][0] = cur;
                vis[t] = 1;
                q[tail++] = t;
            }
            p = edges[p].next;
        }
    }
}
int lca(int a,int b)
{
    if(deep[a] < deep[b]) SWAP(a,b);
    int t = deep[a]-deep[b];
    FOR(i,0,15){
        if(t & sb[i])
            a = father[a][i];
    }
    RFOR(i,15,0)
        {
            if(father[a][i] != father[b][i])
            {
                a = father[a][i];
                b = father[b][i];
            }
        }
    if(a==b) return b;
    return father[a][0];
}
int main()
{
    sb[0] = 1;
    FOR(i,1,15)
        sb[i] = sb[i-1]<<1;
    read();
    int m,a,b;
    SCInt(m);
    bfs();
    FOR(i,0,m-1)
    {
        SCInt(a);SCInt(b);
        int res = lca(a,b);
        if(a==res && b!=res) PRInt(1);
        else if(b==res && a!=res) PRInt(2);
        else PRInt(0);
        ENTER;
    }
    return 0;
}
