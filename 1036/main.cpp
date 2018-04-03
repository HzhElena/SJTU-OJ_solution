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
        data = new T [maxSize];
        front = rear = 0;
    }
    ~seqQueue() {delete [] data;}
    bool isEmpty() const {return rear==front;}
    int getLength() const {return (rear+maxSize-front)% maxSize;}
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
    T dequeue()
    {
        front = (front+1)%maxSize;
        return data[front];
    }
};
void method1(int *a,int N)
{
    seqQueue<int> s[3];
    int minn,minn_number;
    for(int i=0;i<N;++i)
    {
        minn = s[0].getLength();
        minn_number = 0;
        for(int j=1;j<3;++j)
            if(s[j].getLength() < minn)
                {
                    minn = s[j].getLength();
                    minn_number = j;
                }
        s[minn_number].enqueue(a[i]);
    }
    long long waitTotal = 0,final_time = 0;
    int last = 0,maxn_last = 0;
    for(int i=0;i<3;++i)
    {
        last = 0;
        while(!s[i].isEmpty())
        {
            last += s[i].dequeue();
            waitTotal += last;
        }
        waitTotal -= last;
        if(last > maxn_last) maxn_last = last;
    }
    cout<<waitTotal<<" "<<maxn_last<<endl;
}
void method2(int *a,int N)
{
    long long avail[3]={0,0,0};
    int tmp = 0;
    long long waitTotal = 0;
    for(int i=0;i<N;++i)
    {
        if(avail[0] <= avail[1] && avail[0] <= avail[2]) tmp = 0;
        else if(avail[1] <= avail[2] && avail[1] <= avail[0]) tmp = 1;
        else tmp = 2;
        waitTotal += avail[tmp];
        avail[tmp] += a[i];
    }
    if(avail[0] >= avail[1] && avail[0] >= avail[2]) tmp = 0;
    else if(avail[1] >= avail[2] && avail[1] >= avail[0]) tmp = 1;
    else tmp = 2;
    cout<<waitTotal<<" "<<avail[tmp];
}
int main()
{
    int N;
    cin>>N;
    int a[N];
    for(int i=0;i<N;++i)
        scanf("%d",&a[i]);
    method1(a,N);
    method2(a,N);
    return 0;
}
