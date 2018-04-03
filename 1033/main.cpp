#include <iostream>
#include <cmath>
using namespace std;
//注意减号和负号的区别
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
   //     cout<<"top_p: "<<top_p<<endl;
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

const int maxn = 100+5;
char expression[maxn];
enum token{VALUE,LEFTOP,ADD,SUB,MULTI,DIV,EXP,NEG,RIGHTOP};
seqStack<token> token_s;
seqStack<long long> value_s;

void getNum(char *&s,long long & value)
{
    value = 0;
    while(*s<='9' && *s>='0')
    {
       value = value*10 + *s-'0';
       ++s;
    }
}

bool calOp()
{
    token t = token_s.pop();
    long long num1,num2;
    if(t==NEG)
    {
        num1 = value_s.pop();
        num1 = 0-num1;
        value_s.push(num1);
        return true;
    }
    num2 = value_s.pop();
    num1 = value_s.pop();
    switch(t)
    {
    case ADD:
        value_s.push(num1+num2);
        break;
    case SUB:
        value_s.push(num1-num2);
        break;
    case MULTI:
        value_s.push(num1*num2);
        break;
    case DIV:
        if(num2 == 0) return false;
        value_s.push(num1/num2);
        break;
    case EXP:
        double re = pow(num1,num2);
        value_s.push(re);
        break;
    }
    return true;
}
int main()
{
    cin.getline(expression,maxn);
    char *s = expression;
    long long value;
    token last = LEFTOP;
    while(*s!='\0')
    {
        while(*s==' ') {++s; continue;}
        if(*s<='9' && *s>='0') {
            getNum(s,value);
            value_s.push(value);
            last = VALUE;
            continue;
        }
        if((last==RIGHTOP || last == VALUE) && *s=='-')
        {
            while(!token_s.isEmpty() && token_s.top()>=ADD)
            {
                if(!calOp()) {cout<<"Error";return 0;}
            }
            token_s.push(SUB);
            ++s;
            last = SUB;
            continue;
        }
        else if(*s=='-')
        {
            token_s.push(NEG);
            ++s;
            last = NEG;
            continue;
        }
        switch(*s)
        {
        case '(':
            token_s.push(LEFTOP);
            last = LEFTOP;
            ++s;
            break;
        case ')':
            while(!token_s.isEmpty() && token_s.top()!=LEFTOP)
                {
                    if(!calOp()) {cout<<"Error";return 0;}
                }
            if(token_s.isEmpty())
            {
                cout<<"Error";
                return 0;
            }
            else if(token_s.top() == LEFTOP) token_s.pop();
            last = RIGHTOP;
            ++s;
            break;
        case '+':case '-':
            while(!token_s.isEmpty() && token_s.top()>=ADD)
            {
                if(!calOp()) {cout<<"Error";return 0;}
            }
            if(*s == '+') token_s.push(ADD);
            else token_s.push(SUB);
            last = ADD;
            ++s;
            break;
        case '*':case '/':
            while(!token_s.isEmpty() && token_s.top()>=MULTI)
            {
                if(!calOp()) {cout<<"Error";return 0;}
            }
            if(*s=='*') token_s.push(MULTI);
            else token_s.push(DIV);
            last = MULTI;
            ++s;
            break;
        case '^':
            while(!token_s.isEmpty() && token_s.top()>EXP)
            {
                if(!calOp()) {cout<<"Error";return 0;}
            }
            token_s.push(EXP);
            last = EXP;
            ++s;
            break;
        }
    }
    while(!token_s.isEmpty())
    {
        if(token_s.top() == LEFTOP)
        {
            cout<<"Error";
            return 0;
        }
        else if(!calOp()) {cout<<"Error";return 0;}
    }
    if(!value_s.isEmpty())
        cout<<value_s.top();
    return 0;
}
