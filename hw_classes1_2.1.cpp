#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Student {
    private:
       string name;
       vector<double> grades;
    public:
    string getName() const {
return name;
} 
    void setName(const string &s) {
name = s;
}
    string& nameRef() {
return name;
}
    void addGrade(double x) {
        if((x>=0)&&(x<=100))
        grades.push_back(x);
}
    double getAvg() const{
       if (grades.size() == 0)
       return 0;
       double sum=0;
       for (int i=0; i<grades.size(); i++){
       sum += grades[i];
    }
return sum/grades.size();
}
     double highestGrade() const{
        double highest = grades[0];
        if (grades.size() == 0)
        return -1;
     else
        for (int i=0; i<grades.size(); i++) {
        if(grades[i] > highest)
        highest = grades[i];
     }
return highest;
}
     void print() const {
         cout << "name is: " << name << endl;
         if (grades.size() == 0) cout << "no grades posted yet" << endl;
     else
         for (int i=0; i<grades.size(); i++) {
         cout << grades[i] << " ";
     }
     cout << endl;
}
     double* gradePtr(int n) {
   if ((n>grades.size()) || (n<0))
    return NULL;
else
    return &grades[n];
}
};
    void highlow_avg_grade(const Student *a,const Student *b, int n) {
    string name_high, name_low;
    double high = 0, low;
    low = a->getAvg();
    name_low = a->getName();
    if (a->getAvg() > high)
    {
        high = a->getAvg();
        name_high = a->getName();
    }
    for(int i =0; i < n; i ++){
        if(b[i].getAvg() < low)
        {
            low = b[i].getAvg();
            name_low = b[i].getName();
        }
        if(b[i].getAvg() > high)
        {
            high = b[i].getAvg();
            name_high = b[i].getName();
        }
    }
    cout << "high avg = " << name_high << " " << high << endl;
    cout << "low avg = " << name_low << " " << low << endl;
}
void highlow_top_grade(const Student *a,const Student *b, int n){
    string name_high, name_low;
    double high = 0, low;
    low = a->highestGrade();
    name_low = a->getName();
    if(a->highestGrade() > high)
    {
        high = a->highestGrade();
        name_high = a->getName();
    }
    for(int i = 0; i<n; i++)
    {
        if (b[i].highestGrade() < low)
        {
            low = b[i].highestGrade();
            name_low = b[i].getName();
        }
        if (b[i].highestGrade() > high)
        {
            high = b[i].highestGrade();
            name_high = b[i].getName();
        }
    }
    cout << "high top grade = " << name_high << " " << high << endl;
    cout << "low top grade = " << name_low << " " << low << endl;
}

int main() {
       Student *Alice = new Student;
       Student *BobTwins = new Student[2];
       Alice->nameRef() = "Alice";
       BobTwins[0].setName("Bob A");
       BobTwins[1].setName("Bob B");
       Alice->print();
       for (int i=0; i<2; i++) {
          BobTwins[i].print();
}
       for (int i = 65; i <= 110; i += 10) {
       Alice->addGrade(i+0.1);
}
       for (int i = 57; i <= 110; i += 10) {
       BobTwins[0].addGrade(i+0.2);
}
       int igrade=0;
       while (true) {
       double *d = BobTwins[0].gradePtr(igrade);
       if (d==NULL) break;
       else BobTwins[1].addGrade(*d - 0.5);
       ++igrade;     
}
Alice->print();
for (int i=0; i<2; i++) {
BobTwins[i].print();
}
highlow_avg_grade(Alice, BobTwins, 2); 
highlow_top_grade(Alice, BobTwins, 2);
delete Alice;
delete [] BobTwins;
return 0; 
}
