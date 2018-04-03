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
    T getTail() const
    {
        return data[rear];
    }
    T dequeue()
    {
        front = (front+1)%maxSize;
        return data[front];
    }
};

struct point
{
    int x;
    int y;
    point(const int &xx=0,const int &yy=0):x(xx),y(yy) {}
};
int path[7];
bool inPath(point &t)
{
    int tmp = 5*t.x+t.y;
    for(int i=0;i<7;++i)
        if(path[i] == tmp)
            return true;
    return false;
}

int maze[5][5];
int visit[5][5];
int dx[] = {-1,0,0,1};
int dy[] = {0,-1,1,0};

int cal()
{
    for(int i=0;i<5;++i)
        for(int j=0;j<5;++j)
            visit[i][j] = 0;
    point cur,tmp,start;
    start.x = path[0]/5;
    start.y = path[0]%5;
    seqQueue<point> q;
    q.enqueue(start);
    int sum = maze[start.x][start.y];
    int cnt = 1;
    while(!q.isEmpty())
    {
        cur = q.dequeue();
        visit[cur.x][cur.y] = 1;
        for(int i=0;i<4;++i)
        {
            tmp.x = cur.x + dx[i];
            tmp.y = cur.y + dy[i];
            if(tmp.x > 4 || tmp.x <0 || tmp.y > 4 || tmp.y < 0)
                continue;
            if(!visit[tmp.x][tmp.y] && inPath(tmp))
            {
                visit[tmp.x][tmp.y] = 1;
                sum += maze[tmp.x][tmp.y];
                ++cnt;
                if(sum > 3)
                    return 0;
                q.enqueue(tmp);
            }
        }
    }
    return (cnt == 7 && sum <= 3);
}
int main()
{
    char ch[6];
    int ans = 0;
    for(int i=0;i<5;++i)
    {
        cin>>ch;
        for(int j=0;j<5;++j)
            maze[i][j] = ((ch[j] == 'H') ? 1:0);
    }
    for(path[0] = 0;path[0]<19;++path[0])
        for(path[1] = path[0]+1;path[1]<20;++path[1])
            for(path[2] = path[1]+1;path[2]<21;++path[2])
                for(path[3] = path[2]+1;path[3]<22;++path[3])
                    for(path[4] = path[3]+1;path[4]<23;++path[4])
                        for(path[5] = path[4]+1;path[5]<24;++path[5])
                            for(path[6] = path[5]+1;path[6]<25;++path[6])
                                ans+=cal();
    cout<<ans;
    return 0;
}
