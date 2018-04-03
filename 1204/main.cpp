#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class linkList
{
    friend ostream &operator<<(ostream & os,const linkList &x);
    friend istream &operator>>(istream &in, linkList &x);
private:
    struct node
    {
        string data;
        node *next;
        node(const string &ss,node *n=NULL):data(ss),next(n) {}
        node() {next = NULL;}
    };

    node *head;
    int currentLength;

    node *move(int i)
    {
        node *p = head->next;
        while(i--) {
        if (p==NULL) return NULL;
        p = p->next;
        }
        return p;
    }
    void error()
    {
        cout<<"Error!"<<endl;
    }
    int getNum(char *&s);
public:
    void clear();
    linkList()  {head = new node;currentLength = 0;}
    ~linkList() {clear(); delete head;}
    void ins(char *args);
    void del(char *args);
    void list(char *args);
};
void linkList::clear()
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
ostream &operator<<(ostream & os,const linkList &x)
{
    linkList::node *p = x.head;
    while(p->next != NULL)
    {
        p = p->next;
        cout<<p->data<<endl;
    }
    return os;
}
istream &operator>>(istream &in, linkList &x)
{
    string s;
    int i = 0;
    linkList::node *p = x.head;
    while(getline(in,s))
    {
        if(s=="******") break;
        if(!s.size()) {s = "";}
        p->next = new linkList::node(s);
        p = p->next;
        ++i;
    }
    x.currentLength = i;
    return in;
}
int linkList::getNum(char *&s)
{
    while(*s==' ') ++s;
    if(!(*s<='9' && *s>='0')) {return -1;}
    int num = 0;
    while(*s<='9' && *s>='0')
        {
            num = num*10 + (*s - '0');
            ++s;
        }
    if(*s !=' ' && *s !='\0') return -1;
    return num;
}
void linkList::ins(char *args)
{
    int row,col;
    row = getNum(args);
    col = getNum(args);
    if(row > currentLength || row <= 0) {error(); return;}
    ++args;
    if(*args == '\0') {error();return;}
    string s(args);
    node *p = move(row-1);

    if(p==NULL || col<=0 || col > p->data.length()+1) {error(); return;}

    if(p->data=="") {p->data = s;return;}
    else if(col == p->data.length()+1) p->data = p->data + s;
    else{
        p->data.insert(col-1,s);
    }
}
void linkList::del(char *args)
{
    int row,col,num;
    row = getNum(args);
    col = getNum(args);
    num = getNum(args);

    if(row > currentLength || row <= 0) {error(); return;}
    node *p = move(row-1);
    if(p==NULL) {error(); return;}

    if(col <= 0 || col>p->data.length() || num<0 || col + num - 1> p->data.length()) {error(); return;}

    p->data.erase(col-1,num);
}
void linkList::list(char *args)
{
    int row,row2;
    row = getNum(args);
    row2 = getNum(args);
    node *p = move(row-1);
    if(p==NULL || row<0 || row2<0 || row2<row || row2>currentLength) {error(); return;}
    for(int i=0;i<=row2-row;++i)
    {
        cout<<p->data<<endl;
        p = p->next;
    }
}
int main()
{
    linkList v;
    cin>>v;
    char command[150],comName[10];
    while(true)
    {
        int i;
        cin.getline(command,150);
        for(i=0;command[i]!=' ';++i);
        strncpy(comName,command,i);
        if(command[i]!=' ') {cout<<"Error!"<<endl; continue;}
        comName[i] = '\0';
        if(i==0) {cout<<"Error!"<<endl; continue;}
        else if((command + i)=='\0') {cout<<"Error!"<<endl; continue;}
        if(strcmp(comName,"quit")==0) {cout<<v;break;}
        else if(strcmp(comName,"list")==0) v.list(command+i);
        else if(strcmp(comName,"del")==0) v.del(command+i);
        else if(strcmp(comName,"ins")==0) v.ins(command+i);
        else {cout<<"Error!"<<endl; continue;}
    }
    return 0;
}
