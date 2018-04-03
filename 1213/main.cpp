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
class BinaryTree;
bool isEqual(const BinaryTree &tree1,const BinaryTree &tree2);
class BinaryTree
{
    friend bool isEqual(const BinaryTree &tree1,const BinaryTree &tree2)
    {
        if(tree1.size != tree2.size)
            return 0;
        seqQueue<int> q1,q2;
        int root1,root2;
        for(int i=1;i<tree1.size;++i)
        {
            if(tree1.elem[i].parent == 0)
            {
                root1 = i;
                break;
            }
        }
        q1.enqueue(root1);
        for(int i=1;i<tree2.size;++i)
        {
            if(tree2.elem[i].parent == 0)
            {
                root2 = i;
                break;
            }
        }
        q2.enqueue(root2);
        int cur1,cur2;
        while(!q1.isEmpty() && !q2.isEmpty())
        {

            cur1 = q1.dequeue();
            cur2 = q2.dequeue();
            if(tree1.elem[cur1].weight != tree2.elem[cur2].weight)
                return 0;
            if(tree1.elem[cur1].left != 0)
                q1.enqueue(tree1.elem[cur1].left);
            if(tree1.elem[cur1].right != 0)
                q1.enqueue(tree1.elem[cur1].right);
            if(tree2.elem[cur2].left != 0)
                q2.enqueue(tree2.elem[cur2].left);
            if(tree2.elem[cur2].right != 0)
                q2.enqueue(tree2.elem[cur2].right);
        }
        if(!q1.isEmpty() || !q2.isEmpty())
            {return 0;}
        return 1;
    }
private:
    struct node
    {
        int parent;
        int left;
        int right;
        int weight;
        node(int pa = 0,int le = 0,int ri = 0,int w = 0)
        {
            parent = pa;
            left = le;
            right = ri;
            weight = w;
        }
        node(const node &other)
        {
            parent = other.parent;
            left = other.left;
            right = other.right;
            weight = other.weight;
        }
    };
    node *elem;
    int root;
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
    BinaryTree(const BinaryTree &other)
    {
        root = other.root;
        size = other.size;
        elem = new node [size];
        for(int i=0;i<size;++i)
            elem[i] = other.elem[i];
    }
    BinaryTree & operator = (const BinaryTree &other)
    {
        if(this ==  &other)
            return *this;
        root = other.root;
        size = other.size;
        elem = new node [size];
        for(int i=0;i<size;++i)
            elem[i] = other.elem[i];
        return *this;
    }
};
int main()
{
    int n,m;
    scanf("%d",&n);
    BinaryTree tree1(n);
    scanf("%d",&m);
    BinaryTree tree2(m);
    if(m != n)
    {
        printf("%s","N");
        return 0;
    }
    else
    {
        cout<<(isEqual(tree1,tree2) ? "Y":"N");
    }
    return 0;
}
