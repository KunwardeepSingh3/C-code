#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Child;
class Parent;
class Parent {
public:
Parent();
string getName() const;
void setName(string n);
void addChild(const Child &c);
int numChildren() const;
const vector<Child> & getChildren() const;

private:
string name; 
vector<Child> children;
};
class Child {
public:
 Child (string n, int a, const Parent &pt);
    string getName() const;
    int getAge() const;
    const Parent* getParent() const;
  private:
    string name;
    int age;
    Parent p;
};

Parent::Parent() {}
string Parent::getName() const {
return name;
}
void Parent::setName(string n){
 name = n;
}
void Parent::addChild(const Child &c){
    children.push_back(c);
}
int Parent::numChildren() const{
    return children.size();
}
const vector<Child>& Parent::getChildren() const{
    return children;
}

Child::Child(string n, int a, const Parent &pt) {
name = n;
age = a;
p = pt;
}
string Child::getName() const{
return name;
}
int Child::getAge() const{
return age;
}
const Parent* Child:: getParent() const{
return &p;
}
 
int main () {
Parent a, b;
       a.setName("Alice");
       b.setName("Bob");
       Child c("Charlie", 5, a);
       Child d("Dora", 6, a);
       Child e("Elizabeth", 7, b);
       a.addChild(c);
       a.addChild(d);
       b.addChild(e);
       cout << "Parent of " << c.getName() << " is " << c.getParent()->getName() << endl;
       cout << "Parent of " << d.getName() << " is " << d.getParent()->getName() << endl;
       cout << "Parent of " << e.getName() << " is " << e.getParent()->getName() << endl;
       cout << endl;
       cout << "Children of " << a.getName() << endl;
       const vector<Child> &av = a.getChildren();
       for (int i = 0; i < av.size(); ++i)
         cout << setw(12) << av[i].getName() << setw(12) << av[i].getAge() << endl;
       cout << endl;
       cout << "Children of " << b.getName() << endl;
       const vector<Child> &bv = b.getChildren();
       for (int i = 0; i < bv.size(); ++i)
         cout << setw(12) << bv[i].getName() << setw(12) << bv[i].getAge() << endl;
return 0; 
}
