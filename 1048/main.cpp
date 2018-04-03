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

class tree
{
    struct node
    {
        int left;
        int right;
        int parent;
        node (int p = 0,int le = -1,int ri = -1):parent(p),left(le),right(ri) {}
    };
    node *elem;
    int size;
public:
    tree(int n){elem = new node [size = n+1];}
    void create_tree()
    {
        int num,le,ri;
        for(int i=0;i<(size-2)/2;++i){
        scanf("%d %d %d",&num,&le,&ri);
        elem[num].left = le;
        elem[num].right = ri;
        elem[le].parent = num;
        elem[ri].parent = num;
        }
    }
    void levelTraverse() const
    {
        int root;
        for(int i=1;i<size;++i)
        {
            if(elem[i].parent == 0) {root = i; break;}
        }
        seqQueue<int> q;
        q.enqueue(root);
        while(!q.isEmpty())
        {
            root = q.dequeue();
            printf("%d\n",root);
            if(elem[root].left != -1)q.enqueue(elem[root].left);
            if(elem[root].right != -1)q.enqueue(elem[root].right);
        }
    }
};
int main()
{
    int n;
    scanf("%d",&n);
     tree t(n);
     t.create_tree();
     t.levelTraverse();
    return 0;
}
