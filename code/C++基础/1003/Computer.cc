#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char *brand, double price)
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        strcpy(_brand, brand);
    }
    void setBrand(const char *brand)
    {
        strcpy(_brand, brand);
    }
    void setPrice(float price)
    {
        _price = price;
    }
    void print()
    {
        cout << _brand << endl;
        cout << _price << endl;
    }
    ~Computer()
    {
        if(_brand){
            cout << _brand << ": ";
            delete []_brand;
            _brand = nullptr;//设为空指针，安全回收
        }
        cout << "~Computer()" << endl;
    }
private:
    char *_brand;
    double _price;
};

Computer pc1("1:ASUS", 5000);
void test1()
{
    static Computer pc2("2:XiaoMi", 4500);
    Computer pc3("3:Huawei", 6000);

    int *p = new int(1);
    delete p;
    p = nullptr;

    Computer *p2 = new Computer("4:apple", 20000);
    delete p2;
    p2 = nullptr;
}

int main()
{
    test1();
    return 0;
}

