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
        int num;
        node(int p = 0,int le = 0,int ri = 0,int n = 0)
        {
            parent = p;
            left = le;
            right = ri;
            num = n;
        }
    };
    node *elem;
    int size;
public:
    BinaryTree(int n)
    {
        size = n + 1;
        elem = new node [size];
        int p,q,cur = 1;
        while(n--){
            scanf("%d %d",&p,&q);
            elem[cur].left = p;
            elem[cur].right = q;
            elem[p].parent = cur;
            elem[q].parent = cur;
            ++cur;
        }
    }
    bool isCompleteTree() const
    {
        int root,last = 1,cur = 0,tmp;
        seqQueue<int> q;
        for(int i=1;i<size;++i)
        {
            if(cur > 1)
                return false;
            if(elem[i].parent == 0)
               {
                    root = i;
                    ++cur;
                }
        }
        elem[root].num = 1;
        q.enqueue(root);
        while(!q.isEmpty())
        {
            tmp = q.dequeue();
            if(elem[tmp].left)
            {
                cur = elem[tmp].left;
                last = elem[cur].num = elem[tmp].num * 2;
                q.enqueue(cur);
            }
            if(elem[tmp].right)
            {
                cur = elem[tmp].right;
                last = elem[cur].num = elem[tmp].num * 2 + 1;
                q.enqueue(cur);
            }
        }
        return last == (size-1);
    }
};
int main()
{
    int n;
    scanf("%d",&n);
    BinaryTree tree(n);
    cout<<(tree.isCompleteTree() ? 'Y':'N');
    return 0;
}

