#include <iostream>
#include <cstring>
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
}
const int maxn = 1000+5;
int num = 0;
char expression[maxn];
char convert[maxn];
enum token{LEFTOP,RIGHTOP,ADD,SUB,MULTI,DIV};
seqStack<int> value_s;

void getNum(char * &s,int &value)
{
    while(*s==' ') --s;
    value = 0;
    int i = 1;
    while(*s<='9' && *s>='0' && s>=expression)
    {
        convert[num++] = *s;
        value += (*s-'0')*i;
        i *= 10;
        --s;
    }
    convert[num++] = ' ';
}
void printOp(token t)
{
    switch(t)
    {
    case MULTI:
        convert[num++] = '*';
        convert[num++] = ' ';
        break;
    case DIV:
        convert[num++] = '/';
        convert[num++] = ' ';
        break;
    case ADD:
        convert[num++] = '+';
        convert[num++] = ' ';
        break;
    case SUB:
        convert[num++] = '-';
        convert[num++] = ' ';
        break;
    }
}
void cal(token t)
{
    int num1 = value_s.pop();
    int num2 = value_s.pop();
    switch(t)
    {
    case SUB:
        value_s.push(num1-num2);
        break;
    case ADD:
        value_s.push(num1+num2);
        break;
    case MULTI:
        value_s.push(num1*num2);
        break;
    case DIV:
        value_s.push(num1/num2);
        break;
    }
}
void convert_into_prefix()
{
    seqStack<token> s;
    token to;
    int value;
    char *ch = expression;
    for(int i=1;i<strlen(expression);++i) ++ch;
    while(ch >= expression)
    {
        while(*ch == ' ') --ch;
        if(*ch<='9' && *ch>='0') { getNum(ch,value); value_s.push(value); continue;}
        switch(*ch)
        {
        case ')':
            s.push(RIGHTOP);
            --ch;
            break;
        case '(':
            while(!s.isEmpty() && s.top()!=RIGHTOP) {
                    to = s.pop();
                    printOp(to);
                    cal(to);
            }
            if(s.top() == RIGHTOP) s.pop();
            --ch;
            break;
        case '+':case '-':
            if(!s.isEmpty() && s.top()>=MULTI)
            {
                while(!s.isEmpty() && s.top()>=MULTI)
                {
                    to = s.pop();
                    printOp(to);
                    cal(to);
                }
            }
            if(*ch=='+') s.push(ADD);
            else s.push(SUB);
            --ch;
            break;
        case '*':
            s.push(MULTI);
            --ch;
            break;
        case '/':
            s.push(DIV);
            --ch;
            break;
        }
    }
    while(!s.isEmpty())
    {
        to = s.pop();
        printOp(to);
        cal(to);
    }
}
int main()
{
    cin.getline(expression,maxn);
    convert_into_prefix();
    for(int i=num-2;i>=0;--i)
        cout<<convert[i];
    cout<<endl;
    cout<<value_s.top();
    return 0;
}

