#include <iostream>
#include <iomanip>
using namespace std;
template<class T>
class seqQueue
{
private:
    int *data;
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
    seqQueue(int init = 1000) {
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

int main()
{
    int N,p,q,carNum = 0,vanNum = 0;
    cin>>N;
    seqQueue<int> car_s(N),van_s(N);
    for(int i=0;i<N;++i)
    {
        cin>>p>>q;
        if(p==0)
            {
                car_s.enqueue(q);
                ++carNum;
            }
        else
           {
               van_s.enqueue(q);
               ++vanNum;
           }
    }
    int current_time = 0,carWait = 0,vanWait = 0;
    for(int time = 0;!car_s.isEmpty() || !van_s.isEmpty(); time +=10)
    {
        int ship = 0;
        for(ship = 0;!car_s.isEmpty() && ship<8 && car_s.getHead()<=time;++ship)
        {
            carWait += time - car_s.dequeue();
        }
        for(;!van_s.isEmpty() && ship<10 && van_s.getHead()<=time ;++ship)
        {
            vanWait += time - van_s.dequeue();
        }
        for(;!car_s.isEmpty() && ship<10 && car_s.getHead()<=time;++ship)
        {
            carWait += time - car_s.dequeue();
        }
    }
    if(carNum == 0)
        cout<<"0.000";
    else
        cout<<fixed<<setprecision(3)<<carWait/(double)carNum;
    cout<<" ";
    if(vanNum == 0)
        cout<<"0.000";
    else
        cout<<fixed<<setprecision(3)<<vanWait/(double)vanNum;
    return 0;
}
