
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;



double sqrt_Babylonian(double a){
double x[100];
int i;
    for (int i=1; i>0; i++){
        x[0] = 1;
        x[i] = (x[i-1] + a/x[i-1])/2;
           cout <<"value of i is: " << i << ",  value of x[i] is: " << x[i] << endl; 
        if (abs(x[i]-x[i-1])<=pow(10, -4))
    return x[i];	
}
return x[i]; 
}



int main (){
double a = 23650953;
double x[100];
cout <<  sqrt_Babylonian(a) << endl; 
return 0;
}
