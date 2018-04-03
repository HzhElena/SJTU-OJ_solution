#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
template<class T>
int divide(T a[],int low,int high)
{
    T k = a[low];
    do{
        while(k<=a[high] && high>low) --high;
        if(high>low) {a[low] = a[high]; ++low;}
        while(a[low]<=k && high>low) ++low;
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
struct cow
{
    friend bool operator<=(const cow &c1,const cow &c2)
    {
        return c1.pos <= c2.pos;
    }
    int pos;
    int height;
    cow(int p = 0,int h = 0):pos(p),height(h) {}
};
int main()
{
    int N,D,x,h,ans = 0;
    bool left = false,right = false;
    scanf("%d %d",&N,&D);
    cow total_cow[N];
    int maxn = 0;
    for(int i=0;i<N;++i)
    {
        scanf("%d %d",&x,&h);
        total_cow[i].height = h;
        total_cow[i].pos = x;
        if(h>maxn) maxn = h;
    }
    quickSort(total_cow,0,N-1);
    int j;
    for(int i=0;i<N;++i)
    {
        x = total_cow[i].pos;
        left = right = false;
        if(total_cow[i].height*2>maxn)
            continue;
        j = i-1;
        while(j>=0 && (x-total_cow[j].pos)<=D)
        {
            if(total_cow[i].height*2 <= total_cow[j].height)
                {left = true; break;}
            --j;
        }
        j = i+1;
        while(j<N && (total_cow[j].pos-x)<=D)
        {
            if(total_cow[i].height*2 <= total_cow[j].height)
                {right = true;break;}
            ++j;
        }
        if(left && right) ++ans;
    }
    cout<<ans<<endl;
    return 0;
}
