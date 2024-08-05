#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Singleton("Huawei", 5000);
        }
        return _pInstance;
    }
    void init(const char *brand, double price)
    {
        if(_brand){
            delete []_brand;
        }
        _brand = new char[strlen(brand) + 1]();
        strcpy(_brand, brand);
        _price = price;
    }
    void print()
    {
        cout << "brand: " << _brand << endl;
        cout << "price: " << _price << endl;
    }
private:
    Singleton(const char *brand, double price)
        : _brand(new char[strlen(brand) + 1]())
          , _price(price)
    {
        cout << "Singleton(const char *, double)" << endl;
        strcpy(_brand, brand);
    }
    Singleton(Singleton &rhs) = delete;
    Singleton &operator=(const Singleton &rhs) = delete;
    ~Singleton()
    {
        if(_brand){
            delete []_brand;
            _brand = nullptr;
        }
        cout << "~Singleton()" << endl;
    }
private:
    char *_brand; //电脑品牌
    double _price;//电脑价格
    //定义一个指针保存第一次创建的对象
    static Singleton *_pInstance;
private:
    friend class AutoRelease;
};
Singleton * Singleton::_pInstance = nullptr;

class AutoRelease{
public:
    AutoRelease(Singleton * p)
        : _p(p)
    { cout << "AutoRelease(Singleton*)" << endl; }

    ~AutoRelease()
    {
        cout << "~AutoRelease()" << endl;
        if(_p){
            delete _p;
            _p = nullptr;
        }
    }
private:
    Singleton * _p;
};

void test0()
{
    AutoRelease ar(Singleton::getInstance());
    Singleton::getInstance()->print();
}

int main()
{
    test0();
    return 0;
}

