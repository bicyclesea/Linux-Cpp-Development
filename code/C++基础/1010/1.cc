#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    String(const char * pstr)
    {
        cout << "String(const char * pstr)" << endl;
        if(strlen(pstr) <= sizeof(_buffer._local) - 1){//15
            strcpy(_buffer._local, pstr);
            /* cout << _buffer._local << endl; */
            _buffer._pointer = nullptr;
            _size = strlen(_buffer._local);
            _capacity = sizeof(_buffer._local);//16
        }else{
            _buffer._pointer = new char[strlen(pstr) + 1]();
            strcpy(_buffer._pointer, pstr);
            _size = strlen(_buffer._pointer);
            _capacity = strlen(_buffer._pointer) + 1;
        }
    }
    ~String()
    {
        if(_buffer._pointer){
            delete []_buffer._pointer;
        }
        cout << "~String()" << endl;
    }
/*
    char & operator[](size_t idx)
    {
        cout << "char & operator[](size_t idx)" << endl;
        if(_size <= sizeof(_buffer._local) - 1){  //15
            cout << "1" << endl;
            if(idx <= sizeof(_buffer._local) - 2){//14
                cout << "2" << endl;
                cout << _buffer._local << endl;
                return _buffer._local[idx];
            }
        }
        else{
            if(idx < _size - 1){
                return _buffer._pointer[idx];
            }
        }
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
*/
    friend
        ostream & operator<<(ostream & os,const String & rhs);
private:
    union Buffer{
        char * _pointer = nullptr;
        char _local[16];
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

void test0(){
    String str1("hello");
    /* cout << str1[2] << endl; */
    /* String str2("hello,world!!!!!"); */
    //...
}

int main()
{
    test0();
    return 0;
}

