#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define LL long long
#define FOR(i,low,high) for(int i=low;i<=high;++i)
#define RFOR(i,low,high) for(int i=high;i>=low;--i)
#define FORStep(i,low,high,step) for(int i=low;i<=high;i+=step)
#define RFORStep(i,low,high,step) for(int i=high;i>=low;i-=step)
#define SCInt(x) scanf("%d",&x)
#define SCAInt(a,i) scanf("%d",&a[i])
#define SCAAInt(a,i,j) scanf("%d",&a[i][j])
#define ENTER printf("\n")
#define SPACE printf(" ")
#define PRInt(x) printf("%d",x)
#define PRIntS(x) printf("%d ",x)
#define PRAInt(a,i) printf("%d",a[i])
#define PRAIntS(a,i) printf("%d ",a[i])
#define PRAAInt(a,i,j) printf("%d",a[i][j])
#define PRfloat(x) printf("%f",x)
#define MSET(a,i) memset(a,i,sizeof(a))
#define SWAP(a,b) {a=a^b;b=a^b;a=a^b;}
using namespace std;
const int maxn = 1000+5;
int n,pre[maxn],num[350];
int len = 1;
void mul2(int power){
    num[0]=1;
    for (int i = 0; i < power; ++i)
    {
        int r = 0;
        int ori_len = len;
        for (int j = 0; j < ori_len ; ++j)
        {
            int tmp = num[j]*2 + r;
            r = 0;
            num[j] = ( tmp ) % 10;
            if(tmp >= 10){
                r = (tmp)/10 ;
            }
        }
        if(r!=0)
            num[len++] = r;
    }
}
int find_root(int x)
{
    int root = pre[x],tmp,tmp2;
    while(root != pre[root])
        root = pre[root];
    tmp = x;
    while(tmp!=root)
    {
        tmp2 = pre[tmp];
        pre[tmp] = root;
        tmp = tmp2;
    }
    return root;
}
void join(int x,int y)
{
    int prex = find_root(x),prey = find_root(y);
    if(prex == prey) return;
    pre[prex] = prey;
}
int main()
{
    int m,a,b,res=0;
    SCInt(n);
    FOR(i,1,n)
        pre[i] = i;
    SCInt(m);
    FOR(i,0,m-1)
    {
        SCInt(a); SCInt(b);
        join(a,b);
    }
    FOR(i,1,n)
        if(pre[i] == i) ++res;
    mul2(n-res);
    for (int i = len-1; i >=0; --i)
    {
        cout<<num[i];
    }
    return 0;
}
