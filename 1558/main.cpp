#include <iostream>
#include <map>
#include <cstdio>
using namespace std;
const int maxn = 100000;
struct cows
{
    int tag;
    int num;
    cows(int t = -1,int n = 0):tag(t),num(n) {}
};
int main()
{
    int N,K,b;
    scanf("%d %d",&N,&K);
    map<int,int> m;
    map<int,int>::iterator it;
    int tmp = 0;
    cows team[N];
    for(int i=0;i<N;++i)
    {
        scanf("%d",&b);
        if(team[tmp].tag == -1)
            { team[tmp].tag = b; ++team[tmp].num;}
        else if(team[tmp].tag == b)
            ++team[tmp].num;
        else
        {
            ++tmp;
            team[tmp].tag = b;
            ++team[tmp].num;
        }
    }
    int t = 0,n,max = 0;
    for(int i=0;i<=tmp;++i)
    {
        n = m.count(team[i].tag);
        if(n == 0)
        {
            if(m.size() == K+1)
            {
                while(m.size() == K+1 && t<i)
                {
                    it = m.find(team[t].tag);
                    if(it->second > max)
                        max = it->second;
                    it->second -= team[t].num;
                    if(it->second == 0)
                        m.erase(it);
                    ++t;
                }
            }
            m[team[i].tag] = team[i].num;
        }
        else
        {
            m[team[i].tag] += team[i].num;
        }
    }
    for(it = m.begin();it!=m.end();++it)
    {
        if(it->second>max) max = it->second;
    }
    cout<<max<<endl;
    return 0;
}
