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
struct node
{
    friend bool operator<(const node &n1,const node &n2)
    {
        return n1.weight<n2.weight;
    }
    int index;
    int weight;
};
const int maxn = 202000;
int parent[maxn],weight[maxn];
int main()
{
    long long ans = 0;
    bool flag = false;
    int N,M,t,zero,cur,sum;
    node tmp;
    priorityQueue<node> q;
    scanf("%d %d",&N,&M);
    zero = (1-N)%(M-1);
    while(zero<0)
        zero += M-1;
    int length = 2*(N+zero);
    for(int i=N+zero;i<length-zero;++i)
    {
        scanf("%d",&t);
        weight[i] = t;
        tmp.weight = t;
        tmp.index = i;
        q.enQueue(tmp);
    }
    for(int i=length-zero;i<length;++i)
    {
        tmp.weight = 0;
        tmp.index = i;
        q.enQueue(tmp);
    }
    cur = N+zero-1;
    while(!q.isEmpty())
    {
        flag = false;
        sum = 0;
        for(int i=0;i<M;++i)
        {
            tmp = q.dequeue();
            sum += tmp.weight;
            parent[tmp.index] = cur;
            if(q.isEmpty()) {flag = true;break;}
        }
        parent[cur] = cur;
        tmp.index = cur--;
        tmp.weight = sum;
        if(flag) {break;}
        q.enQueue(tmp);
    }
    if(flag) parent[tmp.index] = 0;
    for(int i=N+zero;i<length-zero;++i)
    {
        int pa = parent[i],len = 0;
        while(pa!=0)
        {
            ++len;
            pa = parent[pa];
        }
        ans += len * weight[i];
    }
    cout<<ans;
    return 0;
}
