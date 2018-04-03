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
class tree
{
    struct node
    {
        int weight;
        node *child;
        node *brother;
        node *parent;
        node(int w = 0,node *p = NULL,node *s = NULL,node *b = NULL):weight(w),parent(p),child(s),brother(b) {}
        bool operator < (const node &n)
        {
            return weight<n.weight;
        }
        ~node() {}
        node (const node &other)
        {
            weight = other.weight;
            child = other.child;
            brother = other.brother;
            parent = other.parent;
        }
    };
    struct leaf
    {
        friend  bool operator < (const leaf &n1,const leaf &n2)
        {
            return n1.weight > n2.weight;
        }
//        friend  bool operator < (const  leaf *n1,const  leaf *n2)
//        {
//            return n1->weight > n2->weight;
//        }
        node *cur;
        int weight;
//        leaf *next;
        leaf(node *c = NULL,int w = 0):cur(c),weight(w) {}
        leaf(const leaf &other)
        {
            cur = other.cur;
            weight = other.weight;
        }
    };
    node *root;
public:
    tree():root(NULL) {}
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
        priorityQueue<leaf> q;
        seqStack<node *> s;
        node *tmp,*pre;
        char ch;
        int n=0;
        while((ch = getchar())!=EOF)
        {
            while(ch==' ') ch = getchar();
            if(ch == '(')
            {
                int value;
                ch = getNum(value);
                tmp = new node(value);
                if(!s.isEmpty())
                {
                    pre = s.pop();
                    tmp->parent = pre;
                    if(pre->child == NULL)
                        pre->child = tmp;
                    else
                    {
                        node *s = pre->child;
                        while(s->brother != NULL)
                            s = s->brother;
                        s->brother = tmp;
//                        tmp->brother = pre->child;
//                        pre->child = tmp;
                    }
                    s.push(pre);
                }
                s.push(tmp);
            }
            if(ch == ')')
            {
                tmp = s.pop();
                ++n;
                if(tmp->child == NULL)
                {
                    leaf c(tmp,tmp->weight);
                    q.enqueue(c);
                }
            }
        }
        leaf c,a;
        while(--n)
        {
            c = q.dequeue();
            if(c.cur->parent != NULL)
            {
                 printf("%d ",c.cur->parent->weight);
                 node *tmp = c.cur->parent->child;
                 if(tmp == c.cur)
                 {
                     if(tmp->brother == NULL)
                        {
                            a.cur = c.cur->parent;
                            a.weight = c.cur->weight;
                            q.enqueue(a);
                            continue;
                        }
                    else
                        c.cur->parent->child = tmp->brother;
                 }
                 else
                 {
                     while(tmp->brother!= c.cur)
                        tmp = tmp->brother;
                     tmp->brother = c.cur->brother;
                 }
                 if(tmp->parent->parent == NULL && tmp->parent->child->brother == NULL)
                    {
                        a.cur = c.cur->parent;
                        a.weight = c.cur->parent->weight;
                        q.enqueue(a);
                    }
            }
            else
            {
                 printf("%d ",c.cur->child->weight);
                 node *tmp = c.cur->child->child;
                 c.cur->child->parent = NULL;
                 if(tmp == NULL || tmp->brother == NULL)
                    {
                        a.cur = c.cur->child;
                        a.weight = c.cur->child->weight;
                        q.enqueue(a);
                    }
            }
        }
    }
};
int main()
{
    tree t;
    t.create();
    return 0;
}

