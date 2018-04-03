#include <iostream>
#include <cstdio>
using namespace std;
struct point
{
    int x;
    int y;
    int type;
};
const int maxn = 500+5;
int N,max_num,G_num,area;
point space[maxn];
void init()
{
    scanf("%d",&N);
    char ch;
    for(int i=0;i<N;++i)
    {
        scanf("%d %d",&space[i].x,&space[i].y);
        cin>>ch;
        space[i].type = (ch == 'H') ? 1:2;
        if(ch == 'G') ++G_num;
    }
}
int calculate_area(point *s,int num)
{
    int leftx = s[0].x,rightx = s[0].x,highy = s[0].y,lowy = s[0].y;
    for(int i=1;i<num;++i)
    {
        if(s[i].x < leftx) leftx = s[i].x;
        if(s[i].x > rightx) rightx = s[i].x;
        if(s[i].y < lowy) lowy = s[i].y;
        if(s[i].y > highy) highy = s[i].y;
    }
    return (rightx - leftx) * (highy - lowy);
}
void divide_area(point *s,int num,int cur,point *divide[4],int len[4],int numOfG[4])
{
    for(int i=0;i<num;++i)
    {
        if(s[i].x > s[cur].x)
        {
            divide[0][len[0]++] = s[i];
            if(s[i].type == 2)
                ++numOfG[0];
        }
        else if(s[i].x < s[cur].x)
        {
            divide[1][len[1]++] = s[i];
            if(s[i].type == 2)
                ++numOfG[1];
        }
        if(s[i].y > s[cur].y)
        {
            divide[2][len[2]++] = s[i];
            if(s[i].type == 2)
                ++numOfG[2];
        }
        else if(s[i].y < s[cur].y)
        {
            divide[3][len[3]++] = s[i];
            if(s[i].type == 2)
                ++numOfG[3];
        }
    }
}
void find(point *s,int num,int g_num)
{
    if((num - g_num) < max_num) return;
    if(g_num == 0)
    {
        int a = calculate_area(s,num);
        if(num > max_num) {area = a; max_num = num;}
        else
           {
               if(area > a) area = a;
           }
        return;
    }
    else
    {
        int cur = 0;
        for(int i=0;i<num;++i)
        {
            if(s[i].type == 2) {cur = i; break;}
        }
        point *divide[4];
        int len[4];
        int numOfG[4];
        for(int i=0;i<4;++i)
            {divide[i] = new point[num+1];len[i] = 0;numOfG[i] = 0;}
        divide_area(s,num,cur,divide,len,numOfG);
        for(int i=0;i<4;++i)
            find(divide[i],len[i],numOfG[i]);
        for(int i=0;i<4;++i)
            delete[]divide[i];
    }
}
int main()
{
    init();
    find(space,N,G_num);
    cout<<max_num<<" "<<area;
    return 0;
}
