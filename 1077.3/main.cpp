#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 30+5;
int sum[maxn][maxn];
int root[maxn][maxn];
int value[maxn];
void preOrder(int l,int r)
{
    if(l>r) return;
    printf("%d ",root[l][r]);
    preOrder(l,root[l][r]-1);
    preOrder(root[l][r]+1,r);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&value[i]);
        for(int j=0;j<i;++j)
            sum[i][j] = 1;
        sum[i][i] = value[i];
        root[i][i] = i;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n-i;++j)
            for(int k=j;k<=j+i;++k)
        {
            if(sum[j][k-1]*sum[k+1][i+j] + value[k] > sum[j][i+j])
            {
                sum[j][i+j] = sum[j][k-1]*sum[k+1][i+j] + value[k];
                root[j][i+j] = k;
            }
        }
    printf("%d\n",sum[1][n]);
    preOrder(1,n);
    return 0;
}
