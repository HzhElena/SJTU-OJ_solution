#include <iostream>

using namespace std;
class seqStack
{
private:
    int *data;
    int maxSize;
    int top_p;
public:
    seqStack(int init = 1000)
    {
        data = new int [init];
        maxSize = init;
        top_p = -1;
    }
    ~seqStack() {delete [] data;}
    bool push(const int &x)
    {
        if(top_p == maxSize-1) return false;
        else
            data[++top_p] = x;
        return true;
    }
    bool isFull() {return top_p == maxSize-1;}
    bool isEmpty() {return top_p==-1;}
    int pop() {return data[top_p--];}
    int top() const {return data[top_p];}
};
int main()
{
    int time;
    cin>>time;
    while(time--)
    {
        int N,M;
        cin>>N>>M;
        seqStack s(M);
        int target[N];
        for(int i=0;i<N;++i)
            cin>>target[i];
        int cur = 0;
        bool flag = true;
        for(int i=0;i<N;++i)
        {
            if(!flag) break;
            if(i==target[cur])
            {
                ++cur;
            }
            else if(!s.isEmpty() && s.top()==target[cur])
            {
                s.pop();
                --i;
                ++cur;
            }
            else
            {
                if(s.isFull()) flag = false;
                else
                    s.push(i);
            }
        }
        if(!flag) {cout<<"NO"<<endl; continue;}
        if(s.isEmpty()) {cout<<"YES"<<endl;continue;}
        else
        {
            while(!s.isEmpty() && s.top()==target[cur]) {++cur;s.pop();}
            if(!s.isEmpty()) {cout<<"NO"<<endl; continue;}
            else {cout<<"YES"<<endl;continue;}
        }
    }
    return 0;
}
