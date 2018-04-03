#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 200000+10;
int father[maxn];
bool alive[maxn];
int sons[maxn];
int main()
{
    int n,x,y;
    scanf("%d",&n);
    char ch;
    int cnt = 1;
    alive[1] = 1;
    while(n--)
    {
        ch = getchar();
        while(ch != 'B' && ch!='D') ch = getchar();
        switch(ch)
        {
        case 'B':
            scanf("%d %d",&x,&y);
            alive[y] = true;
            father[y] = x;
            ++sons[x];
            break;
        case 'D':
            scanf("%d",&x);
            alive[x] = false;
            if(!alive[father[x]])
                --cnt;
            else
                --sons[father[x]];
            cnt += sons[x];
            printf("%d\n",cnt);
            break;
        }
    }
    return 0;
}
