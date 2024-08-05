#include <iostream>
#include "space.cc"
using std::cout;
using std::endl;

int main()
{
    int x = 3, y = 4;
    MySpace::swap(x, y);
    cout << x << " " << y << endl;
    return 0;
}

