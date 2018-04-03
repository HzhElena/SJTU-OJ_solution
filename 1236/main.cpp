#include <iostream>
#include <cstdio>
using namespace std;
template<class T>
class seqQueue
{
private:
    T *data;
    int maxSize;
    int front;
    int rear;
    void doubleSpace()
    {
        T *tmp = data;
        data = new T[maxSize*2];
        for(int i=1;i<maxSize;++i)
            data[i] = tmp[(front+i)%maxSize];
        front = 0;
        rear = maxSize-1;
        maxSize *= 2;
        delete tmp;
    }
public:
    seqQueue(int init = 10) {
        maxSize = init;
        data = new T[maxSize];
        front = rear = 0;
    }
    ~seqQueue() {delete [] data;}
    bool isEmpty() const {return rear==front;}
    void enqueue(const T &x)
    {
        if((rear+1)%maxSize == front)
            doubleSpace();
        rear = (rear+1)%maxSize;
        data[rear] = x;
    }
    T getHead() const
    {
        return data[(front+1)%maxSize];
    }
    T getTail() const
    {
        return data[rear];
    }
    T dequeue()
    {
        front = (front+1)%maxSize;
        return data[front];
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
    void dijkstra(int start,int endd)
    {
        int *distance = new int [vers];
        int noEdge = 100000000,cur;
        edgeNode *p;
        for(int i=0;i<vers;++i)
            distance[i] = noEdge;
        distance[start] = 0;
        seqQueue<int> q;
//        cout<<"start: "<<start<<endl;
        q.enqueue(start);
        while(!q.isEmpty())
        {
            cur = q.dequeue();
//            cout<<"cur: "<<cur<<endl;
            p = verList[cur].head;
            while(p)
            {
                if(distance[p->end] > distance[cur] + p->weight)
                    { distance[p->end] = distance[cur] + p->weight; q.enqueue(p->end);}
                p = p->next;
            }
        }
        cout<<distance[endd];
    }
};
int main()
{
    int n,m,start,endd,a,b,w;
    scanf("%d %d %d %d",&n,&m,&start,&endd);
    adjLinkGraph<int,int> graph(n);
    for(int i=0;i<m;++i)
    {
        scanf("%d %d %d",&a,&b,&w);
        graph.insert(a-1,b-1,w);
    }
    graph.dijkstra(start-1,endd-1);
    return 0;
}
