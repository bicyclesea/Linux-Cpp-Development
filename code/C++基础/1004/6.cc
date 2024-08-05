#include <iostream>
using std::cout;
using std::endl;
/*
 * 将单例对象创建在堆区
 * 1. 构造函数私有
 * 2. 通过静态成员函数getInstance创建堆上的对象，返回Point*类型的指针
 * 3. 通过静态成员函数完成堆对象的回收
 * */
class Point
{
public:
    static Point *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Point(1, 2);
        }
        return _pInstance;
    }
    void init(int x, int y)
    {
        _ix = x;
        _iy = y;
    }
    static void destroy()
    {
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
        cout << "<<<delete heap" << endl;
    }
    void print()
    {
        cout << "(" << this->_ix
             << "," << this->_iy
             << ")" << endl;
    }
private:
    Point(int x, int y)
    : _ix(x)
    , _iy(y)
    {
        cout << "Point(int,int)" << endl;
    }
    ~Point()
    {
        cout << "~Point()" << endl;
    }
    //C++11之后可以将成员函数从类中删除
    Point(Point &rhs) = delete;
    Point &operator=(const Point &rhs) = delete;
private:
    int _ix;
    int _iy;
    //定义一个指针保存第一次创建的对象
    static Point *_pInstance;
};
Point *Point::_pInstance = nullptr;
void test1()
{
    //单例对象的使用规范
    Point::getInstance()->init(1, 2);
    Point::getInstance()->print();
    Point::getInstance()->init(10, 20);
    Point::getInstance()->print();
    Point::destroy();
}
int main()
{
    test1();
    return 0;
}

