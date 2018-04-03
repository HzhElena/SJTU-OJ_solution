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

const int maxn = 100000+5;
int father[maxn],lchild[maxn],rchild[maxn],red[maxn],children[maxn],red_num[maxn];

int total_child(int root)
{
    int num = 0;
    if(lchild[root])
        {
            children[lchild[root]] = total_child(lchild[root]);
            num = num + children[lchild[root]] + 1;
        }
    if(rchild[root])
        {
            children[rchild[root]] = total_child(rchild[root]);
            num = num + children[rchild[root]] + 1;
        }
    return num;
}
int total_red(int root)
{
    int num = 0;
    if(red[root]) ++num;
    if(lchild[root]) {red_num[lchild[root]] = total_red(lchild[root]); num += red_num[lchild[root]];}
    if(rchild[root]) {red_num[rchild[root]] = total_red(rchild[root]); num += red_num[rchild[root]];}
    return num;
}
void color_on(int t,int x)
{
    x = x % (children[t] + 1);
    int n = 0,tmp,cur;
    seqStack<int> s;
    seqStack<int> s_num;
    s.push(t);
    s_num.push(0);
    while(!s.isEmpty())
    {
        tmp = s.pop();
        cur = s_num.pop();
        if(cur == 0)
            {
                s.push(tmp);
                s_num.push(1);
                if(lchild[tmp]) {s.push(lchild[tmp]); s_num.push(0);}
            }
            else
            {
                if(n == x) {red[tmp] = 1;return;}
                else ++n;
                if(rchild[tmp]) {s.push(rchild[tmp]); s_num.push(0);}
            }
    }
}
int main()
{
    int N,P,Q,x,y,z,root,cnt = N;
    scanf("%d %d %d",&N,&P,&Q);
    while(N--)
    {
        scanf("%d %d %d",&x,&y,&z);
        father[y] = father[z] = x;
        lchild[x] = y;
        rchild[x] = z;
    }
    for(int i=1;i<=cnt;++i)
    {
        if(father[i] == 0)
            {root = i; break;}
    }
    children[root] = total_child(root);
    while(P--)
    {
        scanf("%d %d",&x,&y);
        color_on(x,y);
    }
    red_num[root] = total_red(root);
    while(Q--)
    {
        scanf("%d",&x);
        printf("%d\n",red_num[x]);
    }
    return 0;
}
