#include <iostream>
#include <cstdio>

using namespace std;
const int word_cnt = 26;
struct node
{
    int num;
    int pos;
    char ch;
    node *next[26];
    node(char c = ' '):ch(c) {for(int i=0;i<word_cnt;++i) next[i] = NULL;num = 0;pos = 0;}
};

bool dfs(node *tmp,int cnt,int &sum)
{
    int cur = -1;
    if(tmp->pos != 0)
        ++sum;
    if(sum == cnt)
    {
        printf("%d\n",tmp->pos);
        return true;
    }
    for(int i=0;i<word_cnt;++i)
    {
        if(tmp->next[i] != NULL)
            {
                sum += tmp->next[i]->num;
                if(sum >= cnt) {
                    cur = i;
                    sum -= tmp->next[i]->num;
                    return dfs(tmp->next[i],cnt,sum);
                }
            }
    }
}
int main()
{
    string s;
    node *root = new node(),*pre;
    int N,M,num;
    scanf("%d %d",&N,&M);
    for(int i=0;i<N;++i)
    {
        cin>>s;
        node *tmp = root;
        if(s.length() == 1)
        {
            if(tmp->next[s[0]-'a'] == NULL)
                tmp->next[s[0]-'a'] = new node();
            tmp->next[s[0]-'a']->pos= i+1;
            tmp->next[s[0]-'a']->ch = s[0];
            ++tmp->next[s[0]-'a']->num;
            continue;
        }
        int j;
        for(j=0;j<s.length()-1;++j)
        {
            if(tmp->next[s[j]-'a'] == NULL)
                tmp->next[s[j]-'a'] = new node(s[j]);
            ++tmp->next[s[j]-'a']->num;
            tmp = tmp->next[s[j]-'a'];
        }
        if(tmp->next[s[j]-'a'] == NULL)
            tmp->next[s[j]-'a'] = new node(s[j]);
        tmp->next[s[j]-'a']->pos= i+1;
        ++tmp->next[s[j]-'a']->num;
    }
    for(int i=0;i<M;++i)
    {
        scanf("%d",&num);
        cin>>s;
        node *tmp = root;
        for(int j=0;j<s.length() && tmp!=NULL;++j)
            tmp = tmp->next[s[j]-'a'];
        if(tmp == NULL) {printf("-1\n"); continue;}
        if(num > tmp->num) {printf("-1\n"); continue;}
        int n = 0;
        dfs(tmp,num,n);
    }
    return 0;
}
