#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
vector<string>v;
 v.push_back("ab");
 v.push_back("cde");
 v.push_back("kkkkkk");
 v.push_back("ab");
 v.push_back("hello");
 v.push_back("hi");
 
set<string> s;
vector<string> tmp;
vector<string>::const_iterator cit;
for (cit = v.begin(); cit !=v.end(); ++cit) {
	 s.insert(*cit);
	 tmp.push_back(*cit);
  if (s.size() != tmp.size())
       break;
}	 

if (s.size() != tmp.size()) {
   cout << "there are duplicates" << endl; 
   } 
   else { 
      cout << "no duplicates" << endl; 
   }

cout << endl;
if(s.size() !=tmp.size()){
	cout<< tmp.back() <<" "<< tmp.size()-1<<endl;
}
 else{
 	cout<< "no duplicates"<<endl;
 }
   cout << endl;
set<string>::iterator s_it;
 for(s_it = s.begin(); s_it != s.end(); ++s_it)
    cout<< *s_it <<endl;
 
 return 0;
}
