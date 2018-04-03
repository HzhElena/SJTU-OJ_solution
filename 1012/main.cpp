#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int S,T;
    cin>>S>>T;
    int maxn = T+5;
    int d[maxn];
    long long cnt[maxn],number[maxn];
    int ans = 1;
    memset(cnt,0,sizeof(cnt));

    for(int i=S;i<=T;++i)
        d[i]=number[i] = 1;

    cnt[1] = T-S+1;
    for(int i=S;i<=T;++i)
        for(int j=1;j<=100;++j)
            if((i*j)%100 == 0)
            {
                int tmp = (i*j)/100 + i;
                if(tmp<=T)
                {
                    if(d[i]+1 > d[tmp])
                    {
                        d[tmp] = d[i] + 1;
                        number[tmp] = number[i];
                    }
                    else if(d[i]+1 == d[tmp])
                        number[tmp] += number[i];
                    ans = (ans >= d[tmp] ? ans:d[tmp]);
                    cnt[d[i]+1] += number[i];
                }
            }
    cout<<ans<<endl<<cnt[ans];
    return 0;
}
