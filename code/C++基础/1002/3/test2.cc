#include <iostream>
#include "space2.cc"
using std::cout;
using std::endl;
using MySpace::add;
namespace MySpace
{
extern int add(int x, int y);
extern double add(double x, int y);
extern double add(int x, double y);
extern int add(int x, int y, int z);
};//end of namespace MySpace
int main()
{
    int x = 3, y = 4, z = 5;
    double k = 4.5;
    cout << add(x) <<endl;
    cout << add(x, y) << endl;
    cout << add(k, x) << endl;
    cout << add(x, k) << endl;
    cout << add(x, y, z) << endl;
    return 0;
}

