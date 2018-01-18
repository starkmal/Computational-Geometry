#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const int N=5005;
const db eps=1e-7;

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
}P[N],Q[N];
bool operator < (const Point &lhs,const Point &rhs){
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
Point operator + (const Point &lhs,const Point &rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator - (const Point &lhs,const Point &rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
db operator * (const Point &lhs,const Point &rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}
db getdis(const Point &lhs,const Point &rhs){
	return sqrt((lhs.x-rhs.x)*(lhs.x-rhs.x)+(lhs.y-rhs.y)*(lhs.y-rhs.y));
}
int n,tl;
int main(){
	int i,j,k,t;
	db x,y,ans=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf",&x,&y);
		P[i]=Point(x,y);
	}
	sort(P+1,P+1+n);
	for(i=1;i<=n;i++){
		while(tl>1&&(Q[tl]-Q[tl-1])*(P[i]-Q[tl-1])<=0)tl--;
		Q[++tl]=P[i];
	}
	t=tl;
	for(i=n-1;i;i--){
		while(tl>t&&(Q[tl]-Q[tl-1])*(P[i]-Q[tl-1])<=0)tl--;
		Q[++tl]=P[i];
	}
	for(i=1;i<tl;i++)ans+=getdis(Q[i],Q[i+1]);
	printf("%.2lf",ans);
}
