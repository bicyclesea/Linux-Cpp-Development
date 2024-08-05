#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class String
{
public:
	String()
        : _pstr(nullptr)
    {}
	String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
	String(const String &rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }
	String &operator=(const String &rhs)
    {
        if(this != &rhs){
            if(_pstr){
                delete []_pstr;
            }
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
            cout << "赋值运算符函数" << endl;
        }
        return *this;
    }
	~String()
    {
        if(_pstr){
            delete []_pstr;
        }
        cout << "~String()" << endl;
    }
	void print()
    {
        cout << _pstr << endl;
    }
    size_t length() const
    {
        return strlen(_pstr);
    }
    const char * c_str() const
    {
        return _pstr;
    }
private:
	char * _pstr;
};

int main()
{
	/* String str1; */
	/* str1.print(); */

	String str2 = "Hello,world";
	String str3("Hello, String");
	
	/* str2.print(); */		
	/* str3.print(); */	
	
	String str4 = str3;
	/* str4.print(); */
	
	str4 = str2;
	str4.print();

    printf("%s\n", str4.c_str());
	
	return 0;
}


