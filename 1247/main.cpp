#include <iostream>
#include <cstdio>
using namespace std;
struct period
{
    friend bool operator<=(period a,period b)
    {
        return (a.left<b.left || (a.left == b.left && a.right <= b.right));
    }
    int left;
    int right;
};
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
int main()
{
    int N,M,cur = -1,left_tree = 0;
    scanf("%d %d",&N,&M);
    period total[M];
    for(int i=0;i<M;++i)
        scanf("%d %d",&total[i].left,&total[i].right);
    quickSort(total,0,M-1);
    for(int i=0;i<M;++i)
    {
        if(total[i].left > N) break;
        if(cur > N) break;
        if(total[i].left > cur)
            left_tree += (total[i].left - cur - 1);
        if(total[i].right > cur)
            cur = total[i].right;
    }
    if(cur < N)
        left_tree += (N-cur);
    cout<<left_tree;
    return 0;
}
