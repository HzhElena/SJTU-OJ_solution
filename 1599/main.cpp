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
    seqStack(const seqStack &other)
    {
        maxSize = other.maxSize;
        top_p = other.top_p;
        data = new T[maxSize];
        for(int i=0;i<=top_p;++i)
            data[i] = other.data[i];
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
bool match(char a,char b)
{
    if(a==')' && b=='(') //sequence
        return true;
    if(a=='}' && b=='{')
        return true;
    if(a==']' && b=='[')
        return true;
    return false;
}
int main()
{
    seqStack<char> s;
    int n,ins;
    scanf("%d",&n);
    bool flag = true;
    for(int i=0;i<n;++i)
    {
        flag = true;
        scanf("%d",&ins);
        if(ins == 1)
        {
            char ch = ' ';
            while(ch==' ')
               ch = getchar();
            s.push(ch);
        }
        else if(ins == 2)
        {
            if(!s.isEmpty())
                s.pop();
        }
        else if(ins == 3)
        {
            if(!s.isEmpty())
                printf("%c\n",s.top());
             //   cout<<s.top()<<endl;
        }
        else
        {
            char ch;
            if(s.isEmpty()) printf("%s\n","YES");
                //cout<<"YES"<<endl;
            else
            {
                seqStack<char> tmp = s;
                seqStack<char> p;
                while(!tmp.isEmpty())
                {
                    ch = tmp.pop();
                    if(ch=='}' || ch==')' || ch==']')
                        p.push(ch);
                    else
                    {
                        if(p.isEmpty()) {//cout<<"NO"<<endl;
                                printf("%s\n","NO");
                                flag = false;break;}
                        if(!match(p.top(),ch))
                        {
                           // cout<<p.top()<<" "<<ch<<endl;
                           printf("%s\n","NO");
                          //  cout<<"NO"<<endl;
                            flag = false;
                            break;
                        }
                        else p.pop();
                    }
                }
                if(flag){
                if(p.isEmpty())
                    printf("%s\n","YES");
                   // cout<<"YES"<<endl;
                else
                    printf("%s\n","NO");
                    //cout<<"NO"<<endl;
                }
            }
        }
    }
    return 0;
}
