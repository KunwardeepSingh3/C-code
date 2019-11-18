#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

class Rational {
public:
   int get_num() const {
      return n;
   }
   int get_den() const {
      return d;
   }
   Rational (): n(1), d(1) {}
   Rational(int a, int b){
    int c = gcd(a,b);
         n = a/c;
         d = b/c;
   }
   Rational operator+(const Rational &r) const;
   Rational operator-(const Rational &r) const;

private:
   int n, d;
   static int gcd(int a, int b);
};
int Rational::gcd(int a, int b)
     {
       if (a < b)
         return gcd(b,a);
       int c = a % b;
       if (c == 0)
         return b;
       else if (c == 1)
return 1;
       return gcd(b,c);
     }

Rational Rational:: operator+(const Rational &r) const{
  int nsum = n+r.get_num();
  int dsum = d+r.get_num();
return Rational(nsum, dsum);
}
Rational Rational::operator-(const Rational &r) const {
  int ndiff = n-r.get_num();
  int ddiff = d-r.get_num();
  return Rational(ndiff, ddiff);
}
int main() {
       Rational r1(6,8), r2(2,4);
       cout << r1.get_num()  << "  " << r1.get_den()  << endl;
       cout << r2.get_num()  << "  " << r2.get_den()  << endl;
       Rational sum1 = r1 + r1;
       Rational sum2 = r1 + r2;
       Rational diff = r1 - r2;
       cout << sum1.get_num()  << "  " << sum1.get_den()  << endl;
       cout << sum2.get_num()  << "  " << sum2.get_den()  << endl;
       cout << diff.get_num()  << "  " << diff.get_den()  << endl;
return 0; }
