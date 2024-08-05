#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class String 
{
public:
    String()
        : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }
    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
    String(const String &rhs)
    {
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    ~String()
    {
        if(_pstr){
            delete []_pstr;
        }
        cout << "~String()" << endl;
    }
    String &operator=(const String &rhs)
    {
        if(this != &rhs){
            if(_pstr){
                delete []_pstr;
            }
            if(rhs._pstr){
                _pstr = new char[strlen(rhs._pstr) + 1]();
                strcpy(_pstr, rhs._pstr);
            }else{
                _pstr = nullptr;
            }
        }
        cout << "String &operator=(const String &rhs)" << endl;
        return *this;
    }
    String &operator=(const char *pstr)
    {
        if(_pstr){
            delete []_pstr;
        }
        _pstr = new char[strlen(pstr) + 1]();
        strcpy(_pstr, pstr);
        cout << "String &operator=(const char *pstr)" << endl;
        return *this;
    }

    String &operator+=(const String &rhs)
    {
        cout << "调用了operator+=函数" << endl;
        char *tmp = new char[strlen(_pstr) + 1]();
        strcpy(tmp, _pstr);
        if(_pstr){
            delete []_pstr;
        }
        _pstr = new char[strlen(tmp) + strlen(rhs._pstr) + 1]();
        strcpy(_pstr, tmp);
        strcat(_pstr, rhs._pstr);
        if(tmp){
            delete []tmp;
        }
        return *this;
    }
    String &operator+=(const char *pstr)
    {
        cout << "String &operator+=(const char *)" << endl;
        char *tmp = new char[strlen(_pstr) + 1]();
        strcpy(tmp, _pstr);
        if(_pstr){
            delete []_pstr;
        }
        _pstr = new char[strlen(tmp) + strlen(pstr) + 1];
        strcpy(_pstr, tmp);
        strcat(_pstr, pstr);
        if(tmp){
            delete []tmp;
        }
        return *this;
    }

    char &operator[](std::size_t index)
    {
        if(index < size() - 1){
            return _pstr[index];
        }else{
            cout << "out of range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    const char &operator[](std::size_t index) const
    {
        return _pstr[index];
    }

    std::size_t size() const
    {
        return sizeof(_pstr);
    }
    const char* c_str() const
    {
        return _pstr;
    }
    void print() const
    {
        cout << _pstr << endl;
    }

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend ostream &operator<<(ostream &os, const String &s);
    friend istream &operator>>(istream &is, String &s);

    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char *, const String &);
private:
    char * _pstr;
};

String operator+(const String &lhs, const String &rhs)
{
    String s;
    s._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1]();
    strcpy(s._pstr, lhs._pstr);
    strcat(s._pstr, rhs._pstr);
    return s;
}
String operator+(const String &lhs, const char *rhs)
{
    String s;
    s._pstr = new char[strlen(lhs._pstr) + strlen(rhs) + 1]();
    strcpy(s._pstr, lhs._pstr);
    strcat(s._pstr, rhs);
    return s;
}
String operator+(const char *lhs, const String &rhs)
{
    String s;
    s._pstr = new char[strlen(lhs) + strlen(rhs._pstr) + 1]();
    strcpy(s._pstr, lhs);
    strcat(s._pstr, rhs._pstr);
    return s;
}

bool operator==(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) != 0;
}

bool operator<(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

ostream &operator<<(ostream &os, const String &s)
{
    os << s._pstr << endl;
    return os;
}

istream &operator>>(istream &is, String &s)
{
    is >> s._pstr;
    return is;
}

int main()
{
    String s1;
    String s2("Hello, World");
    /* s2.print(); */
    String s3 = s2;
    s3.print();
    cout << "----------------" << endl;
    s3 = s1;
    s3 = "nihao";
    s3.print();
    cout << "----------------" << endl;
    s3 += s2;
    s3.print();
    s3 += "back";
    s3.print();
    cout << s3[3] << endl;
    cout << s3[4] << endl;
    cout << s3[5] << endl;
    cout << "----------------" << endl;
    cout << (s3 < s2) << endl;
    cout << s3;
    /* cin >> s3; */
    /* cout << s3; */
    cout << "----------------" << endl;
    String s4 = s2 + s3;
    cout << s2 << s3;
    cout << s4;
    s4 = s2 + "你好";
    cout << s4;
    s4 = "你好" + s2;
    cout << s4;
    return 0;
}

