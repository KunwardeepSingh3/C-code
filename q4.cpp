#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctype.h>
using namespace std;
bool word_match(string s1, string s2){
istringstream is1(s1);
is1 >> s1;
istringstream is2(s2);
is2 >> s2;
for (int i=0; i<s1.length(); i++)
s1 = toupper(s1[i]);
for (int i=0; i<s2.length(); i++)
s2 = toupper(s2[i]); 
return (s1==s2);
}

int main() {
  string s1, s2;
  bool b;
  s1 = "Alice";
  s2 = "AlIcE";
  b = word_match(s1, s2);
  if (b == true)
    cout << "true: [" << s1 << "] [" << s2 << "]" << endl;
  else
    cout << "false: [" << s1 << "] [" << s2 << "]" << endl;
return 0; 
}

