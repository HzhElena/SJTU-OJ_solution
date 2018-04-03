#include <iostream>
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
struct node
{
    int pos;
    int speed;
};
int main()
{
    int N,v,v2;
    int p,p2;
    node t,cur;
    cin>>N;
    seqStack<node> s(N);
    int cnt = 0;
    for(int i=0;i<N;++i)
    {
        cin>>p>>v;
        if(s.isEmpty())
        {
            cur.pos = p;
            cur.speed = v;
            s.push(cur);
            continue;
        }
        else
        {
            t = s.pop();
            if(p == t.pos)
            {
                cur.pos = p;
                cur.speed = cur.speed < v ? cur.speed:v;
                s.push(cur);
            }
            else if(v < t.speed)
            {
                while(!s.isEmpty() && v < t.speed)
                {
                    t = s.pop();
                }
                if(v >= t.speed)
                    s.push(t);
                cur.pos = p;
                cur.speed = v;
                s.push(cur);
            }
            else
            {
                s.push(t);
                cur.pos = p;
                cur.speed = v;
                s.push(cur);
            }
        }
    }
    while(!s.isEmpty())
    {
        ++cnt;
        s.pop();
    }
    cout<<cnt;
    return 0;
}
