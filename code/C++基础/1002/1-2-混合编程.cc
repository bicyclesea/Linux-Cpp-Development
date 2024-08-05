#include <iostream>

extern "C"
{
    float add(float x, int y)
    {
        return x + y;
    }
    /* conflicting types for 'add' */
    float add(int x, float y)
    {
        return x + y;
    }
}
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

