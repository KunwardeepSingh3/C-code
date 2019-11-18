#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;



double power(double x, int n){
    if (x==0) return 0;
       else if (n == 0)
       return 1.0;
          else if (n<0) 
          return power(1.0/x, -n);
             else if (n%2 == 0)
             return power(x, n/2)*power(x, n/2);
                else
                return x*power(x, n/2)*power(x, n/2);
}



int main (){
double a = 2;
for (int b=0; b<10; b++)
cout << power(a, b) << endl;
return 0;
}
