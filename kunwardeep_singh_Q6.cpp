#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;



bool divisible_9(int n, int &s){
    s=0;
    while (n>0){ 
       s += n%10;
          n = n/10;
    }
    cout << "sum is: " << s << endl;
    if (s == 9) return true;
       else if (s < 9) return false;
          else if (s > 9)
    n = s;  
return divisible_9(n, s); 
} 



int main (){
int n=23650953;
int sum;
cout << divisible_9(n,sum) << endl;
return 0;
}
   
