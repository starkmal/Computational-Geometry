#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const int N=100005;
const db eps=1e-7;

struct Point{
	db x,y;
	void Rotate(Point &p,db theta){
		db x=p.x,y=p.y;
		p.x=x*cos(theta)-y*sin(theta);
		p.y=x*sin(theta)+y*cos(theta);
	}
	Point(){}
	Point(db a,db b){
		x=a+eps,y=b+eps;
		Rotate(*this,eps);
	}
}A[N],T[N];

bool operator < (const Point& lhs,const Point& rhs){
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
Point operator + (const Point& lhs,const Point& rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator - (const Point& lhs,const Point& rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
db operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}

inline bool judge(const Point& a,const Point& b,const Point& c){
	return (b-a)*(c-a)<=0;
}//返回向量ac是否在向量ab的右侧

int n,t;
void Graham(){
	sort(A+1,A+1+n);
	for(int i=1;i<=n;i++){
		while(t>1&&judge(T[t-1],T[t],A[i]))t--;
		T[++t]=A[i];
	}
	int tmp=t;
	for(int i=n-1;i;i--){
		while(t>tmp&&judge(T[t-1],T[t],A[i]))t--;
		T[++t]=A[i];
	}
	t--;
}
db RC(){
	db ans=0;
	int x,y,k;
	db t1,t2;
	for(x=1,y=2;x<=t;x++){
		while((T[x+1]-T[x])*(T[y]-T[x])<(T[x+1]-T[x])*(T[y+1]-T[x]))
			y=y%t+1;
		t1=t2=0;
		for(k=1;k<=t;k++)
			t1=max(t1,(T[k]-T[x])*(T[y]-T[x])),
			t2=max(t2,(T[y]-T[x])*(T[k]-T[x]));
		ans=max(ans,t1+t2);
	}
	return ans;
}
int main(){
	int i,j,k;
	db x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf",&x,&y);
		A[i]=Point(x,y);
	}
	Graham();
	printf("%.3lf",RC()/2);
}
