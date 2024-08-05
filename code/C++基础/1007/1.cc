#include <iostream>
using std::cout;
using std::endl;

class Stack {
public:
    Stack()
    : _top(-1)
    {}
    bool empty();   //判断栈是否为空
    bool full();    //判断栈是否已满
    void push(int); //元素入栈
    void pop();     //元素出栈
    int  top();     //获取栈顶元素
private:
    int arr[5];
    int _top;
};

bool Stack::empty()
{
    return _top == -1;
}
bool Stack::full()
{
    return _top == sizeof(arr) / sizeof(int) - 1;
}
void Stack::push(int x)
{
    arr[++_top] = x;
}
void Stack::pop()
{
    --_top;
}
int Stack::top()
{
    return arr[_top];
}

void test0()
{
    Stack stk;
    int i = 1;
    while(!stk.full()){
        stk.push(i++);
    }
    if(stk.full()){
        cout << "Stack is full now." << endl;
    }
    while(!stk.empty()){
        cout << stk.top() << endl;
        stk.pop();
    }
    if(stk.empty()){
        cout << "Stack is empty now." << endl;
    }
}

int main()
{
    test0();
    return 0;
}

