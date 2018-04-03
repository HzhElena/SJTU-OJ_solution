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
struct node
{
    int x;
    int y;
    int num;
    node(int xx=-1,int yy=-1,int n=-1):x(xx),y(yy),num(n) {}
    bool operator > (const node &other)
    {
        return (x > other.x || (x == other.x && y > other.y));
    }
    bool operator == (const node &other)
    {
        return (x == other.x && y==other.y);
    }
};
template<class T>
int divide(T a[],int low,int high)
{
    T k = a[low];
    do{
        while(a[high] > k && high>low) --high;
        if(high>low) {a[low] = a[high]; ++low;}
        while(k > a[low] && high>low) ++low;
        if(low<high) {a[high] = a[low]; --high;}
    } while(low!=high);
    a[low] = k;
    return low;
}
template<class T>
void quickSort(T a[],int low,int high)
{
    if(high<=low) return;
    int mid = divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}
int binarySearch(node a[],int low,int high,node target)
{
    int mid;
    while(high >= low)
    {
        mid = (high+low)/2;
        if(a[mid] == target) return a[mid].num;
        if(a[mid] > target)
            high = mid-1;
        else
            low = mid+1;
    }
    return 0;
}
const int maxn = 100000+5;
node total[maxn];
int hashx[maxn],hashy[maxn];
int main()
{
    int n,x,y,z,m,tmp;
    SCInt(n);
    FOR(i,0,maxn-1) hashx[i] = hashy[i] = i;
    FOR(i,0,n-1)
    {
        SCInt(total[i].x);SCInt(total[i].y);SCInt(total[i].num);
    }
    quickSort(total,0,n-1);
    SCInt(m);
    while(m--)
    {
        SCInt(x);SCInt(y);SCInt(z);
        switch(x)
        {
        case 0:
            if(y==z) continue;
            SWAP(hashx[y],hashx[z]);
            break;
        case 1:
            if(y==z) continue;
            SWAP(hashy[y],hashy[z]);
            break;
        case 2:
            y = hashx[y];
            z = hashy[z];
            node target(y,z);
            PRInt(binarySearch(total,0,n-1,target));
            ENTER;
        }
    }
    return 0;
}
