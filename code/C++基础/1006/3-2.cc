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
    int getX() const { return X; };
    int getY() const { return Y; };
    void print()
    {
        cout << "X = " << X
             << ", Y = " << Y << endl;
    }
private:
    int X, Y;
};
//普通函数进行重载
Point operator-(const Point &lhs, const Point &rhs)
{
    return Point(lhs.getX() - rhs.getX(),
                 lhs.getY() - rhs.getY());
}
int main()
{
    Point pt1(3, 4);
    Point pt2(2, 1);
    Point pt3 = pt1 - pt2;
    pt3.print();
    return 0;
}

