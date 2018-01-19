#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;

typedef double db;
const db pi=acos(-1.0);
const db eps=1e-8,Inf=1e5;
const int N=505;

struct Point{
	db x,y;
	void Rotate(db theta){
		db a=x,b=y;
		x=a*cos(theta)-b*sin(theta);
		y=a*sin(theta)+b*cos(theta);
	}
	Point(){}
	Point(db a,db b):x(a),y(b){
//		x+=eps,y+=eps;
//		this->Rotate(eps);
	}
}A[N],S[N],T[N];

bool operator < (const Point& lhs,const Point& rhs){
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
Point operator + (const Point& lhs,const Point& rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator - (const Point& lhs,const Point& rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
Point operator * (db lambda,const Point& rhs){
	return Point(rhs.x*lambda,rhs.y*lambda);
}
db operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.x+lhs.y*rhs.y;
}
db operator ^ (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}

struct Line{
	Point p,v;
	Line(){}
	Line(Point a,Point b):p(a),v(b){}
};
Point operator * (const Line& lhs,const Line& rhs){
	//%%%Sparrow
	db k=((lhs.p-rhs.p)^lhs.v)/(rhs.v^lhs.v);
	return rhs.p+k*rhs.v;
//	return lhs.p+(((rhs.p-lhs.p)^rhs.v)/(lhs.v^rhs.v))*lhs.v;		//A.p+k*A.v=B.p+k*B.v;
}
int n,m,tot;
void HS(Line x){
	int i,t=0;
	S[0]=S[tot];
	S[tot+1]=S[1];
	for(i=1;i<=tot;i++){
		if(((S[i]-x.p)^x.v)>=-eps){
			if(((S[i-1]-x.p)^x.v)<=-eps)T[++t]=Line(S[i-1],S[i]-S[i-1])*x;
			if(((S[i+1]-x.p)^x.v)<=-eps)T[++t]=Line(S[i],S[i+1]-S[i])*x;
		}else T[++t]=S[i];
	}
	for(i=1;i<=t;i++)S[i]=T[i];
	tot=t;
}
int main(){
	int i,j,k;
	db x,y;
	S[++tot]=Point(-Inf,-Inf);
	S[++tot]=Point(Inf,-Inf);
	S[++tot]=Point(Inf,Inf);
	S[++tot]=Point(-Inf,Inf);
	scanf("%d",&n);
	while(n--){
		scanf("%d",&m);
		for(i=1;i<=m;i++){
			scanf("%lf%lf",&x,&y);
			A[i]=Point(x,y);
		}
		for(i=2;i<=m;i++)HS(Line(A[i],A[i]-A[i-1]));
		HS(Line(A[m],A[1]-A[m]));
	}
	db ans=0.0;
//	for(i=1;i<tot;i++)
//		ans+=S[i]^S[i+1];
//	ans+=S[tot]^S[1];
	S[0]=S[tot];
	for(i=0;i<tot;i++)
		ans+=S[i]^S[i+1];
	printf("%.3lf",ans/2);
}
