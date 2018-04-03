#include <iostream>
using namespace std;
template<class T>
class set
{
private:
    struct node
    {
        T data;
        node *next;
        node(const T &d,node *n=NULL):data(d),next(n) {}
        node():next(NULL) {}
        node(const node &other)
        {
            data = other.data;
            next = other.next;
        }
    };
    node *arr;
public:
    set() {arr = new node;}
    set(const set &other)
    {
        arr = new node;
        node *tmp = other.arr, *p = arr;
        while(tmp->next != NULL)
        {
            p->next = new node(tmp->next->data);
            p = p->next;
            tmp = tmp->next;
        }
    }
    void insert(const T &x)
    {
        node *tmp = arr;
        while(tmp->next!=NULL && tmp->next->data < x) tmp = tmp->next;
        if(tmp->next == NULL)
            tmp->next = new node(x);
        else if(tmp->next->data == x)
            return;
        else
            tmp->next = new node(x,tmp->next);
    }
    void merge(const set &other)
    {
        node *tmp = other.arr->next;
        node *p = arr;
        while(tmp != NULL)
        {
            while(p->next != NULL && p->next->data < tmp->data)
                p = p->next;
            if(p->next==NULL) p->next = new node(tmp->data);
            else if(p->next->data == tmp->data) ;
            else
                p->next = new node(tmp->data,p->next);
            tmp = tmp->next;
            p = p->next;
        }
    }
    void sub(const set &other)
    {
        node *tmp = other.arr->next;
        node *p = arr;
        while(tmp != NULL)
        {
            p = arr;
            while(p->next != NULL && p->next->data != tmp->data)
                p = p->next;
            if(p->next && p->next->data == tmp->data)
                {
                    node *tmp = p->next;
                    p->next = tmp->next;
                    delete tmp;
                }
            tmp = tmp->next;
        }
    }
    void multi(const set &other)
    {
        node *tmp = other.arr->next;
        node *p = arr,*q = arr;
        arr = new node;
        node *cur = arr;
        while(tmp != NULL)
        {
            p = q;
            while(p->next != NULL && p->next->data != tmp->data)
                p = p->next;
            if(p->next && p->next->data==tmp->data)
            {
                cur->next = new node(tmp->data);
                cur = cur->next;
                p = p->next;
            }
            tmp = tmp->next;
        }
    }
    void traverse() const
    {
        node *tmp = arr->next;
        while(tmp!=NULL)
        {
            cout<<tmp->data<<" ";
            tmp = tmp->next;
        }
        cout<<endl;
    }
};
int main()
{
    int n,value,m;
    cin>>n;
    char op;
    set<int> s;
    while(n--)
    {
        set<int> other;
        cin>>op;
        cin>>m;
        while(m--)
        {
            cin>>value;
            other.insert(value);
        }
        switch(op)
        {
        case '+':
            s.merge(other);
            s.traverse();
            break;
        case '*':
            s.multi(other);
            s.traverse();
            break;
        case'-':
            s.sub(other);
            s.traverse();
            break;
        }
    }
    return 0;
}
