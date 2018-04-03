#include <iostream>
#include <cstdio>
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
const int maxn = 8000+5;
int total[maxn],second[maxn];
int main()
{
    int M,N,b[7],tmp = 0,total_num,last;
    SCInt(M);
    while(M--){
        SCInt(N);
        bool flag = false;
        FOR(i,0,8*N-1)
            total[i] = i+1;
        total_num = 8*N;
        FOR(i,0,6)
            SCAInt(b,i);
        FOR(i,0,6)
        {
            int k = b[i];
            tmp = 0;
            int num = (k<<1)-1;
            int remain = total_num % num,num2 = (total_num/num)*num;
            if(k==1)
            {
                PRInt(total[total_num-1]);
                ENTER;
                flag = true;
                break;
            }
            if(total_num == 1)
                break;
            if(total_num < k)
                continue;
            if(remain >= k)
            {
                FORStep(j,0,num2-1,2*k-1)
                {
                    FOR(t,j,j+k-2)
                        second[tmp++] = total[t];
                }
                FOR(j,num2,num2+k-2)
                    { second[tmp++] = total[j];}
                last = total[total_num-1];
            }
            if(remain < k)
            {
                FOR(j,num2,total_num-1)
                    second[tmp++] = total[j];
                FORStep(j,0,num2-1,2*k-1)
                {
                    FOR(t,j,j+k-2)
                        second[tmp++] = total[t];
                }
                last = total[num2-1];
            }
            FOR(t,0,tmp-1)
                total[t] = second[t];
            total_num = tmp;
        }
        if(!flag)
            { PRInt(last); ENTER;}
    }
    return 0;
}
