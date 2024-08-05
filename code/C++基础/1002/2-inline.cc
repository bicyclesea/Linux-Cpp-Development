#include <iostream>
using std::cout;
using std::endl;

#define MAX(X, Y) ((X)>(Y)?(X):(Y))
#define MULTIPLY(X, Y) ((X)*(Y))

//在普通函数的定义形式之前加上inline
//表示向编译器提出内联的建议
//如果编译器采用了内联
//就会在编译阶段进行替换
inline int multiply(int x, int y)
{
    return x * y;
}
void test0()
{
    int a = 2, b = 3, c = 4;
    //2 + 3 * 4
    cout << MULTIPLY(a + b, c) << endl;
    //相比于宏函数的缺点
    //调用普通函数会有开销
    //使用inline函数实际上不会有函数调用的开销
    cout << multiply(a + b, c) << endl;
}
int main()
{
    test0();
    return 0;
}


