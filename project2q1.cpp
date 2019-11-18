#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
                                        
class Message1 {                   // DECLARATIONS FOR CLASS Message1

public:
   Message1();
   Message1(string f);
   Message1(string f, string t);
   Message1(string f, string t, string s);
   Message1(string f, string t, string s, string txt);
   
   string from() const;
   string to() const;
   string subject() const;
   string text() const;
   string date() const;
   
   void setRecipient(string t);
   
   void setSubject(string s);
   void setText(string txt);
   void prependText(string t);
   void appendText(string t);
    
   void print() const;
   
private:
   string addDomain(string s);
   
   string _from;
   string _to;
   string _subject;
   string _text;
   int _date;
};
                 // NON INLINE METHODS AND FUNCTIONS FOR CLASS Message1
    
    string Message1::from() const {
       return _from;
    }
    string Message1::to() const {
       return _to;
    }
    string Message1::subject() const {
       return _subject;
    }
    string Message1::text() const {
       return _text;
    }
    string Message1::date() const {
       return string("n/a");
    }
    void Message1::print() const {
       cout << "From: " << _from << endl;
       cout << "To: " << _to << endl;
       cout << "Subject: " << _subject << endl;
       cout << "Date: " << date() << endl;
       cout << _text << endl;
       cout << endl;
    }
    void Message1::setSubject(string s) {
       _subject = s;
    }
    void Message1::setText(string txt) {
       _text = txt;
    }
  
    void Message1::setRecipient(string t) {
       _to = addDomain(t);
    }
    void Message1::prependText(string t){
	_text = t+" "+_text;
    }
    void Message1::appendText(string t){
	_text = _text+ " "+t;
    }
    string Message1::addDomain(string s) {
       const string _domain = "@qc.cuny.edu";
       istringstream iss(s);
       iss >> s;
       return s + _domain;
    }
    Message1::Message1() { 
       _date = 0; 
    }
    Message1::Message1(string f) {
       _from = addDomain(f); 
       _date = 0;
    }
    Message1::Message1(string f, string t) {
       _from = addDomain(f);
       _to = addDomain(t);
       _date = 0;
    }
    Message1::Message1(string f, string t, string s) {
       _subject = s;
       _from = addDomain(f);                                             
       _to = addDomain(t);
       _date = 0;
    }
    Message1::Message1(string f, string t, string s, string txt) {
       _text = txt;
       _subject = s;
       _from = addDomain(f);
       _to = addDomain(t);
       _date = 0;
    }
    ostream& operator<<(ostream& os, const Message1 &m){
       os << "From: " << m.from() << endl;
       os << "To: " << m.to() << endl;
       os << "Subject: " << m.subject() << endl;
       os << "Date: " << m.date() << endl;
       os << m.text() << endl;
       os << endl;
       return os;    
    }
	


class Vec_Message1 {                       //DECLARATION FOR CLASS Vec_Message1

public:
    Vec_Message1();
    Vec_Message1(int n);
    Vec_Message1(int n, const Message1 &a);

    Vec_Message1(const Vec_Message1 &orig);
    Vec_Message1& operator= (const Vec_Message1 &rhs);
    ~Vec_Message1();

    int capacity() const;
    int size() const;

    Message1 front() const;
    Message1 back() const;

    void clear();
    void pop_back();
    void push_back(const Message1 &a);

    Message1& at(int n);
    Message1& operator[] (int n);
    const Message1& operator[] (int n) const;
private:
    void allocate();
    void release();

    int _capacity;
    int _size;
    Message1*_vec;
};

                                     //NON INLINE METHODS AND FUNCTION FOR CLASS Vec_Message1 
int Vec_Message1:: capacity() const{
    return _capacity;
}

int Vec_Message1:: size() const{
    return _size;
}
void Vec_Message1:: clear() {
    _size = 0;
}

void Vec_Message1:: pop_back() {
    if (_size > 0) _size--;
}

void Vec_Message1::allocate() {
    if (_capacity <= 0) _vec = NULL;
    else _vec = new Message1[_capacity];
}

void Vec_Message1::release() {
    if (_vec != NULL){
       delete [] _vec;
       _vec = NULL;
    }
    else {} _vec = NULL;
}
Vec_Message1:: Vec_Message1() : _capacity(0), _size(0), _vec(0) {};

