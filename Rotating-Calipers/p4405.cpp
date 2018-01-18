#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const db eps=1e-10;
const db pi=acos(-1.0);
const int N=50005;
#define DEB 0

struct Point{
	db x,y;
	void Rotate(db theta){
		db a=x,b=y;
		x=a*cos(theta)-b*sin(theta);
		y=a*sin(theta)+b*cos(theta);
	}
	Point(){}
	Point(db a,db b){
		x=a+eps,y=b+eps;
		this->Rotate(eps);
	}
}A[N],T[N];
bool operator < (const Point& lhs,const Point& rhs) {
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
Point operator + (const Point& lhs,const Point& rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator - (const Point& lhs,const Point& rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
db operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.x+lhs.y*rhs.y;
}
Point operator * (const Point& lhs,db lambda){
	return Point(lhs.x*lambda,lhs.y*lambda);
}
Point operator / (const Point& lhs,db lambda){
	return Point(lhs.x/lambda,lhs.y/lambda);
}
db operator ^ (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}
db mod(const Point& t){
	return sqrt(t.x*t.x+t.y*t.y);
}
int fcmp(db x,db y){/*
	if(x-y<eps)return -1;
	if(x-y>-eps)return 1;
	return 0;*/
	if(fabs(x-y)<eps)return 0;
	if(x-y<-eps)return -1;
	if(x-y>eps)return 1;
}

int n,tot;
void Graham(){
	sort(A+1,A+1+n);
	int i,t;
	for(i=1;i<=n;i++){
		while(tot>1&&fcmp((T[tot]-T[tot-1])^(A[i]-T[tot-1]),0)!=1)tot--;
		T[++tot]=A[i];
	}
	t=tot;
	for(i=n-1;i;i--){
		while(tot>t&&fcmp((T[tot]-T[tot-1])^(A[i]-T[tot-1]),0)!=1)tot--;
		T[++tot]=A[i];
	}
	tot--;
}

int c[5];
Point g[5];
void RC(int x){
	int i;
	c[1]=(x+1)%tot+1;
	while(fcmp((T[x+1]-T[x])^(T[c[1]]-T[x]),(T[x+1]-T[x])^(T[c[1]+1]-T[x]))<0)
		c[1]=c[1]%tot+1;
	c[2]=x%tot+1;
	while(fcmp((T[c[2]]-T[x])*(T[x+1]-T[x]),(T[c[2]+1]-T[x])*(T[x+1]-T[x]))<0)
		c[2]=c[2]%tot+1;
	c[3]=c[1]%tot;
	while(fcmp((T[c[3]]-T[x])*(T[x+1]-T[x]),(T[c[3]+1]-T[x])*(T[x+1]-T[x]))>0)
		c[3]=c[3]%tot+1;
}
int main(){
	int i,j,k;
	db x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf",&x,&y);
		A[i]=Point(x,y);
//		A[i].x=x,A[i].y=y;
	}
	Graham();
#if DEB
	RC(5);
	for(i=1;i<=3;i++)
		printf("%.3lf %.3lf\n",T[c[i]].x,T[c[i]].y);
#endif
	db len,h,l1,l2,maxx=1e9;
	Point tmp,ttt;
	for(i=1;i<=tot;i++){
		RC(i);
		len=mod(T[i+1]-T[i]);
		h=((T[i+1]-T[i])^(T[c[1]]-T[i]))/mod(T[i+1]-T[i]);
		l1=(T[c[2]]-T[i])*(T[i+1]-T[i])/len;
		l2=(T[c[3]]-T[i+1])*(T[i]-T[i+1])/len;
		if(fcmp((l1+l2-len)*h,maxx)<0){
			maxx=(l1+l2-len)*h;
			
			tmp=(T[i+1]-T[i])*(l1/len);
			g[1]=T[i]+tmp;
			
			tmp=(T[i]-T[i+1])*(l2/len);
			g[4]=T[i+1]+tmp;
			
			ttt=(T[i+1]-T[i])/mod(T[i+1]-T[i]);
			ttt.Rotate(pi/2);
			tmp=ttt*h;
			g[2]=g[1]+tmp;
			g[3]=g[4]+tmp;
		}
	}
	printf("%.6lf\n",maxx);
	int lb=1;
	for(i=1;i<=4;i++)
		if(fcmp(g[i].y,g[lb].y)<0||(fcmp(g[i].y,g[lb].y)==0&&fcmp(g[i].x,g[lb].x)<0))lb=i;

	for(i=0;i<=3;i++){
		j=(lb+i-1)%4+1;
		if(fcmp(fabs(g[j].x),0.00001)<0)printf("0.00000 ");
		else printf("%.5lf ",g[j].x);
		if(fcmp(fabs(g[j].y),0.00001)<0)printf("0.00000\n");
		else printf("%.5lf\n",g[j].y);
	}
}
