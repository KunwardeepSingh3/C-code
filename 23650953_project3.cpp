#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>
#include <chrono>
#include <map>
using namespace std;

class Name;
class Message;
class EmailAccount;
class BaseFolder;
class Drafts;

template<typename T> class Vec {
  public:
      Vec();
      Vec(int n);
      Vec(int n, const T &a);

      Vec(const Vec &orig);
      Vec& operator= (const Vec &rhs);
      ~Vec() { release(); }

      int capacity() const { return _capacity; }
      int size() const { return _size; }

      T front() const;
      T back() const;

      void clear() { _size = 0; }
      void pop_back();
      void push_back(const T &a);
      void erase(int n);

      T& at(int n);
      T& operator[] (int n) { return at(n); }
      const T& operator[] (int n) const;
  private:
      void allocate();
      void release();
      int _capacity;
      int _size;
      T * _vec;
};

class Name {
  public:
      Name();
      Name(string s);

      void set(string s);
      string name() const;
      string address() const;

  private:
      string _name;
      string _address;
};

class Message {
  public:
      Message(string f);
      Message(string f, string t);
      Message(string f, string t, string s);
      Message(string f, string t, string s, string txt);
      Message(const Message& orig);
      const Name& from() const;
      const Name& to() const;
      string subject() const;
      string text() const;

      string date() const;
      void send();

      void setRecipient(string t);
      void setSubject(string s);
      void setText(string txt);

      void prependText(string t);
      void appendText(string t);
      void print() const;
  private:
      void setDate();

      Name _from;
      Name _to;
      string _subject;
      string _text;
      time_t _date;
};

class EmailAccount {
  public:
      EmailAccount(string s);
      ~EmailAccount();

      const Name& owner() const;
      Drafts& drafts();
      BaseFolder& in();
      BaseFolder& out();

      void send(Message *m);
      void receive(Message *m);
      void insert(Message *m);

  private:
      Name _owner;
      Drafts *_drafts;
      BaseFolder *_in;
      BaseFolder *_out;

      EmailAccount(const EmailAccount& orig) {}
      EmailAccount& operator= (const EmailAccount& rhs) { return *this; }
};

class Drafts {
  public:
      Drafts(EmailAccount *ac);
      ~Drafts();

      void display() const;
      void send(int n);
      void erase(int n);

      Message* addDraft();
      Message* addDraft(Message *m);
      Message* getDraft(int n);
      Message* operator[](int n);

  private:
      int newKey();

      int _newKey;
      map<int, Message*> _drafts;
      EmailAccount *_ac;

      Drafts(const Drafts& orig) {}
      Drafts& operator= (const Drafts& rhs) { return *this; }
};

class BaseFolder {
  public:
      BaseFolder(EmailAccount *ac);

      int size() const;

      void display() const;
      void erase(int n);
      void forward(int n) const;
      void print(int n) const;
      void receive(const Message *m);
      void reply(int n) const;
      virtual ~BaseFolder();

  protected:
      virtual string type() const = 0;
      virtual const Name& tofrom(const Message *m) const = 0;

      Vec<const Message*> _msg;
      EmailAccount *_ac;

  private:
      BaseFolder(const BaseFolder& orig) {}
      BaseFolder& operator= (const BaseFolder& rhs) { return *this; }
};

class Inbox : public BaseFolder {
  public:
      Inbox(EmailAccount *ac);

  protected:
      virtual string type() const;
      virtual const Name& tofrom(const Message *m) const;
};

class Outbox : public BaseFolder {
  public:
      Outbox(EmailAccount *ac);

  protected:
      virtual string type() const;
      virtual const Name& tofrom(const Message *m) const;
};

class ISP {
  public:
      static void addAccount(EmailAccount *e) {
          _accounts[e->owner()] = e;
      }
      static void send(Message *m);

  private:
      ISP() {}
      static map<Name, EmailAccount*> _accounts;
};

    template<typename T>
       Vec<T>::Vec() : _capacity(0), _size(0), _vec(NULL) {}

    template<typename T>
       Vec<T>::Vec(int n) {
          if (n <= 0) {
             _size = 0, _capacity = 0;
             _vec = NULL;
          }
          else {
             _size = n, _capacity = n;
             allocate();
          }
       }

    template<typename T>
       Vec<T>::Vec(int n, const T &a) {
          if (n <= 0) {
             _size = 0, _capacity = 0;
             _vec = NULL;
        }
          else {
             _size = n, _capacity = n;
             allocate();
             for (int i = 0; i < _capacity; i++)
             _vec[i] = a;
          }
        }

    template<typename T>
    void Vec<T>::release() {
        if (_vec != NULL)
            delete [] _vec;
        _vec = NULL;
    }

template<typename T>
    void Vec<T>::allocate() {
        if (_capacity > 0)
            _vec = new T[_capacity];
        else
            _vec = NULL;
    }

template<typename T>
    Vec<T>::Vec(const Vec &orig) {
        _size = orig._size;
        _capacity = orig._size;
        allocate();
        for (int i = 0; i < _size; i++)
            _vec[i] = orig._vec[i];
    }

