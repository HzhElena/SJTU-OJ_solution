#include <iostream>

using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    if(n==0 ||  m==0) {cout<<0; return 0;}
    int maze[n][m];
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
           cin>>maze[i][j];
    int maxn = 0;
    for(int i=0;i<n-1;++i)
        for(int j=0;j<m-1;++j)
    {
        int minn_len = (n-i-1) < (m-1-j) ? (n-1-i) : (m-1-j);
        for(int k = minn_len + i;k > i + maxn;--k)
        {
            int t = k - i + j;
            if(maze[k][j] == maze[i][j] && maze[i][j] == maze[i][t] && maze[i][j] == maze[k][t])
                if((k-i) > maxn) maxn = k-i;
        }
    }
    cout<<(maxn+1)*(maxn+1);
    return 0;
}
