#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int N,k;
    cin>>N>>k;
    int a[N];
    for(int i=0;i<N;++i)
        scanf("%d",&a[i]);
    int minmax_rp,maxn = a[0],max_num = 0,start = 0,tmp;
    for(int i=1;i<k;++i)
        if(a[i] >= maxn) {maxn = a[i]; max_num = i;}
    minmax_rp = maxn;
    start = max_num + 1;
    while(start < N)
    {
        maxn = a[start];
        max_num = start;
        for(int i=1;i<k;++i)
        {
            if(maxn > minmax_rp)  break;
            tmp = (start + i) % N;
            if(a[tmp] > maxn)
            {
                maxn = a[tmp];
                max_num = tmp;
            }
        }
        if(maxn < minmax_rp)
            minmax_rp = maxn;
        if(max_num >= start)
            start = max_num + 1;
        else
            break;
    }
    cout<<minmax_rp;
    return 0;
}
