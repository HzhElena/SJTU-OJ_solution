#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class IllegalSize{};
class OutOfRange{};
template<class> class seqList;
template<class T>
class seqList
{
private:
    int currentLength;
    int maxSize;
    T *data;
    void doubleSpace();
public:
    seqList(int initSize = 100);
    ~seqList() {delete[]data;}
    void clear() {currentLength = 0;}
    int length() const {return currentLength;}
    T visit(int i) const;
    int search(const T &) const;
    void insert(int i,const T &);
    void remove(int i);
    void traverse() const;
    void insertEnd(const T &d);
    void change(int i,const T &x)
    {
        data[i] = x;
    }
};
template<class T>
void seqList<T>::doubleSpace()
{
    T *tmp = data;
    maxSize *= 2;
    data = new T[maxSize];
    for(int i=0;i<currentLength;++i)
        data[i] = tmp[i];
    delete [] tmp;
}
template<class T>
seqList<T>::seqList(int initSize)
{
    if(initSize <=0 ) throw IllegalSize();
    maxSize = initSize;
    data = new T [maxSize];
    currentLength = 0;
}
template<class T>
T seqList<T>::visit(int i) const
{
    if(i<0 || i>=currentLength) throw OutOfRange();
    return data[i];
}
template<class T>
int seqList<T>::search(const T &target) const
{
    for(int i=0;i<currentLength;++i)
        if(data[i]==target) return i;
    return -1;
}
template<class T>
void seqList<T>::insert(int i,const T &d)
{
   if(i<0 || i>currentLength) throw OutOfRange();
   if(currentLength == maxSize)
        doubleSpace();
   for(int j=currentLength;j>i;--j)
        data[j] = data[j-1];
   data[i] = d;
   ++currentLength;
}
template<class T>
void seqList<T>::insertEnd(const T &d)
{
    insert(currentLength,d);
}
template<class T>
void seqList<T>::remove(int i)
{
    if(i<0 || i>=currentLength) throw OutOfRange();
    for(int j=i;j<currentLength-1;++j)
        data[j] = data[j+1];
    --currentLength;
}
template<class T>
void seqList<T>::traverse() const
{
    for(int i=0;i<currentLength;++i)
        cout<<data[i]<<'\t';
    cout<<endl;
}
template<class T>
class seqStack
{
private:
    T *data;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 50) {
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

enum token{LEFTOP,RIGHTOP,SUB,ADD,MULTI,DIV};
seqStack<token> s;
seqStack<int> value;
seqList<string> v;
seqList<int> v_num;
int mod;

int getNum(char *&s)
{
    int value = 0;
    while(*s<='9' && *s>='0')
     {
        value = value * 10 + *s - '0';
        ++s;
     }
     return value;
}
void calculate(token t)
{
    int num2 = value.pop();
    int num1 = value.pop();
    int tmp;
    switch(t)
    {
    case ADD:
        tmp = (num1+num2)%mod;
        if(tmp<0)
            tmp+=mod;
        value.push(tmp);
        break;
    case SUB:
        tmp = (num1 -num2)%mod;
        if(tmp<0)
            tmp+=mod;
        value.push(tmp);
        break;
    case MULTI:
        tmp =(num1 * num2)%mod;
        if(tmp<0)
            tmp+=mod;
        value.push(tmp);
        break;
    case DIV:
        tmp = (num1/num2)%mod;
        if(tmp<0)
            tmp+=mod;
        value.push(tmp);
        break;
    }
}
int getvariable(char *& s)
{
    string t;
    int pos;
    while(*s !='(' && *s!=')' && *s!='+' && *s!='-' && *s!='*' && *s!='/' && !(*s<='9' && *s>='0'))
    {
        if(*s==';' || *s =='\0') break;
        t += *s;
        ++s;
    }
    pos = v.search(t);
   // cout<<"variable: "<<t<<endl;
   // cout<<"pos: "<<pos<<endl;
    if(pos == -1)
    {
        v.insertEnd(t);
        v_num.insertEnd(0);
        return 0;
    }
    else
        return v_num.visit(pos);
}

int main()
{
    string st,tmp;
    getline(cin,st);
    int i;
    for(i=0;i<st.length();++i)
    {
        if(st[i] == '=') break;
        else tmp+=st[i];
    }
    ++i;
    char *ch = &st[i];
    mod = getNum(ch);
    v.insertEnd(tmp);
    v_num.insertEnd(mod);
      //  cout<<"mod: "<<mod<<endl;
    while(getline(cin,st))
    {
        string tmp;
        int i;
        for(i=0;i<st.length();++i)
        {
            if(st[i] == '=') break;
            else tmp+=st[i];
        }
        ++i;
        char *ch = &st[i];
        while(*ch!=';')
        {
            if(*ch == '(')
               {
                   s.push(LEFTOP);
                   ++ch;
               }
            else if(*ch == ')')
            {
                token tmp;
                while(!s.isEmpty() && s.top()!=LEFTOP)
                {
                    tmp = s.pop();
                    calculate(tmp);
                }
                if(!s.isEmpty() && s.top() == LEFTOP)
                    s.pop();
                ++ch;
            }
            else if(*ch<='9' && *ch>='0')
            {
                int num = getNum(ch);
                value.push(num);
            }
            else if(*ch=='+' || *ch=='-')
            {
                while(!s.isEmpty() && s.top()>=SUB)
                    {
                        calculate(s.pop());
                    }
                    if(*ch == '+')
                        s.push(ADD);
                    else
                        s.push(SUB);
                    ++ch;
            }
            else if(*ch=='*' || *ch=='/')
            {
            while(!s.isEmpty() && s.top()>=MULTI)
                    {
                        calculate(s.pop());
                    }
                    if(*ch == '*')
                        s.push(MULTI);
                    else
                        s.push(DIV);
                    ++ch;
            }
            else
            {
                int t = getvariable(ch);
                value.push(t);
            }
        }
        int val;
        while(!s.isEmpty())
            calculate(s.pop());
        if(!value.isEmpty())
        {
            val = value.top();
            cout<<val<<endl;
        }
      //  cout<<"tmp: "<<tmp<<endl;
        int pos = v.search(tmp);
        if(pos==-1)
           {
             //   cout<<"insert: "<<val<<endl;
                v.insertEnd(tmp);
                v_num.insertEnd(val);
           }
        else
            v_num.change(pos,val);
    }
    return 0;
}