Vec_Message1::Vec_Message1(int n){
    if (n<=0) {
       _capacity = 0;
       _size = 0;
       _vec = NULL;
    }
    else {
       _capacity = n, _size = n;
       allocate();
    }
}

Vec_Message1::Vec_Message1(int n, const Message1 &a){
    if (n<=0) {
       _capacity = 0, _size = 0, _vec = NULL;
    }
    else {
       _capacity = n, _size = n;
       allocate();
       for (int i=0; i<_capacity; i++)
       _vec[i] = a;
    }
}

Vec_Message1::~Vec_Message1() {
    release();
}

Vec_Message1::Vec_Message1(const Vec_Message1 &orig) {
    _capacity = orig._size;
    _size = orig._size;
    allocate();
    for (int i=0; i<_size; i++)
    _vec[i] = orig._vec[i];
}

Vec_Message1& Vec_Message1::operator= (const Vec_Message1 &rhs) {
    if (this == &rhs) return *this;
    _capacity = rhs._size;
    _size = rhs._size;
    release();
    allocate();
    for (int i=0; i<_size; i++){
       _vec[i] = rhs._vec[i];
    }
    return *this;
}

Message1 Vec_Message1::front() const {
       if (_size > 0) return _vec[0];
       else {
         Message1 default_obj;
         return default_obj;
       }
     }
Message1 Vec_Message1::back() const {
       if (_size > 0) return _vec[_size-1];
       else {
         Message1 default_obj;
         return default_obj;
       }
}
void Vec_Message1::push_back(const Message1 &a) {
    if (_size < _capacity){
       _vec[_size] = a;
       _size++;
    }
    else if (_size == _capacity){
       if(_capacity == 0) _capacity = 1;
       else if (_capacity>0) _capacity *= 2;
       Message1 *oldvec = _vec;
       allocate();
       if (oldvec != NULL){
          for (int i=0; i<_size; i++)
          _vec[i] = oldvec[i];
          delete [] oldvec;
       }
       _vec[_size] = a;
       _size++;
    }
}

Message1& Vec_Message1::at(int n) {
    if ((n>=0)&&(n<_size)) return _vec[n];
    else {
       Message1 *pnull = NULL;
       return *pnull;
    }
}
Message1& Vec_Message1:: operator[] (int n) {
return at(n);
}

const Message1& Vec_Message1::operator[] (int n) const {
if ((n>=0)&&(n<_size)) return _vec[n];
    else {
       Message1 *pnull = NULL;
       return *pnull;
    }
}
void reverse (Vec_Message1 &v) {
    int n = v.size();
    if (n <= 1) return;
    if (n%2 == 0){
       for (int i=0; i<n/2; i++){
          Message1 tmp = v.at(i);
          v.at(i) = v.at(n-1-i);
          v.at(n-1-i) = tmp;
       }
    }
    else {
for (int i=0; i<(n-1)/2; i++){
          Message1 tmp = v.at(n-1-i);
           v.at(n-1-i) = v.at(i);
           v.at(i) = tmp;
       }
    }
}

void print(ostream &os, const Vec_Message1 &v) {
    cout << "elements of vector are: ";
    for(int i=0; i<v.size(); i++)
    os << v[i] << " ";
    os << endl;
}


int main() {
string _from, _to, _subject, _text;
int _date;
Message1 m("kunwar", "simran", "cs211", "Hello");
m.print();
cout << "This email is sent from: " << m.from() << endl;
cout << "this email is received by: " << m.to() <<endl;
m.setSubject("Project2");
m.setText("I did first question.");
m.print();
cout << endl;
m.prependText("Wow!");
m.appendText("yayy..");
m.print();
Message1 b(m);
b.print();
cout << endl;
Message1 x, y;
x = x = y;
x = y = x;
cout << x << endl;
cout << y << endl;
Vec_Message1 z;
z.push_back(x);
z.push_back(b);
z.push_back(m);
z.push_back(y);
for (int i = 0; i < z.size(); i++) {
        cout << z[i];
    }
    reverse(z);
    for (int i = 0; i < z.size(); i++) {
        cout << z[i];
    }
    cout << endl << "BREAK" << endl;
    Message1 c((Message1(m)));
    cout << c;
  
return 0;
} 
