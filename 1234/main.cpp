#include <iostream>
#include <cstdio>
using namespace std;
template<class T>
class priorityQueue
{
private:
    T *data;
    int maxSize;
    int currentSize;
    void doubleSpace()
    {
        T *tmp = data;
        maxSize *= 2;
        data = new T[maxSize];
        for(int i=0;i<=currentSize;++i)
            data[i] = tmp[i];
        delete [] tmp;
    }
    void buildheap()
    {
        for(int i=currentSize/2;i>0;--i)
            percolateDown(i);
    }
    void percolateDown(int hole)
    {
        int child;
        T tmp = data[hole];
        for(;hole*2<=currentSize; hole = child)
        {
            child = hole*2;
            if(child != currentSize && data[child+1] < data[child])
                ++child;
            if(data[child]<tmp) data[hole] = data[child];
            else break;
        }
        data[hole] = tmp;
    }
public:
    priorityQueue(int capacity = 100)
        {data = new T[capacity]; currentSize = 0;maxSize = capacity; }
    priorityQueue(const T d[],int size)
    {
        maxSize = size+10;
        currentSize = size;
        data = new T[maxSize];
        for(int i=0;i<size;++i)
            data[i+1] = d[i];
        buildheap();
    }
    ~priorityQueue() {delete [] data;}
    bool isEmpty() {return currentSize == 0;}
    void enQueue(const T &x)
    {
        if(currentSize == maxSize-1)
            doubleSpace();
        int hole = ++currentSize;
        for(;hole>1 && x<data[hole/2];hole /= 2)
            data[hole] = data[hole/2];
        data[hole] = x;
    }
    T dequeue()
    {
        T minn = data[1];
        data[1] = data[currentSize--];
        percolateDown(1);
        return minn;
    }
    T getHead() const{return data[1];}
};
class DisjointSet
{
    int size;
    int *parent;
public:
    DisjointSet(int s){
        size = s;
        parent = new int [size];
        for(int i=0;i<size;++i)
            parent[i] = -1;
    }
    int find(int target)
    {
        if(parent[target]<0)
            return target;
        return (parent[target] = find(parent[target]));
    }
    void Union(int root1,int root2)
    {
        if(root1 == root2) return;
        if(parent[root1] > parent[root2])
        {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
        else
        {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }
};
template<class TypeOfVer,class TypeOfEdge>
class adjLinkGraph
{
private:
    struct edgeNode
    {
        int end;
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode(int e,TypeOfEdge w,edgeNode *n=NULL)
        {
            end =e;
            weight = w;
            next = n;
        }
    };
    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h = NULL)
        {
            head = h;
        }
    };
    verNode *verList;
    int vers;
    int edges;
public:
    adjLinkGraph(int vsize)
    {
        vers = vsize;
        verList = new verNode[vers];
        for(int i=0;i<vers;++i)
        {
            verList[i].ver = i+1;
        }
    }
    ~adjLinkGraph()
    {
        int i;
        edgeNode *p;

        for(i=0;i<vers;++i)
            while((p=verList[i].head)!=NULL)
            {
                verList[i].head = p->next;
                delete p;
            }
        delete [] verList;
    }
    bool insert(int u,int v,TypeOfEdge w)
    {
        verList[u].head = new edgeNode(v,w,verList[u].head);
        ++edges;
        return true;
    }
    struct edge
    {
        int b;
        int e;
        int weight;
        bool operator < (const edge& other) const
        {
            return (weight < other.weight);
        }
    };
    void kruskal() const
    {
        DisjointSet s(vers);
        int cnt = 0,res = 0;
        edge tmp;
        edgeNode *p;
        priorityQueue<edge> q;
        for(int i=0;i<vers;++i)
        {
            p = verList[i].head;
            while(p)
            {
                tmp.b = i;
                tmp.e = p->end;
                tmp.weight = p->weight;
                q.enQueue(tmp);
                p = p->next;
            }
        }
        while(cnt < vers-1)
        {
            tmp = q.dequeue();
            int t1 = s.find(tmp.b),t2 = s.find(tmp.e);
            if(t1 != t2)
            {
                s.Union(t1,t2);
                res += tmp.weight;
                ++cnt;
            }
        }
        cout<<res;
    }
};
int main()
{
    int n,m,a,b,w;
    scanf("%d %d",&n,&m);
    adjLinkGraph<int,int> graph(n);
    for(int i=0;i<m;++i)
    {
        scanf("%d %d %d",&a,&b,&w);
        graph.insert(a-1,b-1,w);
        graph.insert(b-1,a-1,w);
    }
    graph.kruskal();
    return 0;
}
