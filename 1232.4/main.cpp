#include <iostream>
#include <cstdio>
#define FOR(i,low,high) for(int i=low;i<=high;++i)
#define RFOR(i,low,high) for(int i=high;i>=low;--i)
#define SCInt(x) scanf("%d",&x)
#define SCAInt(a,i) scanf("%d",&a[i])
#define SCAAInt(a,i,j) scanf("%d",&a[i][j])
#define ENTER printf("\n")
#define SPACE printf(" ")
#define PRInt(x) printf("%d",x)
#define PRIntS(x) printf("%d ",x)
#define PRAInt(a,i) printf("%d",a[i])
#define PRAIntS(a,i) printf("%d ",a[i])
#define MAX_INT 0xffffff
using namespace std;
int N, A, B;
int *result,*cur,*parent,**maze, *indexOfx,*indexOfy;
int res = 0;
bool nopath = true;
int Find(int x)
{
    int root = x;
    if (parent[root] < 0) return root;
    while (parent[root] > 0)
    root = parent[root];
    while (x != root)
    {
        int tmp = parent[x];
        parent[x] = root;
        x = tmp;
    }
    return root;
}
bool Union(int x, int y)
{
    int root1 = Find(x);
    int root2 = Find(y);
    if (root1 == root2) return false;
    if (parent[root1] > parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
    return true;
}
template <class VerType, class EdgeType>
class adjListGraph
{
private:
      struct edgeNode
    {
        int dest;
        EdgeType weight;
        edgeNode *next;
        edgeNode(int e,EdgeType w,edgeNode *n=NULL)
        {
            dest =e;
            weight = w;
            next = n;
        }
    };
    struct verNode
    {
        VerType ver;
        edgeNode *head;
        verNode(edgeNode *h = NULL)
        {
            head = h;
        }
    };
    verNode *verList;
    int verts;
    int edges;
public:
    adjListGraph(int vSize = 0)
    {
        verts = vSize;
        edges = 0;
        verList = new verNode[vSize];
    }
    bool insert(int u,int v,EdgeType w)
    {
        verList[u].head = new edgeNode(v,w,verList[u].head);
        ++edges;
        return true;
    }
    void find_path(int start, int dest)
    {
        bool *visited = new bool[verts];
        for (int i=0; i<verts; ++i)
            visited[i] = false;
        int current = 0;
        dfs(start, dest, visited, current);
        FOR(i,0,res-1)
            { PRAInt(result,i); SPACE;}
    }
    void dfs(int start, int target, bool visited[], int &curLen)
    {
        int minn = MAX_INT,second_min = MAX_INT;
        edgeNode *p = verList[start].head;
        cur[curLen++] = start;
        visited[start] = true;
        if (start == target)
        {
            res = curLen;
            FOR(i,0,res-1)
                result[i] = cur[i];
            return;
        }
        nopath = true;
        while (p != NULL)
        {
            if (!visited[p->dest])
            {
                if (p->dest < minn)
                {
                    nopath = false;
                    second_min = minn;
                    minn = p->dest;
                }
                else
                {
                    nopath = false;
                    p = p->next;
                    continue;
                }
                if(nopath) minn = second_min;
                dfs(p->dest,target,visited,curLen);
                --curLen;
                visited[p->dest] = false;
            }
            p = p->next;
        }
    }
};

int main()
{
    SCInt(N);
    SCInt(A);
    SCInt(B);
    int tmp = N*(N+1)/2+1;
    adjListGraph<int, int> graph(tmp);

    parent = new int[tmp];
    maze = new int*[N+1];
    indexOfx = new int[tmp];
    indexOfy = new int[tmp];
    result = new int[tmp];
    cur = new int[tmp];

    int cnt = 1;
    FOR(i,0,tmp-1)
        parent[i] = -1;
    FOR(i,1,N)
    {
        maze[i] = new int[N+1];
        for (int j=1; j<=i; ++j)
        {
            maze[i][j] = cnt;
            indexOfx[cnt] = i;
            indexOfy[cnt] = j;
            ++cnt;
        }
    }

    while (Find(A) != Find(B))
    {
        int a, b;
        scanf("%d %d", &a, &b);
        int x = indexOfx[a], y = indexOfy[a];
        switch(b)
        {
            case 0:
                if (x < 2 || y < 2) continue;
                Union(maze[x-1][y-1], maze[x][y]);
                graph.insert(maze[x-1][y-1], maze[x][y], 1);
                graph.insert(maze[x][y], maze[x-1][y-1], 1);
                break;
            case 1:
                if (x < 2 || y > x-1) continue;
                Union(maze[x-1][y], maze[x][y]);
                graph.insert(maze[x-1][y], maze[x][y], 1);
                graph.insert(maze[x][y], maze[x-1][y], 1);
                break;
            case 2:
                if (x >= N) continue;
                Union(maze[x+1][y], maze[x][y]);
                graph.insert(maze[x+1][y], maze[x][y], 1);
                graph.insert(maze[x][y], maze[x+1][y], 1);
                break;
            case 3:
                if (x >= N || y >= N) continue;
                Union(maze[x+1][y+1], maze[x][y]);
                graph.insert(maze[x+1][y+1], maze[x][y], 1);
                graph.insert(maze[x][y], maze[x+1][y+1], 1);
        }
    }
    graph.find_path(A,B);
    return 0;
}
