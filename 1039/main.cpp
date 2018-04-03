#include <iostream>
#include <cstdio>
using namespace std;
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

class tree
{
    struct node
    {
        int left;
        int right;
        int data;
        int time;
        node (int le = -1,int ri = -1,int d = 0,int t=0):left(le),right(ri),data(d),time(t) {}
    };
    node *elem;
    int size;
public:
    tree(int n){elem = new node [size = n+1];}
    void create_tree()
    {
        int num,le,ri;
        for(int i=1;i<size;++i){
        scanf("%d %d %d",&num,&le,&ri);
        elem[num].left = le;
        elem[num].right = ri;
        }
    }
    void sequence() const
    {
        seqQueue<int> q;
        q.enqueue(1);
        int cur,tmp;
        elem[1].data = 1;
        while(!q.isEmpty())
        {
            cur = q.dequeue();
            if(elem[cur].left != -1) {
                   tmp =  elem[cur].left;
                    q.enqueue(tmp);
                    elem[tmp].data = elem[cur].data*2;
            }
            if(elem[cur].right != -1){
                tmp = elem[cur].right;
                q.enqueue(tmp);
                elem[tmp].data = elem[cur].data*2+1;
            }
        }
        for(int i = 1;i<size;++i)
            printf("%d ",elem[i].data);
        printf("\n");
    }
    void postOrder() const
    {
        seqStack<int> s;
        if(size<=1) return;
        s.push(elem[1].data);
        int cur;
        while(!s.isEmpty())
        {
            cur = s.pop();
            if(++elem[cur].time==1)
            {
                s.push(cur);
                if(elem[cur].left!=-1) s.push(elem[cur].left);
            }
            else if(elem[cur].time==2)
            {
                s.push(cur);
                if(elem[cur].right!=-1) s.push(elem[cur].right);
            }
            else
            {
                printf("%d ",cur);
            }
        }
    }
};
int main()
{
    int n;
    scanf("%d",&n);
    tree t(n);
    t.create_tree();
    t.sequence();
    t.postOrder();
    return 0;
}
