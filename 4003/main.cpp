#include <iostream>

using namespace std;
class IllegalSize{};
class OutOfRange{};
template<class> class seqList;
template<class T>
class seqList
{
private:
    int currentLength;
    int maxSize;
    T *data;
    void doubleSpace();
public:
    seqList(int initSize = 10);
    seqList(const seqList<T> & other);
    ~seqList() {delete[]data;}
    void clear() {currentLength = 0;}
    int length() const {return currentLength;}
    T visit(int i) const;
    void insert(int i,const T &);
    void remove(int i);
};
template<class T>
void seqList<T>::doubleSpace()
{
    T *tmp = data;
    maxSize *= 2;
    data = new T[maxSize];
    for(int i=0;i<currentLength;++i)
        data[i] = tmp[i];
    delete [] tmp;
}
template<class T>
seqList<T>::seqList(int initSize)
{
    if(initSize <=0 ) throw IllegalSize();
    maxSize = initSize;
    data = new T [maxSize];
    currentLength = 0;
}
template<class T>
T seqList<T>::visit(int i) const
{
    if(i<0 || i>=currentLength) throw OutOfRange();
    return data[i];
}
template<class T>
void seqList<T>::insert(int i,const T &d)
{
   if(i<0 || i>currentLength) throw OutOfRange();
   if(currentLength == maxSize)
        doubleSpace();
   for(int j=currentLength;j>i;--j)
        data[j] = data[j-1];
   data[i] = d;
   ++currentLength;
}
template<class T>
void seqList<T>::remove(int i)
{
    if(i<0 || i>=currentLength) throw OutOfRange();
    for(int j=i;j<currentLength-1;++j)
        data[j] = data[j+1];
    --currentLength;
}

int main()
{
    int n,k;
    cin>>n>>k;
    seqList<int> v;
    int len = 0;
    int i;
    while(n > 0)
    {
        for(i=0;1<<i <=n;++i) ;
        --i;
        n-=1<<i;
        v.insert(len++,1<<i);
    }
    if(v.length()<=k) {cout<<0;}
    else
    {
        int sum = 0;
        for(int i=v.length()-1;i>=k;--i)
            sum += v.visit(i);
        cout<<v.visit(k-1)-sum;
    }
    return 0;
}
