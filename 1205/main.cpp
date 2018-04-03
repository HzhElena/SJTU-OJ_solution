#include <iostream>
#include <cstring>
using namespace std;
const int maxn1 = 10+5;
const int maxn = 800;
int value[maxn1][maxn];
int A(int m,int n)
{
    if(n<maxn)
    {
        if(value[m][n]>0) return value[m][n];
        if(m != 0 && n != 0) {
            value[m][n] =  A(m-1,A(m,n-1));
        }
        else if(m!=0 && n==0) {value[m][n] = A(m-1,1);}
        else {value[m][n] = n+1;}
        return value[m][n];
    }
    else
    {
        if(m != 0 && n!=0) return A(m-1,A(m,n-1));
        else if(m!=0 && n==0) return A(m-1,1);
        else return n+1;
    }
}

int main()
{
    int m,n;
    cin>>m>>n;
    cout<<A(m,n);
    return 0;
}
