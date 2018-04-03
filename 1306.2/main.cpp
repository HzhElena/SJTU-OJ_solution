#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 500+5;
double height[maxn],alpha;
struct point
{
    int x;
    int y;
};
struct Circle
{
    int x;
    int r;
};
Circle circle[maxn];

int main()
{
    int n;
    scanf("%d %lf",&n,&alpha);
    for(int i=0;i<=n;++i)
        scanf("%lf",&height[i]);
    for(int i=0;i<n;++i)
        {
            height[i+1] += height[i];
            scanf("%lf",&circle[i].r);
        }
    double tan_value = tan(alpha);
    for(int i=0;i<n;++i)
        circle[i].x = height[i]/tan_value;

    return 0;
}
