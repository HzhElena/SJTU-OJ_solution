#include<iostream>
#include<cstdio>
using namespace std;
const int V = 100010;
const int E = 200010;
const int Q = 400010;
const int X = 99999999;
int v[V],a[E],b[E],w[E];
int cnt=0,dis[V],pre[V],num[V],parent;
bool k[V];
void print_ans(int x)
{
	if (pre[x]!=-1) print_ans(pre[x]);
	if (x==parent)
	{
		printf("%d",x);return;
	}
	else
	{
		printf("%d ",x);return;
	}
}
void add_edge(int x , int y, int c)
{
	a[++cnt]=v[x];
	v[x]=cnt;
	b[cnt]=y;
	w[cnt]=c;
}
int main()
{
	int N,M,s,e;
	int t1,t2,t3;
	scanf("%d %d %d %d",&N,&M,&s,&e);
	for (int i=1;i<=M;i++){
		scanf("%d %d %d",&t1,&t2,&t3);
		add_edge(t1,t2,t3);
	}
	for (int i=1;i<=N;i++)
        dis[i]=X;
	t1=X;
	t2=0;
	dis[s]=0;
	pre[s]=-1;
	num[s]=1;
	for (int i=1;i<=N;i++)
	{
		t1=X;
		for (int j=1;j<=N;j++)
		{
			if (!k[j] && t1>dis[j])
			{
				t1=dis[j];
				t2=j;
			}
		}
		k[t2]=true;
		for (int j=v[t2];j!=0;j=a[j])
		{
			if (!k[b[j]] && t1+w[j]<dis[b[j]])
			{
				dis[b[j]] = t1+w[j];
                pre[b[j]] = t2;
                num[b[j]] = num[t2]+1;
			}
			else if (!k[b[j]] && t1+w[j]==dis[b[j]])
			{
				if (num[b[j]] > num[t2]+1)
				{
					num[b[j]] = num[t2]+1;
					pre[b[j]] = t2;
				}
			}
		}

	}
	parent = e;
	printf("%d\n",dis[e]);
	print_ans(e);
	return 0;
}
