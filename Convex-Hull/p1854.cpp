#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const int N=10005;
const db eps=1e-7;

struct Point{
	db x,y;
	void rotate(Point& a,db theta){
		a.x=a.x*cos(theta)-a.y*sin(theta);
		a.y=a.x*sin(theta)+a.y*cos(theta);
	}
	Point(){}
	Point(db a,db b){
		x=a+eps,y=b+eps;
		rotate(*this,eps);
	}
}P[N];
db getdis(const Point& a,const Point& b){
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
Point operator - (const Point& lhs,const Point& rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
db operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}
Point operator + (const Point& lhs,const Point& rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
bool operator < (const Point& lhs,const Point& rhs){
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
int n,tl,q[N];
int main(){
	int i,j,k;
	db x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf",&x,&y);
		P[i]=Point(x,y);
	}
	sort(P+1,P+1+n);
#define cal(a,b,c) ((b-a)*(c-a))
	for(i=1;i<=n;i++){
		while(tl>1&&cal(P[q[tl-1]],P[q[tl]],P[i])<=0)tl--;
		q[++tl]=i;
	}
	int tmp=tl;
	for(i=n-1;i;i--){
		while(tl>tmp&&cal(P[q[tl-1]],P[q[tl]],P[i])<=0)tl--;
		q[++tl]=i;
	}
	db ans=0;
	for(i=1;i<tl;i++)ans+=getdis(P[q[i]],P[q[i+1]]);
	printf("%.2lf",ans);
}
