#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;

struct person{
    int time;
    bool sex;
};
bool compareTime(person a,person b){return a.time<b.time;}
int l[100000];
person p[10000000];
int main()
{
    int tmpp;
    int n,m;
    cin>>n;
    //int l[n];
    for(int i=0;i<n;i++)
        cin>>l[i];
    cin>>m;
    //person p[m];
    for(int i=0;i<m;i++)
    {
        cin>>tmpp>>p[i].time;
        if(tmpp==1)
            p[i].sex=true;
        else
            p[i].sex=false;
    }
    sort(p,p+m,compareTime);
    /*for(int i=0;i<m;i++)
    {
       cout<<p[i].sex<<p[i].time<<endl;
    }*/
    double maleTime=0;
    double femaleTime=0;
    int nmale=0;
    int nfemale=0;
    queue<person> male;
    queue<person> female;
    for(int i=0;i<m;i++)
    {
        if(p[i].sex)
        {
            male.push(p[i]);
            nmale++;
        }
        else
        {
            female.push(p[i]);
            nfemale++;
        }
    }

    long long cur=0;
    for(int i=0;i<n;i++)
    {
        while((!male.empty())&&(!female.empty())&&(male.front().time<=cur)&&(female.front().time<=cur))
        {

            maleTime+=cur-male.front().time;
            //cout<<l[imusic]-tmp.time<<endl;
            femaleTime+=cur-female.front().time;
            male.pop();
            female.pop();
        }
        if(i!=n-1) cur += l[i];
    }
    while(!male.empty())
    {
            maleTime+=cur-male.front().time;
            //cout<<l[imusic]-tmp.time<<endl;

            male.pop();

    }
    while(!female.empty())
    {
             femaleTime+=cur-female.front().time;
             female.pop();
    }
    cout << setiosflags(ios::fixed) << setprecision(2) << maleTime/nmale << ' ' << femaleTime/nfemale;
	return 0;
}
