#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class PointXY {
public:
double x,y;
};

double distance(const PointXY &u,const PointXY &v) {
return sqrt((u.x - v.x)* (u.x - v.x)+ (u.y - v.y)*(u.y - v.y));
}

void area_perimeter(vector<PointXY> &v,double &area,double &perimeter)
{
double a = distance(v[0],v[1]);
double b = distance(v[1],v[2]);
double c = distance(v[2],v[0]);

perimeter = a+b+c;
double s = perimeter/2.0;
area = sqrt(s*(s-a)*(s-b)*(s-c));
}

int main() {
int n = 3;
vector<PointXY> v(n);

v[0].x = 3.5;
v[0].y = 0.4;

v[1].x = 7.2;
v[1].y = 0.6;

v[2].x = 4.1;
v[2].y = 5.6;

double area,perimeter;
area_perimeter(v,area,perimeter);

cout<<"area "<<area<<endl;
cout<<"perimeter "<<perimeter<<endl;

return 0;
}


