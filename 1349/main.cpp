#include <iostream>

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
struct node
{
    int x;
    int y;
    int color;
    node(int xx=0,int yy=0,int c= 0)
    {
        x = xx;
        y = yy;
        color = c;
    }
};
int main()
{
    seqQueue<node> s;
    int row,col;
    cin>>row;
    cin>>col;
    int maze[row][col];
    char ch;
    cin.get();
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
       {
        ch = cin.get();
//        cout<<ch<<' ';
        if(ch == 'R') maze[i][j] = 0;
        else maze[i][j] = 1;
       }
       cin.get();
    }
    int total_way = 0;
    node cur(0,0,maze[0][0]),tmp;
    s.enqueue(cur);
    while(!s.isEmpty())
    {
        cur = s.dequeue();
        if(cur.x == row-1 && cur.y == col-1) { ++total_way; continue;}
        for(int i = cur.x+1;i<row;++i)
            for(int j = cur.y+1;j<col;++j)
        {
            if(maze[i][j] == cur.color)
                continue;
            else
            {
                tmp.x = i;
                tmp.y = j;
                tmp.color = maze[i][j];
                s.enqueue(tmp);
            }
        }
    }
    cout<<total_way;
    return 0;
}
