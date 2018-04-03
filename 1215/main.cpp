#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
template<class T>
class Binomial
{
    struct node
    {
        T data;
        node *son;
        node *brother;
        node(const T &x,node *s = NULL,node *b = NULL):data(x),son(s),brother(b) {}
        node() {son = NULL;brother = NULL;}
    };
    node **forest;
    int number;
    node * merge(node *t1,node *t2)
    {
        node *minn,*maxn;
        if(t1->data > t2->data) {maxn = t1; minn = t2;}
        else {maxn = t2; minn = t1;}
        if(minn->son == NULL)
            minn->son = maxn;
        else
        {
            node *p = minn->son;
            while(p->brother != NULL) p = p->brother;
            p->brother = maxn;
        }
        return minn;
    }
    int findMin()
    {
        int minn,i;
        for(i=0;i<number && forest[i] == NULL;++i) ;
        minn = i;
        for(;i<number;++i)
            if(forest[i]!=NULL && forest[i]->data < forest[minn]->data)
                minn = i;
        return minn;
    }
    void deleteTree(node *rt)
    {
        node *son = rt->son,*t;
        while(son!=NULL)
        {
            t = son;
            son = son->brother;
            deleteTree(t);
        }
        delete rt;
    }
public:
    Binomial(int n=100)
    {
        number = int(log(n)/log(2)) + 1;
        forest = new node*[number];
        for(int i=0;i<number;++i)
            forest[i] = NULL;
    }
    ~Binomial()
    {
        for(int i=0;i<number;++i)
            if(forest[i] != NULL) deleteTree(forest[i]);
        delete [] forest;
    }
    void enqueue(const T &x)
    {
        Binomial tmp(1);
        tmp.forest[0] = new node(x);
        merge(tmp);
    }
    T dequeue()
    {
        T value;
        int minn = findMin();
        if(minn == 0)
        {
            value = forest[0]->data;
            delete forest[0];
            forest[0] = NULL;
            return value;
        }
        node *t = forest[minn],*son,*brother;
        int sizeofQ = int(pow(2,minn)-1);
        Binomial tmp(sizeofQ);
        value = t->data;
        son = t->son;
        delete t;
        forest[minn] = NULL;
        int i=0;
        while(son!=NULL)
        {
            tmp.forest[i++] = son;
            brother = son->brother;
            son->brother = NULL;
            son = brother;
        }
        merge(tmp);
        return value;
    }
        bool isEmpty() const
    {
        for(int i=0;i<number;++i)
            if(forest[i] != NULL) {return false;}
        {
        return true;
        }
    }
    void merge(Binomial &other);
    T getMin()
    {
        int minn = findMin();
        return forest[minn]->data;
    }
};
template<class T>
void Binomial<T>::merge(Binomial<T> &other)
{
    node **tmp = forest;
    node *carry;
    int tmpSize = number;
    int minn = min(number,other.number);
    if(number<other.number)
    {
        number = other.number;
        if(other.forest[number] != NULL) ++number;
    }
    else if(tmp[number] != NULL) ++number;
    forest = new node*[number];
    for(int i=0;i<number;++i)
        forest[i] = NULL;
    carry = NULL;
    for(int i=0;i<minn;++i)
    {
        if(carry == NULL){
            if(tmp[i]!=NULL && other.forest[i]!= NULL)
                carry = merge(tmp[i],other.forest[i]);
            else if(tmp[i] == NULL)
                forest[i] = other.forest[i];
            else if(forest[i] == NULL)
                forest[i] = tmp[i];
        }
        else
        {
            if(tmp[i]!=NULL && other.forest[i]!= NULL)
            {
                forest[i] = carry;
                carry = merge(tmp[i],other.forest[i]);
            }
            else if(tmp[i] == NULL && other.forest[i] == NULL)
                {forest[i] = carry; carry = NULL;}
            else if(tmp[i] == NULL)
                carry = merge(other.forest[i],carry);
            else
                carry = merge(tmp[i],carry);
        }
    }
    int i;
    if(other.number == minn)
    {
        for(i=minn;i<tmpSize;++i)
        {
            if(carry == NULL)
                forest[i] = tmp[i];
            else if(tmp[i] == NULL)
                {forest[i] = carry; carry = NULL;}
            else
                carry = merge(tmp[i],carry);
        }
    }
    else
    {
        for(i=minn;i<other.number;++i)
        {
            if(carry == NULL)
                forest[i] = other.forest[i];
            else if(other.forest[i] == NULL)
                { forest[i] = carry; carry =NULL;}
            else
                carry = merge(other.forest[i],carry);
        }
    }
    if(carry != NULL)
        {
            forest[i] = carry;
        }
    for(int i=0;i<other.number;++i)
        other.forest[i] = NULL;
    delete[]tmp;
}
int main()
{
    int m,x;
    scanf("%d",&m);
    Binomial<int> tree(20000);
    char ex[10];
    while(m--)
    {
        scanf("%s",&ex);
        if(ex[0] == 'i')
        {
            scanf("%d", &x);
            tree.enqueue(x);
        }
        else if(ex[0]=='m')
        {
            printf("%d\n",tree.getMin());
        }
        else
        {
            tree.dequeue();
        }
    }
}
