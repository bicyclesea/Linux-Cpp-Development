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
    //成员函数实现
    Point operator-(const Point &rhs)
    {
        return Point(X - rhs.X, Y - rhs.Y);
    }
private:
    int X, Y;
};
int main()
{
    Point pt1(3, 4);
    Point pt2(2, 1);
    Point pt3 = pt1 - pt2;
    pt3.print();
    return 0;
}

