#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int a[n];
    int result[n];
    for(int i=0;i<n;++i)
        cin>>a[i];
    for(int i=n-1;i>=0;--i)
    {
        result[i] = 0;
        int j = i+1;
        while(j<n && a[j] > a[i])  ++j;
        if(j == n) continue;
        else
        {
            result[i] += result[j];
            if(a[i]==a[j]) continue;
            else ++result[i];
        }
    }
    for(int i=0;i<n;++i)
        cout<<result[i]<<" ";
    return 0;
}
