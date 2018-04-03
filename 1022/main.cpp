#include <iostream>

using namespace std;

int main()
{
    long long n;
    cin>>n;
    int last = 0;
    int cur = 1;
    if(n % 2040 == 0) {cout<<0; return 1;}
    else
    {
        n = n % 2040;
        for(int i=1;i<n;++i)
        {
            int tmp = last+cur;
            if(tmp > 2010) tmp %= 2010;
            last = cur;
            cur = tmp;
        }
    }
    cout<<cur;
}