template<typename T>
    Vec<T>& Vec<T>::operator= (const Vec<T> &rhs) {
        if (this == &rhs)
            return *this;
        _size = rhs._size;
        _capacity = rhs._size;
        release();
        allocate();
        for (int i = 0; i < _size; i++)
            _vec[i] = rhs._vec[i];
        return *this;
    }

template<typename T>
    T Vec<T>::front() const {
        if (_size <= 0)
            return 0;
        else
            return _vec[0];
    }

template<typename T>
    T Vec<T>::back() const {
        if (_size <= 0)
            return 0;
        else
            return _vec[_size-1];
    }

template<typename T>
    void Vec<T>::pop_back() {
        if (_size > 0)
            _size--;
    }

template<typename T>
    void Vec<T>::push_back(const T &a) {
        if (_size < _capacity) {
            _vec[_size] = a;
            _size++;
        }
        else {
            if (_capacity == 0)
                _capacity = 1;
            else
                _capacity *= 2;
            T *oldvec = _vec;
            _vec = new T[_capacity];
            if (oldvec != NULL) {
                for (int i = 0; i < _size; i++)
                    _vec[i] = oldvec[i];
            }
            delete [] oldvec;
            _vec[_size] = a;
            _size++;
        }
    }

template<typename T>
    void Vec<T>::erase(int n) {
        if ((n >= 0) && (n < _size)) {
            for (int i = n; i < (_size - 1); i++)
                _vec[i] = _vec[i+1];
        }
        _size--;
    }

template<typename T>
    T& Vec<T>::at(int n) {
        if ((n >= 0) && (n < _size))
            return _vec[n];
        else {
            T *pnull = NULL;
            return *pnull;
        }
    }

template<typename T>
    const T& Vec<T>::operator[] (int n) const {
        if ((n >= 0) && (n < _size))
            return _vec[n];
        else {
            T *pnull = NULL;
            return *pnull;
        }
    }

    Name::Name() {}

    Name::Name(string s) { set(s); }

    void Name::set(string s) {
       const string _domain = "@qc.cuny.edu";
       istringstream iss(s);
       iss >> _name;
       if (_name == "")
       _address = "";
       else {
         _address = _name + _domain;
         for (int i = 0; i < _address.length(); i++)
         _address[i] = tolower(_address[i]);
       }
    }

    string Name::name() const { return _name; }

    string Name::address() const { return _address; }

    bool operator==(const Name& n1, const Name& n2) {
       return (n1.address() == n2.address());
    }

    bool operator<(const Name& n1, const Name& n2) {
       return (n1.address() < n2.address());
    }

    Message::Message(string f) {
       _from.set(f);
       _date = 0;
    }

    Message::Message(string f, string t) {
       _from.set(f);
       _to.set(t);
       _date = 0;
    }

    Message::Message(string f, string t, string s) {
       _subject = s;
       _from.set(f);
       _to.set(t);
       _date = 0;
    }

    Message::Message(string f, string t, string s, string txt) {
       _text = txt;
       _subject = s;
       _from.set(f);
       _to.set(t);
       _date = 0;
    }

    const Name& Message::from() const { return _from; }

    const Name& Message::to() const { return _to; }

    string Message::subject() const { return _subject; }

    string Message::text() const { return _text; }

    string Message::date() const {
       if (_date > 0)
          return std::ctime(&_date);
       else
          return "";
    }

    void Message::send() { setDate(); }

    void Message::setRecipient(string t) { _to.set(t); }

    void Message::setSubject(string s) { _subject = s; }

    void Message::setText(string txt) { _text = txt; }

    void Message::prependText(string t) {
       _text.insert(0, " ");
       _text.insert(0, t);
    }

    void Message::appendText(string t) {
       _text.insert(_text.size(), " ");
       _text.insert(_text.size(), t);
    }

    void Message::print() const {
       cout << "From: " << _from.name() << " <" << _from.address() << ">" << endl;
       cout << "To: " << _to.name() << " <" << _to.address() << ">" << endl;
       cout << "Subject: " << _subject << endl;
       cout << "Date: " << date() << endl;
       cout << _text << endl;
    }

    void Message::setDate() {
       auto t_now = std::chrono::system_clock::now();
       _date = std::chrono::system_clock::to_time_t(t_now);
    }

    EmailAccount::EmailAccount(string s) {
       _owner.set(s);
       _drafts = new Drafts(this);
       _in = new Inbox(this);
       _out = new Outbox(this);
       ISP::addAccount(this);
    }

    EmailAccount::~EmailAccount() {
       delete _drafts;
       delete _in;
       delete _out;
    }

    const Name& EmailAccount::owner() const { return _owner; }

    Drafts& EmailAccount::drafts() { return *_drafts; }

    BaseFolder& EmailAccount::in() { return *_in; }

    BaseFolder& EmailAccount::out() { return *_out; }

    void EmailAccount::send(Message *m) {
       _out->receive(m);
       ISP::send(m);
    }

    void EmailAccount::receive(Message *m) { _in->receive(m); }

    void EmailAccount::insert(Message *m) { _drafts->addDraft(m); }

    Drafts::Drafts(EmailAccount *ac) : _ac(ac) {
       _newKey = 0;
       _drafts[0] = NULL;
    }

    Drafts::~Drafts() {
       for (map<int, Message*>::iterator it = _drafts.begin(); it != _drafts.end(); ++it)
       delete it->second;
    }
 
    void Drafts::display() const {
       cout << _ac->owner().name() << " Drafts: " << endl;
       if (_drafts.size() <= 1) {
       cout << "no messages to display" << endl;
    }
    else {
        map<int, Message*>::const_iterator mcit;
        for (mcit = _drafts.begin(); mcit != _drafts.end(); ++mcit) {
            if (mcit->first == 0)
                continue;
            const Message *ptr = mcit->second;
            cout << mcit->first << endl;
            cout << ptr->to().name() << endl;
            cout << ptr->subject() << endl;
        }
    }
}

    void Drafts::send(int n) {
       Message *ptr = _drafts[n];
       if (ptr == NULL)
       cout << "Message not found" << endl;
       else if (ptr->to().address() == "") {
          cout << "You must specify a recipient" << endl;
          return;
       }
    else {
        cout << "sending" << endl;
        ptr->send();
        _drafts.erase(n);
        _ac->send(ptr);
    }
    }

    void Drafts::erase(int n) {
    delete _drafts[n];
    _drafts.erase(n);
   }

