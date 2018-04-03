#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 30;
struct node
{
    int data;
    node *left;
    node *right;
};
node *poss[maxn];
int t;
int score[maxn],lchild[maxn],rchild[maxn];
void build(int low,int high,int &root)
{
    int minn = score[low],root = low;
    if(low == high) return;
    for(int i=low+1;i<=high;++i)
        if(score[i] < minn) { minn = score[i]; root = i;}
    build(low,root-1,lchild[root]);
    build(root+1,high,child[root]);
}
void preOrder(int root)
{
    if(!root) return;
    printf()
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d",&score[i]);
    int root;
    build(0,n-1,root);
    return 0;
}
