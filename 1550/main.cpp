#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int n,t,water = 0;
    cin>>n;
    int* w = new int[10000];
    memset(w,0,10000);
    char dup;
    for(int i = 1;i<=n;i++)
    {
        cin>>dup;
        cin>>t;
        for(int j = 0;j<t;j++)
        {
            if(w[j] != 0) water += i- w[j] -1;
            w[j] = i;
        }
    }
    cin>>dup;
    cout<<water;
    return 0;
}
