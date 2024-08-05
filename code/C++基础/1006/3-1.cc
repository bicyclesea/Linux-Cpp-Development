#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
    Point(int xx = 0, int yy = 0)
    : X(xx)
    , Y(yy)
    {}
    void print()
    {
        cout << "X = " << X
             << ", Y = " << Y << endl;
    }
    /* 重载-运算符 */
    friend Point operator-(const Point &lhs, const Point &rhs);
private:
    int X, Y;
};
//友元函数进行重载
Point operator-(const Point &lhs, const Point &rhs)
{
    return Point(lhs.X - rhs.X,
                 lhs.Y - rhs.Y);
}
int main()
{
    Point pt1(3, 4);
    Point pt2(2, 1);
    Point pt3 = pt1 - pt2;
    pt3.print();
    return 0;
}

