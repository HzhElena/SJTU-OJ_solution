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
            if(data[child] < tmp) data[hole] = data[child];
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
    void enqueue(const T &x)
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
template<class T>
class seqStack
{
private:
    T *data;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10) {
        data = new T[initSize];
        maxSize =initSize;
        top_p = -1;
    }
    ~seqStack(){delete[] data;}
    bool isEmpty() const{return top_p==-1;}
    void push(const T &x)
    {
        if(top_p == maxSize-1) doubleSpace();
        data[++top_p] = x;
    }
    T top() const
    {
        return data[top_p];
    }
    T pop()
    {
        return data[top_p--];
    }
};
template<class T>
void seqStack<T>::doubleSpace()
{
    T *tmp = data;
    maxSize *= 2;
    data = new T [maxSize];
    for(int i=0;i<maxSize;++i)
        data[i] = tmp[i];
    delete [] tmp;
}

const int maxn = 100000+5;
long long relation[maxn];
int degree[maxn];

char getNum(int &value)
{
    value = 0;
    char ch = getchar();
    while(ch==' ') ch = getchar();
    while(ch<='9' && ch>='0')
    {
        value = value*10 + ch - '0';
        ch = getchar();
    }
    return ch;
}
 void create()
    {
        priorityQueue<int> q;
        seqStack<int> s;
        int pre,tmp,value;
        char ch;
        int n=0;
        while((ch = getchar())!=EOF)
        {
            while(ch==' ') ch = getchar();
            if(ch == EOF) break;
            if(ch == '(')
            {
                ch = getNum(value);
                if(!s.isEmpty())
                {
                    pre = s.top();
                    relation[pre] += value;
                    relation[value] += pre;
                    ++degree[pre];
                    ++degree[value];
                }
                s.push(value);
            }
            if(ch == ')')
            {
                tmp = s.pop();
                ++n;
                if(degree[tmp] == 1)
                    q.enqueue(tmp);
            }
        }
        while(--n)
        {
            tmp = q.dequeue();
            int last = relation[tmp];
            printf("%d ",last);
            --degree[last];
            relation[last] -= tmp;
            if(degree[last] == 1)
                q.enqueue(last);
        }
    }
int main()
{
    create();
    return 0;
}