Message* Drafts::addDraft() {
    int key = newKey();
    Message *ptr = new Message(_ac->owner().name());
    _drafts[key] = ptr;
    return ptr;
}
Message* Drafts::addDraft(Message *m) {
    int key = newKey();
    _drafts[key] = m;
    return m;
}
Message* Drafts::getDraft(int n) { return _drafts[n]; }
Message* Drafts::operator[](int n) { return _drafts[n]; }

int Drafts::newKey() { return (++_newKey); }

BaseFolder::BaseFolder(EmailAccount *ac) : _ac(ac) { _msg.push_back(NULL); }

int BaseFolder::size() const { return _msg.size(); }

void BaseFolder::display() const {
    cout << _ac->owner().name() << " " << type() << endl;
    if (_msg.size() <= 1)
        cout << "no messages to display" << endl;
    else if (_msg.size() > 1) {
        for (int i = 1; i < _msg.size(); i++) {
            const Name &tmp = tofrom(_msg[i]);
            cout << i << endl;
            cout << tmp.name();
            cout << _msg[i]->subject();
        }
    }
}
void BaseFolder::erase(int n) {
    if ((n >= 1) && (n < _msg.size())) {
        delete _msg[n];
        _msg.erase(n);
    }
}
void BaseFolder::forward(int n) const {
    if ((n >= 1) && (n < _msg.size())) {
        const Message *m = _msg[n];
        string fwd_subject = "Fwd: " + m->subject();
        Message *ptr = new Message(_ac->owner().name(), "", fwd_subject, m->text());
        _ac->insert(ptr);
    }
}
void BaseFolder::print(int n) const {
    if ((n >= 1) && (n < _msg.size()))
        print(n);
}
void BaseFolder::receive(const Message *m) { _msg.push_back(m); }
void BaseFolder::reply(int n) const {
    if ((n >= 1) && (n < _msg.size())) {
        const Message *m = _msg[n];
        string subject = "Re: " + m->subject();
        const Name& tmp = tofrom(m);
        Message *ptr = new Message(_ac->owner().name(), tmp.name(), subject, m->text());
        _ac->insert(ptr);
    }
}

BaseFolder::~BaseFolder() {
    for (int i = 0; i < _msg.size(); i++)
        delete _msg[i];
}

Inbox::Inbox(EmailAccount *ac) : BaseFolder(ac) {}

string Inbox::type() const { return "Inbox:"; }
const Name& Inbox::tofrom(const Message *m) const { return m->from(); }

Outbox::Outbox(EmailAccount *ac) : BaseFolder(ac) {}

string Outbox::type() const { return "Outbox:"; }
const Name& Outbox::tofrom(const Message *m) const { return m->to(); }

map<Name, EmailAccount*> ISP::_accounts;

void ISP::send(Message *m) {
    EmailAccount *ac = _accounts[m->to()];
    if (ac == NULL) {
        cout << "Delivery failed, to recipient: " << m->to().name() << endl;
        return;
    }
    else {
        Message *clone = new Message(*m);
        ac->receive(clone);
        return;
    }
}
         
    Message::Message(const Message &orig) {
    _subject = orig._subject;
    _text = orig._text;
    _date = orig._date;
    _from = orig._from;
    _to = orig._to;
    }


int main() {

    EmailAccount aa("kunwar");
    EmailAccount bb("alex");

    Drafts d(&aa);
    d.display();
    Message *mm = d.addDraft();
    mm->setRecipient("alex");
    mm->setSubject("CS211");
    mm->setText("Hey! hope we do good in project");
    cout << endl;
    d.display();
    d.send(1);
    cout << endl;
    Inbox ii(&bb);
    ii.display(); 
    cout << endl;
    Outbox out(&aa);
    out.display();

    return 0; 
}










