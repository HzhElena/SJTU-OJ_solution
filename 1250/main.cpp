#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int n,f,tmp,j;
    scanf("%d %d",&n,&f);
    int preSum[n+1],weight,ans = -1;
    preSum[0] = 0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&weight);
        preSum[i] = preSum[i-1] + weight;
    }
    for(int i=0,j=0;i<=n-f;++i)
    {
        if(i > j && (i+f-j)*(preSum[i] - preSum[j]) < (i-j)*(preSum[i+f] - preSum[j]))
            j = i;
        tmp = (1000 * (preSum[i+f] - preSum[j])/(i+f-j));
        if(ans < tmp)
            ans = tmp;
    }
    printf("%d",ans);
    return 0;
}

