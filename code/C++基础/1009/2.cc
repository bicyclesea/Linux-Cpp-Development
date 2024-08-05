#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
    class AutoRelease{
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Singleton(1, 2);
        }
        return _pInstance;
    }
    void init(int x, int y)
    {
        _ix = x;
        _iy = y;
    }
    void print()
    {
        cout << "(" << this->_ix
            << "," << this->_iy
            << ")" << endl;
    }
private:
    Singleton(int x, int y)
        : _ix(x)
          , _iy(y)
    {
        cout << "Singleton(int,int)" << endl;
    }
    Singleton(const Singleton &rhs) = delete;
    Singleton &operator=(const Singleton &rhs) = delete;
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
    static AutoRelease _ar;
};
Singleton* Singleton::_pInstance = nullptr;
//使用AutoRelease类的无参构造对_ar进行初始化
Singleton::AutoRelease Singleton::_ar;

void test1(){
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(10,80);
    Singleton::getInstance()->print();
}

int main()
{
    test1();
    return 0;
}

