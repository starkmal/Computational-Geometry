#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const db eps=1e-9,Inf=1e9;
const int N=505;

struct Point{
	db x,y;
	Point(){}
	Point(db a,db b):x(a),y(b){}
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
	return Point(lambda*rhs.x,lambda*rhs.y);
}
db operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}
db operator ^ (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.x+lhs.y*rhs.y;
}

struct Line{
	Point p,v;
	Line(){}
	Line(const Point& a,const Point& b):p(a),v(b){}
};
Point operator * (const Line& lhs,const Line& rhs){
	return lhs.p+(rhs.p-lhs.p)*rhs.v/(lhs.v*rhs.v)*lhs.v;
}

int n,tot;
void HI(const Line& x){
	S[0]=S[tot];
	S[tot+1]=S[0];
	int i,t=0;
	for(i=1;i<=tot;i++){
		if((S[i]-x.p)*x.v>=-eps){
			if((S[i-1]-x.p)*x.v<=-eps)T[++t]=Line(S[i-1],S[i]-S[i-1])*x;
			if((S[i+1]-x.p)*x.v<=-eps)T[++t]=Line(S[i+1],S[i+1]-S[i])*x;
		}
		else T[++t]=S[i];
	}
	for(i=1;i<=t;i++)S[i]=T[i];
	tot=t;
}
db cal(db x,Line l){
	return l.p.y+(l.v.y/l.v.x)*(x-l.p.x);
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%lf",&A[i].x);
	for(i=1;i<=n;i++)scanf("%lf",&A[i].y);
	S[++tot]=Point(-Inf,-Inf);
	S[++tot]=Point(Inf,-Inf);
	S[++tot]=Point(Inf,Inf);
	S[++tot]=Point(-Inf,Inf);
	for(i=1;i<n;i++)
		HI(Line(A[i],A[i+1]-A[i]));
	sort(S+1,S+1+tot);
	db ans=Inf,y;
	for(i=1;i<=tot;i++){
		k=lower_bound(A+1,A+1+n,S[i])-A;
		if(k==n){
			if(fabs(S[i].x-A[k].x)<=eps)ans=min(ans,S[i].y-A[k].y);
			else break;
		}
		else{
			y=cal(S[i].x,Line(A[i],A[i+1]-A[i]));
			printf("%.3lf %.3lf %.3lf %.3lf %.3lf\n",S[i].x,S[i].y,A[i].x,A[i].y,y);
			ans=min(ans,S[i].y-y);
		}
	}
	for(i=1;i<=n;i++){
		k=lower_bound(S+1,S+1+n,A[i])-S;
		if(k==tot){
			if(fabs(S[k].x-A[i].x)<=eps)ans=min(ans,S[k].y-A[i].y);
			else break;
		}
		else {
			y=cal(A[i].x,Line(S[i],S[i+1]-S[i]));
			printf("%.3lf %.3lf %.3lf\n",A[i].x,A[i].y,y);
			ans=min(ans,y-A[i].y);
		}
	}
	printf("%.3lf",ans);
}
