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
enum symbol{BEGIN,END,IF,THEN,ELSE};

int main()
{
    bool flag = true;
    seqStack<symbol> begin_s,if_s;
    char ss[100];
    while(cin>>ss)
    {
        if(strcmp(ss,"begin")==0) begin_s.push(BEGIN);
        else if(strcmp(ss,"if")==0)
        {
            if(if_s.isEmpty())
            {
                if_s.push(IF);
                continue;
            }
            if(if_s.top()==IF){flag = false;break;}
            else if_s.push(IF);
        }
        else if(strcmp(ss,"end")==0)
        {
            if(!begin_s.isEmpty())
            {
                if(begin_s.top()==BEGIN)
                    begin_s.pop();
            }
            else {flag = false;break;}
        }
        else if(strcmp(ss,"then")==0)
        {
            if(!if_s.isEmpty())
            {
                if(if_s.top()==IF)
                {
                	if_s.push(THEN);
				}
                else {flag = false;break;}
            }
            else {flag = false;break;}
        }
        else if(strcmp(ss,"else")==0)
        {
            if(if_s.isEmpty()){flag = false;break;}
            if(if_s.top()==THEN)
            {
                if_s.pop();
                if(if_s.isEmpty()){flag = false;break;}
                if_s.pop();
            }
            else {flag = false;break;}
        }
    }
    while(!if_s.isEmpty())
    {
        if(if_s.top()!=THEN) {flag = false;break;}
        if_s.pop();
        if(if_s.top()!=IF) {flag=false;break;}
        if_s.pop();
    }
    if(!begin_s.isEmpty()) {flag=false;}
    if(flag) cout<<"Match!"<<endl;
    else cout<<"Error!"<<endl;
    return 0;
}
