#include<iostream>
#include<cstring>

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
        data = new T [initSize];
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
}
struct token
{
    char data;
    int pos;
};
int main()
{
    const int maxn = 100+5;
    char expression[maxn];
    seqStack<token> seq;
    token t;
    cin.getline(expression,maxn);
    char *s;
    int len = strlen(expression);
    s = new char [len];
    s[len] = '\0';
    for(int i=0;i<len;++i)
    {
        if(expression[i] == '(')
            {
                t.data = '(';
                t.pos = i;
                seq.push(t);
            }
        else if(expression[i] == ')')
        {
            if(!seq.isEmpty() && seq.top().data=='(')
               {
                    s[seq.top().pos] =' ';
                    s[i] = ' ';
                    seq.pop();
               }
            else s[i] = '?';
        }
        else s[i] = ' ';
    }
    while(!seq.isEmpty())
    {
        t = seq.top();
        s[t.pos] = '$';
        seq.pop();
    }
    cout<<expression<<endl;
    cout<<s;
    return 0;
}
