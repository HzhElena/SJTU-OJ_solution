#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int N=500+5;
const double INF=1e9;
const double eps=1e-8;
const double pi=acos(-1);

struct Point{
    double x,y;
    Point(double a=0,double b=0):x(a),y(b){}
    void print(){printf("%lf %lf\n",x,y);}
};

struct Line{
    Point s,t;
    double k,b;
    Line(){}
    Line(Point a,Point c):s(a),t(c){
        k=(t.y-s.y)/(t.x-s.x);
        b=s.y-k*s.x;
    }
    double f(double x){return k*x+b;}
};

struct Circle{
    double x,r;
    Circle(){}
    Circle(double x,double r):x(x),r(r){}
};

int sgn(double x){
    if(abs(x)<eps) return 0;
    else return x<0?-1:1;
}

Line L[N];
Circle C[N];
int nl;

void addTangentLine(Circle a,Circle b){
    nl++;
    double sina=(a.r-b.r)/(b.x-a.x);
    double cosa=sqrt(1-sina*sina);
    double tana=sina/cosa;
    L[nl].s=Point(a.x+a.r*sina,a.r*cosa);
    L[nl].t=Point(b.x+b.r*sina,b.r*cosa);
    L[nl].k=-tana;
    L[nl].b=L[nl].s.y-L[nl].k*L[nl].s.x;
}
int n;
double alpha,h[N],lb=INF,rb;
double F(double x){
    double re=0;
    for(int i=1;i<=nl;i++) if(x>=L[i].s.x&&x<=L[i].t.x) re=max(re,L[i].f(x));
    for(int i=1;i<=n;i++) if(x>=C[i].x-C[i].r && x<=C[i].x+C[i].r)
        re=max(re,sqrt(C[i].r*C[i].r-(x-C[i].x)*(x-C[i].x)));
    return re;
}
double cal(double l,double r){
    return (F(l)+F(r)+4*F((l+r)/2))*(r-l)/6;
}
double simpson(double l,double r,double now){
    double mid=(l+r)/2,p=cal(l,mid),q=cal(mid,r);
    if(abs(now-p-q)<eps) return now;
    else return simpson(l,mid,p)+simpson(mid,r,q);
}

Point p;
int main(){
    scanf("%d %lf",&n,&alpha);
    for(int i=1;i<=n+1;i++) scanf("%lf",&h[i]),h[i]+=h[i-1];
    for(int i=1;i<=n;i++) scanf("%lf",&C[i].r);
    double ta=tan(alpha);
    p=Point(h[n+1]/ta,0);
    rb=max(rb,p.x);
    C[n].x=h[n]/ta;
    double x=C[n].x,r=C[n].r;
    lb=min(lb,x-r);
    rb=max(rb,x+r);// ±ß½ç
    if(x+r<p.x){
        double l=r*r/(p.x-x);
        double h=sqrt(r*r-l*l);
        L[++nl] = Line(Point(x+l,h),p);
    }
    for(int i=n-1;i>=1;i--){
        C[i].x=h[i]/ta;
        double x=C[i].x,r=C[i].r;
        lb=min(lb,x-r);
        rb=max(rb,x+r);
        if(sgn(C[i+1].x-C[i].x-abs(C[i+1].r-C[i].r))>0)
            addTangentLine(C[i],C[i+1]);
    }
    printf("%.2f",2*simpson(lb,rb,cal(lb,rb)));
    return 0;
}
