#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class Point
{
public:
    Point(int x, int y)
        : _ix(x)
        , _iy(y)
    {}
    //友元类的声明
    friend class Line;
private:
    int _ix;
    int _iy;
};
class Line
{
public:
    float distance(const Point &lhs, const Point &rhs)
    {
        return sqrt(pow(lhs._ix - rhs._ix, 2) +
                    pow(lhs._iy - rhs._iy, 2));
    }
    void setX(Point &rhs, int x)
    {
        rhs._ix = x;
    }
};
void test0()
{
    Point pt(0, 0);
    Point pt2(5, 12);
    Line l1;
    cout << l1.distance(pt, pt2) << endl;
}

int main()
{
    test0();
    return 0;
}

