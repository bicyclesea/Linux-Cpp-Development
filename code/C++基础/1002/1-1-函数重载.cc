#include <iostream>
using std::cout;
using std::endl;

int add(int x, int y)
{
    return x + y;
}
int add(int x, int y, int z)
{
    return x + y + z;
}
float add(float x, int y)
{
    return x + y;
}
float add(int x, float y)
{
    return x + y;
}
void test0()
{
    int a = 1, b = 2, c = 3;
    float d = 2.2;
    cout << add(a, b) << endl;
    cout << add(a, b, c) << endl;
    cout << add(d, a) << endl;
    cout << add(c, d) << endl;
}
int main()
{
    test0();
    return 0;
}

