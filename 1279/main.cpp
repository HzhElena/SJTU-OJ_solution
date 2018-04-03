#include <iostream>
#include <cstring>
using namespace std;
template<class T>
class seqQueue
{
private:
    T *data;
    int maxSize;
    int front;
    int rear;
    void doubleSpace()
    {
        T *tmp = data;
        data = new T[maxSize*2];
        for(int i=1;i<maxSize;++i)
            data[i] = tmp[(front+i)%maxSize];
        front = 0;
        rear = maxSize-1;
        maxSize *= 2;
        delete tmp;
    }
public:
    seqQueue(int init = 10) {
        maxSize = init;
        data = new T[maxSize];
        front = rear = 0;
    }
    ~seqQueue() {delete [] data;}
    bool isEmpty() const {return rear==front;}
    void enqueue(const T &x)
    {
        if((rear+1)%maxSize == front)
            doubleSpace();
        rear = (rear+1)%maxSize;
        data[rear] = x;
    }
    T getHead() const
    {
        return data[(front+1)%maxSize];
    }
    T dequeue()
    {
        front = (front+1)%maxSize;
        return data[front];
    }
};
void quickSort(int s[],int l,int r)
{
    if(l<r)
    {
        int i=l,j=r,x=s[l];
        while(i<j)
        {
            while(i<j && s[j]>=x)
                --j;
            if(i<j)
                s[i] = s[j];
            while(i<j && s[i]<=x)
                ++i;
            if(i<j)
                s[j] = s[i];
        }
        s[i] = x;
        quickSort(s,l,i-1);
        quickSort(s,i+1,r);
    }
}
void read_number(int &number)
{
    char ch;
    int len = 0;
    number = 0;
    while((ch=cin.get())!='\n' && len!=7)
    {
        if(ch == '-') ;
        else if(ch<='9' && ch>='0')
        {
            number = number*10 + ch-'0';
            ++len;
        }
        else
        {
            if(ch<='R')
                number = number * 10 + (ch-'A')/3 + 2;
            else
                number = number * 10 + (ch-'A'-1)/3 + 2;
            ++len;
        }
    }
    while(ch!='\n') ch = cin.get();
}
void print_num(int& num)
{
    char ex[9];
    ex[8] = '\0';
    ex[3] = '-';
    int i=7;
    while(num > 0)
    {
        if(i == 3) --i;
        ex[i] = num % 10 + '0';
        --i;
        num /= 10;
    }
    while(i!=-1)
    {
        if(i == 3) --i;
        ex[i] = '0';
        --i;
    }
    cout<<ex<<' ';
}
template<class T>
void merge(T a[],int left,int mid,int right)
{
    T *tmp = new T[right-left+1];
    int i=left,j = mid,k=0;
    while(i<mid && j<=right)
    {
        if(a[i]<a[j]) tmp[k++] =  a[i++];
        else tmp[k++] = a[j++];
    }
    while(i<mid) tmp[k++] = a[i++];
    while(j<=right) tmp[k++] = a[j++];
    for(int i=left;i<=right;++i)
        a[i] = tmp[i-left];
    delete [] tmp;
}
template<class T>
void merge_sort(T a[],int left,int right)
{
    if(left == right) return;
    int mid = (right+left)/2;
    merge_sort(a,left,mid);
    merge_sort(a,mid+1,right);
    merge(a,left,mid+1,right);
}
struct node
{
    int num;
    int time;
};
int main()
{
    int n;
    cin>>n;
    cin.get();
    int a[n];
    for(int i=0;i<n;++i)
        read_number(a[i]);
    merge_sort(a,0,n-1);
    node cur;
    seqQueue<node> s;
    int tmp = 0;
    while(tmp < n)
    {
        cur.num = a[tmp];
        cur.time = 1;
        ++tmp;
        while(a[tmp] == cur.num) { ++tmp; ++cur.time; }
        if(cur.time > 1)
            s.enqueue(cur);
    }
    if(s.isEmpty())
        cout<<"No duplicates.";
    while(!s.isEmpty())
    {
        cur = s.dequeue();
        print_num(cur.num);
        cout<<cur.time<<endl;
    }
    return 0;
}
