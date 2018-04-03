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
    int length() const {return top_p+1;}
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

int main()
{
    int n,total = 0;
    seqStack<int> s;
    seqStack<int> wait;
    cin>>n;
    char ch;
    int cur;
    for(int i=0;i<n;++i)
    {
        cin>>ch;
        cin>>cur;
        if(s.isEmpty())
            s.push(cur);
        else
        {
            while(!s.isEmpty() && s.top()<cur)
                wait.push(s.pop());
            if(s.isEmpty())
            {
                int t = wait.pop();
                while(!wait.isEmpty())
                {
                    total += t - wait.pop();
                }
                s.push(cur);
            }
            else if(s.top() >= cur)
            {
                while(!wait.isEmpty())
                 {
                     total += cur-wait.pop();
                     s.push(cur);
                 }
                 s.push(cur);
            }
        }
    }
    cout<<total;
    return 0;
}
