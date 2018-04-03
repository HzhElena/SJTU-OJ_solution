#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    const int maxn = 100+5;
    int total = 0;
    int visit[maxn];
    memset(visit,0,sizeof(visit));
    int n;
    int a[1000];
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
        visit[a[i]] = 1;
    }
    int tmp = 1,len = n,t;
    while(tmp < len){
        if(a[tmp] == 0) {++tmp; continue;}
        for(int i=0;i<tmp;++i)
        {
            if(a[i]==1 || a[i]==0) continue;
            else if(a[tmp] > a[i]) {
                t = a[tmp]/a[i];
                if(visit[t] > 0)
                    continue;
                else
                  {
                    a[len++] = t;
                    visit[t] = 1;
                  }
            }
            else if(a[tmp] < a[i])
            {
                t = a[i]/a[tmp];
                if(visit[t] > 0)
                    continue;
                else
                    {
                      a[len++] = t;
                      visit[t] = 1;
                    }
            }
        }
        ++tmp;
    }
    cout<<len;
    return 0;
}
