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
class BinaryTree
{
private:
    struct node
    {
        int parent;
        int left;
        int right;
        int weight;
        node(int parent = 0,int le = 0,int ri = 0,int w = 0)
        {
            left = le;
            right = ri;
            weight = w;
        }
    };
    node *elem;
    int size;
public:
    BinaryTree(int &n)
    {
        int p,q,v;
        size = n+1;
        elem = new node [size];
        for(int i=1;i<=n;++i)
        {
            scanf("%d %d %d",&p,&q,&v);
            elem[i].left = p;
            elem[i].right = q;
            elem[i].weight = v;
            elem[p].parent = i;
            elem[q].parent = i;
        }
    }
    void depthTraverse() const
    {
        int root,cur;
        seqQueue<int> q;
        for(int i=1;i<size;++i)
        {
            if(elem[i].parent == 0)
            {
                root = i;
                break;
            }
        }
        q.enqueue(root);
        while(!q.isEmpty())
        {
            cur = q.dequeue();
            printf("%d ",elem[cur].weight);
            if(elem[cur].left)
                q.enqueue(elem[cur].left);
            if(elem[cur].right)
                q.enqueue(elem[cur].right);
        }
    }
};
int main()
{
    int n;
    scanf("%d",&n);
    BinaryTree tree(n);
    tree.depthTraverse();
}
