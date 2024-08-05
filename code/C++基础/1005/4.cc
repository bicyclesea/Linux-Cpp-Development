#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Point
{
public:
    Point(int xx = 0, int yy = 0)
    : X(xx)
    , Y(yy)
    {
        cout << "Point构造函数被调用" << endl;
    }
    Point(const Point &rhs)
    : X(rhs.X)
    , Y(rhs.Y)
    {
        cout << "Point拷贝构造函数被调用" << endl;
    }
    Point &operator=(const Point &rhs)
    {
        if(this != &rhs){
            X = rhs.X;
            Y = rhs.Y;
            cout << "赋值运算符函数" << endl;
        }
        return *this;
    }
    void print()
    {
        cout << "X = " << X << ", Y = " << Y << endl;
    }
    ~Point()
    {
        cout << X << "," << Y << ": ";
        cout << "~Point()" << endl;
    }
private:
    int X, Y;
};
int main()
{
    vector<Point> vec;
    Point pt1(3, 4);
    Point pt2(4, 5);
    Point pt3(5, 6);
    cout << "-------------------" << endl;
    vec.push_back(pt1);
    vec.push_back(pt2);
    vec.push_back(pt3);
    cout << "-------------------" << endl;
    for(size_t i = 0; i < vec.size(); ++i){
        vec[i].print();
    }
    return 0;
}

