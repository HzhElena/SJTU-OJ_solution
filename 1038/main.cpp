#include <iostream>

using namespace std;
class linkList
{
private:
    struct node
    {
        int data;
        node *next;
        node *prev;
        node(){next = NULL; prev=NULL;}
        node(const int &d,node *p=NULL,node *n=NULL):data(d),prev(p),next(n) {}
    };
    node *head;
public:
    linkList() {head = NULL;}
    ~linkList() {delete head;}
    class itr
    {
        friend class linkList;
    private:
        node *pos;
    public:
        itr(node *p=NULL):pos(p) {}
        itr operator++()
        {
            return pos = pos->next;
        }
        itr operator--()
        {
            return pos = pos->prev;
        }
        void move_next(int i)
        {
            for(int j=0;j<i;++j)
                pos = pos->next;
        }
        void move_prev(int i)
        {
            for(int j=0;j<i;++j)
                pos = pos->prev;
        }
        int &operator*()
    {
        return pos->data;
    }
    };
    itr begin()
    {
        return head;
    }

    void insert(itr &p,const int &x)// insert after p
    {
        if(p.pos==NULL) {
                head = p.pos = new node(x);
                head->next = head;
                head->prev = head;
                return;
            }
        else
        {
            node *tmp = new node(x,p.pos,p.pos->next);
            p.pos->next->prev = tmp;
            p.pos->next = tmp;
            p.pos = p.pos->next;
        }
    }

    void erase(itr &p)
    {
        if(p.pos==NULL) return;
        else if(p.pos->next == p.pos)
        {
            delete p.pos;
            head = p.pos = NULL;
            return;
        }
        else
        {
            p.pos->prev->next = p.pos->next;
            p.pos->next->prev = p.pos->prev;
            node *q = p.pos->next;
           // cout<<p.pos->data<<endl;
            if(p.pos == head) {head = q;}
            delete p.pos;
            p.pos = q;
        }
    }
};
int main()
{
    typedef linkList::itr itr;
    int n,k;
    cin>>n;
    linkList v;
    itr p = v.begin();
    for(int i=1;i<=n;++i)
        v.insert(p,i);
    p = v.begin();
    int len = n;
    for(int i=1;i<len;++i)
    {
        cin>>k;
        k = (k-1)%n;  //move
        if(k > n/2)
        {
            p.move_prev(n-k);
           // cout<<"*p: "<<*p<<endl;
        }
        else
        {
            p.move_next(k);
           // cout<<"*p: "<<*p<<endl;
        }
        v.erase(p);
        --n;
    }
    p = v.begin();
    cout<<*p;
    return 0;
}
