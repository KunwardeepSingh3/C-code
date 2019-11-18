#include <iostream>
#include <iomanip>
using namespace std;

class PointInt;
class PointDbl;

class PointInt{
public:
PointInt(){
x = 0;
y = 0;
}

void set(int a,int b){
x = a;
y = b;
}
int getx()const{return x;}
int gety()const{return y;}
  
PointInt& operator=(const PointInt &rhs){
if(&rhs == this){
return *this;
}
x = rhs.getx();
y = rhs.gety();
return *this;
}

PointInt& operator=(const PointDbl &rhs);
private:
int x,y;
};

class PointDbl{
public:
PointDbl(){
x = 0;
y = 0;
}
  
void set(double a,double b){
x = a;
y = b;
}
  
double getx()const{return x;}
double gety()const{return y;}
  
PointDbl& operator=(const PointInt &rhs){
x = (double)(rhs.getx());
y = (double)(rhs.gety());
return *this;
}
PointDbl& operator=(const PointDbl &rhs){
if(&rhs == this){
return *this;
}
x = rhs.getx();
y = rhs.gety();
   
return *this;
}
private:
double x,y;
};

PointInt& PointInt::operator=(const PointDbl &rhs){
cout <<"\nWARNING : Will Loss in Decimal data \n";
x = (int)rhs.getx();
y = (int)rhs.gety();

return *this;
}

PointDbl operator+(PointDbl dbl,PointInt pint){
PointDbl res;
res.set((dbl.getx()+pint.getx()),(dbl.gety()+pint.gety()));
return res;
}
PointDbl operator+(PointInt pint,PointDbl dbl){
PointDbl res;
res.set((dbl.getx()+pint.getx()),(dbl.gety()+pint.gety()));
return res;
}

     //QUESTION 8 OVERLOADING OPERATORS

bool operator==(const PointDbl &u, const PointDbl &v) {
if((u.getx() == v.getx()) && (u.gety() == v.gety()))
return true;
else
return false;
}
bool operator==(const PointInt &u, const PointInt &v){
if((u.getx() == v.getx()) && (u.gety() == v.gety()))
return true;
else
return false;
}
bool operator==(const PointDbl &u, const PointInt &v){
if((u.getx() == v.getx()) && (u.gety() == v.gety()))
return true;
else
return false;
}
bool operator==(const PointInt &u, const PointDbl &v) {
if((u.getx() == v.getx()) && (u.gety() == v.gety()))
return true;
else
return false;
}

    // BONUS OVERLOAD OPERATOR!=
bool operator!= (const PointDbl &u, const PointDbl &v) {
if((u.getx() != v.getx()) && (u.gety() != v.gety()))
return true;
else return false;
}


int main(){
PointDbl dp,pdbl;
PointInt ip,pint;
pdbl.set(1.1,2.2);
pint.set(3,4);

dp = pint;
ip = pdbl;

PointDbl s1 = pdbl + pint;
PointDbl s2 = pint + pdbl;

cout<< "dp " << dp.getx() << " " << dp.gety() << endl;
cout<< "ip " << ip.getx() << " " << ip.gety() << endl;
cout << "s1 " << s1.getx() << " " << s1.gety() << endl;
cout << "s2 " << s2.getx() << " " << s2.gety() << endl;

return 0;
}
