#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
    static Computer * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Computer("xiaomi",5000);
        }
        return _pInstance;
    }

    void init(const char * brand,double price){
        if(_brand){
            delete [] _brand;
        }
        _brand = new char[strlen(brand) +1]();
        strcpy(_brand,brand);
        _price = price;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
        cout << "<<<delete heap" << endl;
    }

    void print(){
        cout << "brand:" << _brand << endl;
        cout << "price:" << _price << endl;
    }
private:
    Computer(const char * brand, double price)
        : _brand(new char[strlen(brand) + 1]())
          , _price(price)
    {
        cout << "Computer(const char *,double)" << endl;
        strcpy(_brand, brand);
    }

    Computer(const Computer & rhs) = delete;
    Computer & operator=(const Computer & rhs) = delete;

    ~Computer(){
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
        cout << "~Computer()" << endl;
    }
private:
    char * _brand;
    double _price;
    static Computer * _pInstance;
};
Computer * Computer::_pInstance = nullptr;

void test1(){
    Computer::getInstance()->init("Apple", 15000);
    Computer::getInstance()->print();
    Computer::destroy();
}

int main()
{
    test1();
    return 0;
}


