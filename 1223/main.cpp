#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
template<class T>
int divide(T a[],int low,int high)
{
    T k = a[(low+high)/2];
    swap(a[low],a[(low+high)/2]);
    do{
        while(compare(k,a[high]) && high>low) --high;
        if(high>low) {a[low] = a[high]; ++low;}
        while(compare(a[low],k) && high>low) ++low;
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
struct node
{
    int score;
    int strength;
    int number;
};
bool compare(const node &a1,const node &a2)
{
    return (a1.score > a2.score || a1.score == a2.score && a1.number < a2.number);
}
int main()
{
    int N,R;
    scanf("%d %d",&N,&R);
    N *= 2;
    node total[N+5];
    for(int i=0;i<N;++i)
        {total[i].number = i+1; scanf("%d",&total[i].score);}
    for(int i=0;i<N;++i)
        scanf("%d",&total[i].strength);
    quickSort(total,0,N-1);
    while(R--)
    {
        int cur = N-1;
        for(int i=0;i<cur;i+=2)
        {
            if(total[i].strength > total[i+1].strength)
                ++total[i].score;
            else ++total[i+1].score;
        }
        quickSort(total,0,N-1);
    }
    for(int i=0;i<N;++i)
    {
        printf("%d ",total[i].number);
    }
    return 0;
}
