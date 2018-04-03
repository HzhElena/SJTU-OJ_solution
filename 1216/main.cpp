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
    int find(const T &x)
    {
        int minn = -1,min_num;
        for(int i=1;i<=currentSize;++i)
        {
            if( (data[i] < minn || minn == -1) && data[i] > x)
            {
                minn = data[i];
                min_num = i;
            }
        }
        return min_num;
    }
    void decrease(int i,int v)
    {
        T tmp;
        int hole = i;
        data[hole] -= v;
        for(tmp = data[hole];hole > 1 && tmp < data[hole/2];hole /= 2)
            data[hole] = data[hole/2];
        data[hole] = tmp;
    }
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
int main()
{
    int m,x,v;
    priorityQueue<int> q;
    scanf("%d",&m);
    char ex[12];
    while(m--)
    {
        scanf("%s",&ex);
        if(ex[0] == 'i')
        {
            scanf("%d",&x);
            q.enQueue(x);
        }
        else if(ex[0] == 'f')
        {
            scanf("%d",&x);
            printf("%d\n",q.find(x));
        }
        else
        {
            scanf("%d %d",&x,&v);
            q.decrease(x,v);
        }
    }
    return 0;
}
