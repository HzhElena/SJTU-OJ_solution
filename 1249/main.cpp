#include <iostream>

using namespace std;
class node
{
    friend bool operator <=(const node &a,const node &b)
    {
        if(a.x*b.y <= a.y*b.x)
            return true;
        return false;
    }
        friend bool operator >= (const node &a,const node &b)
    {
        if(a.x*b.y >= a.y*b.x)
            return true;
        return false;
    }
     friend bool operator <(const node &a,const node &b)
    {
        if(a.x*b.y < a.y*b.x)
            return true;
        return false;
    }
public:
    int x;
    int y;
public:
    node(int xx = 1,int yy = 1) {
        x = xx;
        y = yy;
        for(int i=xx;i>1;--i)
        {
            if(x%i == 0 && y%i == 0)
            {
                x/=i;
                y/=i;
            }
        }
    }
};
void quickSort(node s[],int l,int r)
{
    if(l<r)
    {
        int i=l,j=r;
        node x=s[l];
        while(i<j)
        {
            while(i<j && s[j]>=x)
                --j;
            if(i<j)
                s[i] = s[j];
            while(i<j && s[i]<=x)
                ++i;
            if(i<j)
                s[j] = s[i];
        }
        s[i] = x;
        quickSort(s,l,i-1);
        quickSort(s,i+1,r);
    }
}
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

int main()
{
    int n;
    cin>>n;
    int total =(n+1)*n/2 + 1;
    node a[total];
    int k=1;
    a[0].x = 1;
    a[0].y = 1;
    for(int i=0;i<n;++i)
        for(int j=i+1;j<=n;++j)
    {
        node tmp(i,j);
        a[k] = tmp;
        ++k;
     //   cout<<i<<"/"<<j<<endl;
    }
    quickSort(a,0,total-1);
    seqQueue<node> q;
    for(int i=0;i<total;++i)
    {
        if(q.isEmpty() || q.getTail()<a[i])
            q.enqueue(a[i]);
    }
    node cur;
    while(!q.isEmpty()){
            cur = q.dequeue();
            if(cur.x==0) cur.y = 1;
        cout<<cur.x<<"/"<<cur.y<<endl;
    }
    return 0;
}

