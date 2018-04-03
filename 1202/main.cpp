#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class bigInteger
{
    friend istream & operator>>(istream &in,bigInteger &a);
    friend void operator+(const bigInteger &a,const bigInteger &b);
private:
    struct node
    {
        int data;
        node *next;
        node():next(NULL) {}
        node(const int &d,node *n=NULL):data(d),next(n) {}
    };
    node *head;
    int currentLength;
public:
    bigInteger() {head = new node;currentLength = 0;}
    bigInteger(const bigInteger &other);
    bigInteger & operator = (const bigInteger &other);
    ~bigInteger() {clear();delete head;}
    void clear();
};
bigInteger::bigInteger(const bigInteger &other)
{
    head = new node;
    node *p = other.head->next,*q = head;
    while(p!=NULL)
    {
        q->next = new node (p->data);
        p = p->next;
        q = q->next;
    }
}
bigInteger & bigInteger::operator = (const bigInteger &other)
{
    if(this == &other) return *this;
    clear();
    node *p = other.head->next,*q = head;
    while(p!=NULL)
    {
        q->next = new node (p->data);
        p = p->next;
        q = q->next;
    }
    return *this;
}
void bigInteger::clear()
{
    node *p = head->next,*q;
    head->next = NULL;
    while(p!=NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
}
istream & operator>>(istream &in,bigInteger &a)
{
    string s;
    typedef bigInteger::node node;
    bigInteger::node *p = a.head;
    char ch;
    int t = 0;
    int num = 0;
    bool flag = true;
    in>>s;
    int i=s.size()-1,j=1;
    while(i>=0)
    {
        ch = s[i];
        --i;
        if(t%8 || flag) {
         num = num + (int(ch-'0'))*j; j*=10; ++t;
         flag = false;
         }
        else
          {
              p->next = new node(num);
              p = p->next;
              ++a.currentLength;
              t = 1;
              j = 10;
              num = int(ch-'0');
          }
    }
    p->next = new node(num);
    ++a.currentLength;
    return in;
}
void operator+(const bigInteger &a,const bigInteger &b)
{
    int *s;
    int maxn = (a.currentLength> b.currentLength)? a.currentLength:b.currentLength;
    s = new int [maxn+5];
    int ss=0;
    typedef bigInteger::node node;
    node *p = a.head->next,*q = b.head->next,*tmp;
    bigInteger c;
    node *t = c.head;
    int m=0;
    while(p!=NULL && q!=NULL)
    {
        int pp = p->data+q->data+m;
        t->next = new node(pp%100000000);
        s[ss++] = pp%100000000;
        if(pp>=100000000) m = 1;
        else m=0;
        t = t->next;
        p = p->next;
        q = q->next;
    }
    if(p==NULL) tmp = q;
    else tmp = p;
    while(tmp != NULL)
    {
        int pp = tmp->data+m;
        t->next = new node(pp%100000000);
        s[ss++] = pp%100000000;
        if(pp >= 100000000) m = 1;
        else m=0;
        t = t->next;
        tmp = tmp->next;
    }
    if(m!=0)
    {
        t->next = new node(m);
        s[ss++] = m;
        t = t->next;
    }
    cout<<s[ss-1];
    for(int i=ss-2;i>=0;--i)
    {
        if(s[i]==0) {cout<<"00000000";} //处理0的情况
        else if(s[i]<10000000) {
            int j=1;
            int t=1;
            while(s[i]/j != 0) {++t;j*=10;}
            for(int k=0;k<=8-t;++k) cout<<'0';
            cout<<s[i];
        }
        else
            cout<<s[i];
    }
    delete [] s;
}
int main()
{
    bigInteger a,b;
    cin>>a;
    cin>>b;
    a+b;
    return 0;
}
