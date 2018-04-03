
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
    delete [] tmp;
}
enum color{RED,YELLOW,BLUE};
int main()
{
    seqStack<color> s;
    int num[3] = {0,0,0};
    char ex[1000+5];
    cin.getline(ex,1000+5);
    int len = strlen(ex);
    for(int i=0;i<len;++i)
    {
        if(ex[i] ==' ') continue;
        else if(ex[i]=='<'){
            int j = i + 1;
            for(;j<len;++j)
            {
                if(ex[j] == '>') break;
                else if(ex[j] == '/') break;
                else if(ex[j] == ' ') j = len;
                else if(ex[j] == '<') j = len;
                else if(!(ex[j]<='z' && ex[j]>='a' || ex[j]<='Z' && ex[j]>='A'))
                    j = len;

            }
            if(j >= len-1) continue;
            else if(ex[i+1] == '/')
            {
                char col[10];
                j = i;
                while(ex[j] != '>' && j < len) ++j;
                if(j==len) continue;
                for(int k=i+2;k<j;++k)
                {
                     col[k-i-2] = ex[k];
                }
                col[j-i-2] = '\0';
                if(strcmp(col,"blue")==0 && !s.isEmpty())
                    s.pop();
                else if(strcmp(col,"yellow")==0 && !s.isEmpty())
                    s.pop();
                else if(strcmp(col,"red")==0 && !s.isEmpty())
                    s.pop();
                else continue;
                i = j;
                continue;
            }
            else
            {
                char col[10];
                for(int k=0;k<j-i-1;++k)
                    col[k] = ex[i+k+1];
                col[j-i-1] = '\0';
               // cout<<"col: "<<col<<endl;
                if(strcmp(col,"blue")==0)
                    s.push(BLUE);
                else if(strcmp(col,"yellow")==0)
                    s.push(YELLOW);
                else if(strcmp(col,"red")==0)
                    s.push(RED);
                else continue;
                i = j;
                continue;
            }
        }
        else if((ex[i]<='z' && ex[i]>='a') || (ex[i]<='Z' && ex[i]>='A'))
            {
                if(!s.isEmpty())
                   {
                        ++num[s.top()];
                   }
            }
        else continue;
    }
    cout<<num[0]<<" "<<num[1]<<" "<<num[2];
    return 0;
}
