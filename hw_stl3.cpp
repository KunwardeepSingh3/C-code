#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;

bool comp1(const string &s1, const string &s2) {
    return (s1 < s2);
}

bool comp2(const string &s1, const string &s2) {
    return (s1 > s2);
}

int main(){
vector<string>v;
 v.push_back("a");
 v.push_back("cde");
 v.push_back("ab");

sort(v.begin(), v.end(), comp1);

vector<string>::iterator v_it;
 for(v_it = v.begin(); v_it != v.end(); ++v_it)
    cout<< *v_it <<endl;

cout << endl;

vector<string>::reverse_iterator v_rit;
for (v_rit = v.rbegin(); v_rit != v.rend(); ++v_rit)
  cout << *v_rit << endl;

cout << endl;

v.push_back("kunwar");
v.push_back("deep");
v.push_back("hello");

sort(v.begin(), v.end(), comp2);

vector<string>::const_iterator v_cit;
   for (v_cit = v.cbegin(); v_cit != v.cend(); ++v_cit)
     cout << *v_cit << endl;

cout << endl;

vector<string>::const_reverse_iterator v_crit;
   for (v_crit = v.crbegin(); v_crit != v.crend(); ++v_crit)
     cout << *v_crit << endl;

return 0;
}
