#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    Base(int b)
        : _b(b)
    {}
    friend Base operator+(const Base &lhs, const Base &rhs);
    friend bool operator==(const Base &lhs, const int rhs);
private:
    int _b;
};
Base operator+(const Base &lhs, const Base &rhs)
{
    return Base(lhs._b + rhs._b);
}
bool operator==(const Base &lhs, const int rhs)
{
    return lhs._b == rhs;
}

int main()
{
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x + y == i + j) << endl;
    return 0;
}

