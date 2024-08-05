#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

//前向声明
class Point;
class Line{
public:
    //distance函数的定义需要在Point类定义之后实现
    float distance(const Point & lhs, const Point & rhs);
};

class Point{
public:
    Point(int x, int y)
        : _ix(x)
        , _iy(y)
    {}
    friend float Line::distance(const Point & lhs, const Point & rhs);
private:
    int _ix;
    int _iy;
};
/* 在Point类定义之后实现Line::distance */
float Line::distance(const Point & lhs, const Point & rhs)
{
    return sqrt((lhs._ix - rhs._ix) * (lhs._ix - rhs._ix) +
                (lhs._iy - rhs._iy) * (lhs._iy - rhs._iy));
}

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

