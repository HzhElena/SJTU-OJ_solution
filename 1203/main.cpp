#include <string>
#include <sstream>
#include <iostream>
using namespace std;
template<class T> class seqList;
template<class T> ostream & operator<<(ostream &os,const seqList<T> &x);
template<class T> istream & operator>>(istream &in,seqList<T> &x);
template<class T> seqList<T> operator+(const seqList<T> &a,const seqList<T> &b);
template<class T>
class seqList
{
    friend ostream & operator<<<>(ostream &os,const seqList<T> &x);
    friend istream & operator>><>(istream &in,seqList<T> &x);
    friend seqList<T> operator+<>(const seqList<T> &a,const seqList<T> &b);
private:
    T *data;
    int maxSize;
    int currentLength;
    void doubleSpace()
    {
        T *tmp = data;
        maxSize *= 2;
        data = new T [maxSize];
        for(int i=0;i<currentLength;++i)
            data[i] = tmp[i];
        delete [] tmp;
    }
public:
    seqList(int initSize = 10):maxSize(initSize) {currentLength = 0; data = new T [maxSize];}
    ~seqList() {delete[]data;}
    void clear() {currentLength = 0;}
    seqList(const seqList &other)
    {
        maxSize = other.maxSize;
        data = new T [maxSize];
        currentLength = other.currentLength;
        for(int i=0;i<currentLength;++i)
            data[i] = other.data[i];
    }
    seqList & operator=(const seqList &other)
    {
        if(this == &other) return *this;
        delete[] data;
        maxSize = other.maxSize;
        data = new T [maxSize];
        currentLength = other.currentLength;
        for(int i=0;i<currentLength;++i)
            data[i] = other.data[i];
        return *this;
    }
    void insert_at_end(const T &x)
    {
        if(currentLength == maxSize) doubleSpace();
        data[currentLength++] = x;
    }
};
template<class T>
ostream & operator<<(ostream &os,const seqList<T> &x)
    {
        for(int i = 0;i<x.currentLength;++i)
            os<<x.data[i]<<' ';
        return os;
    }
template<class T>
istream & operator>>(istream &in,seqList<T> &x)
    {
        int i=0;
        string s;
       // cout<<"s: "<<s<<endl;
        getline(in,s);
        while(s=="" || s=="\n") getline(in,s);
        stringstream ss(s);
        T tmp;
        while(ss>>tmp)
        {
          //  cout<<"tmp: "<<tmp<<endl;
            x.data[i] = tmp;
            ++i;
        }
        x.currentLength = i;
      //  cout<<"x.curret: "<<x.currentLength<<endl;
        return in;
    }
template<class T>
seqList<T> operator+(const seqList<T> &a,const seqList<T> &b)
{
    seqList<T> c = a;
    //cout<<111<<endl;
    for(int i = 0;i<b.currentLength;++i)
        c.insert_at_end(b.data[i]);
    return c;
}

int main()
{
    string s;
    getline(cin,s);
    int n1,n2;
    cin>>n1>>n2;
    if(s=="int"){
        seqList<int> a(n1),b(n2),c(n1+n2);
        cin>>a>>b;
        c = a+b;
        cout<<c;
    }
    else if(s=="double")
    {
        seqList<double> a(n1+n2),b(n2),c(n1+n2);
        cin>>a>>b;
      //  cout<<"a: "<<a<<endl;
        c = a+b;
        cout<<c;
    }
    else if(s=="char")
    {
        seqList<char> a(n1),b(n2),c(n1+n2);
        cin>>a>>b;
        c = a+b;
        cout<<c;
    }
}
