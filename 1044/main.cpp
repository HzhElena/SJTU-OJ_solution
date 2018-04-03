#include <iostream>
#include <cstdio>
#include <cstring>
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
        for(int i = 0;i<=currentSize;++i)
            data[i] = tmp[i];
        delete [] tmp;
    }
    void percolateDown(int hole)
    {
        T tmp = data[hole];
        int child;
        for(;hole*2 <= currentSize;hole = child)
        {
            child = hole*2;
            if(child != currentSize && data[child+1]>data[child])
                ++child;
            if(tmp < data[child])
                data[hole] = data[child];
            else break;
        }
        data[hole] = tmp;
    }
    void buildheap()
    {
        for(int i=currentSize/2;i>0;--i)
            percolateDown(i);
    }
public:
    priorityQueue(int init = 100) {maxSize = init;currentSize = 0;data = new T[maxSize];}
    priorityQueue(T *d,int size)
    {
        maxSize = size+10;
        currentSize = size;
        data = new T[maxSize];
        for(int i=0;i<size;++i)
            data[i+1] = d[i];
        buildheap();
    }
    ~priorityQueue() {delete [] data;}
    bool isEmpty() const {return currentSize == 0;}
    T getHead() const {return data[1];}
    void enqueue(const T &x)
    {
        if(currentSize == maxSize-1)
            doubleSpace();
        int hole = ++currentSize;
        for(;hole>1 && data[hole/2] < x;hole/=2)
            data[hole] = data[hole/2];
        data[hole] = x;
    }
    T dequeue()
    {
        T maxn = data[1];
        data[1] = data[currentSize--];
        percolateDown(1);
        return maxn;
    }
};
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


struct resource
{
    int f;
    int w;
    int rank;
    char *name;
    bool operator < (const resource &other)
    {
        return rank<other.rank;
    }
    bool operator >(const resource &other)
    {
        return rank>other.rank;
    }
    resource(char *n = NULL,int ff = 0,int ww = 0,int r = 0):name(n),f(ff),w(ww),rank(r) {}
    resource(const resource &other)
    {
        name = new char[strlen(other.name)+1];
        strcpy(name,other.name);
        f = other.f;
        w = other.w;
        rank = other.rank;
    }
};

seqQueue<int> food;
seqQueue<int> wood;

int main()
{
    int K,num,farmer = 0;
    int total_food = 0,total_wood = 0;
    scanf("%d",&K);
    resource total_resource[K],re;
    char ex[25];
    for(int i=0;i<K;++i)
    {
        int f,w,r;
        scanf("%s",ex,25);
        total_resource[i].name = new char[strlen(ex)+1];
        strcpy(total_resource[i].name,ex);
        cout<<total_resource[i].name<<endl;
        scanf("%d %d %d",&total_resource[i].f,&total_resource[i].w,&total_resource[i].rank);
    }
    int N;
    scanf("%d",&N);
    for(int j=1;j<=N;++j)
    {
        scanf("%s",ex,25);
        scanf("%d",&num);
        num += farmer;
        switch(ex[0])
        {
        case 'f':
            food.enqueue(num);
            total_food += num;
            break;
        case 'w':
            wood.enqueue(num);
            total_wood += num;
            break;
        }
        priorityQueue<resource> q;
        for(int i=0;i<K;++i)
        {
            if(total_resource[i].f <= total_food && total_resource[i].w <= total_wood)
            {
                q.enqueue(total_resource[i]);
            }
        }
        if(!q.isEmpty())
        {
            re = q.dequeue();
            if(strcmp(re.name,"farmer")==0)
                ++farmer;
        int sub_food = re.f,sub_wood = re.w;
        while(sub_food > 0)
        {
            int tmp = food.dequeue();
            sub_food -= tmp;
            total_food -= tmp;
        }
        while(sub_wood > 0)
        {
            int tmp = wood.dequeue();
            sub_wood -= tmp;
            total_wood -= tmp;
        }
        printf("#%d: a ",j);
        printf("%s",re.name);
        printf(" was created.\n");
        }
    }
    printf("food: %d, wood: %d",total_food,total_wood);
    return 0;
}
