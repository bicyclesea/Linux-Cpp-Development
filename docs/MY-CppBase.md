# C++基础

## 1001 C++基础篇之类和对象01

### 1. 什么是命名空间？其作用是什么？匿名命名空间有什么特点？

【答】

**命名空间**

所谓命名空间，就是一个可以由用户自己定义的作用域，在不同的作用域中可以定义相同名字的变量，互不干扰，系统能够区分它们。

命名空间又称为名字空间，是程序员命名的内存区域，程序员根据需要指定一些有名字的空间域，把一些全局实体分别存放到各个命名空间中，从而与其他全局实体分隔开。通俗的说，每个名字空间都是一个名字空间域，存放在名字空间域中的全局实体只在本空间域内有效。名字空间对全局实体加以域的限制，从而合理的解决命名冲突。

C++中定义命名空间的基本格式如下：

```c++
namespace bs
{
    int val1 = 0;
    char val2;
}// end of namespace bs
```

在声明一个命名空间时，大括号内不仅可以存放变量，还可以存放以下类型：

变量、常量、函数、结构体、引用、类、对象、模板、命名空间等，它们都称为实体。

**作用**

命名空间，能避免命名冲突。

（1）避免命名冲突：命名空间提供了一种将全局作用域划分成更小的作用域的机制，用于避免不同的代码中可能发生的命名冲突问题；

（2）组织代码：将相关的实体放到同一个命名空间；

（3）版本控制：不同版本的代码放到不同的命名空间中。

总之，需要用到代码分隔的情况就可以考虑使用命名空间。

还有一个隐藏的好处：声明主权。

**匿名命名空间的特点**

（1）匿名命名空间，简称匿名空间，是不定义名字的命名空间；

（2）匿名命名空间中的实体，只在本文件中起作用；

```c++
/*匿名命名空间的定义方式*/
namespace{
    //...
}//end of anonymous namespace
```

（3）使用匿名命名空间中实体时，可以直接使用，也可以加上作用域限定符（没有空间名）；

```c++
namespace {
    int val = 10;
    void func(){
        cout << "func()" << endl;
    }
}//end of anonymous namespace

//以下用法均ok
void test0()
{
    cout << val << endl;
    cout << ::val << endl;
    func();
    ::func();
}
```

（4）如果匿名空间中定义了和全局位置中同名的实体，会有冲突；如果使用::作用域限定符，也无法访问到匿名空间中重名的实体，只能访问到全局的实体。

```c++
int num = 10;

void print(){
    cout << "print()" << endl;
}

//要注意避免匿名空间中定义与全局位置同名的实体
namespace
{
    int num = 100;
    
    void print(){
        cout << "N print()" << endl;
    }
}

void test0(){
    //cout << num << endl; //error
    //print(); //error
    //
    //只能访问到全局位置定义的实体
    cout << ::num << endl;
    ::print();
}
```

### 2. `const`关键字与宏定义的区别是什么？（面试常考）、

【答】（1）**发生的时机不同**：C语言中的宏定义发生时机在预处理时，做字符串的替换；const常量是在编译时（const常量本质还是一个变量，只是用const关键字限定之后，赋予只读属性，使用时依然是以变量的形式去使用）

（2）**类型和安全检查不同**：宏定义没有类型，不做任何类型检查；const常量有具体的类型，在编译期会执行类型检查。

在使用中，应尽量以const替换宏定义，可以减小犯错误的概率。

### 3. 什么是**常量指针**和**指向常量的指针**？什么是**数组指针**和**指针数组**？什么是**函数指针**和**指针函数**？请举例说明。

**常量指针与指向常量的指针**

| int * const p = &x;                        | 常量指针                     | 不能改变这个指针的指向，但是可以通过指针改变其指向的值 |
| ------------------------------------------ | ---------------------------- | ------------------------------------------------------ |
| const int * p = &x; 或 int const * p = &x; | 指向常量的指针（或指针常量） | 不能通过指针改变其指向的值，但是可以改变这个指针的指向 |

常量指针：

```c++
void test2()
{
    int num1 = 100;
    int num2 = 200;
    //常量指针（const pointer），从右向左读
    int *const p = &num1;
    *p = 300;//允许通过指针修改其指向的值
    /* p = &num2;//error 不允许指针修改指向 */
    cout << num1 << endl;
}
```

**总结：const在*右边，即为常量指针，不能改变这个指针的指向，但是可以通过指针改变其指向的值。**

指向常量的指针：

```c++
int number1 = 10;
int number2 = 20;

const int *p1 = &number1;//指向常量的指针
*p1 = 100;//error 通过p1指针无法修改其所指内容的值
p1 = &number2;//ok 可以改变p1指针的指向
```

代码中p1称为指向常量的指针（pointer to const），尽管number1本身并不是一个int常量，但定义指针p1的方式决定了无法通过p1修改其指向的值。但值得注意的是，修改p1的指向是允许的。

补充：如果有一个const常量，那么普通的指针也无法指向这个常量，只有指向常量的指针才可以。

```c++
const int x = 20;
int *p = &x; //error
const int *cp = &x; //ok
```

指向常量的指针还有第二种写法，各种特点同上，一般较少采用。

```c++
int const *p2 = &number1; //指向常量的指针 的第二种写法
```

```c++
void test1()
{
    int num1 = 100;
    int num2 = 200;
    
    //指向常量的指针
    const int *p1 = &num1;
    cout << *p1 << endl;
    //*p1 = 400;//error，不允许通过指针修改其指向的值
    p1 = &num2;//ok，允许修改指向
    cout << *p1 << endl;
    
    num1 = 1000;
    
    const int num = 8;
    /* int *p = &num;//error */
    const int *p = &num;
    
    //指向常量的指针
    int const *p2 = &num2;
    /* *p2 = 800; */
    p2 = &num1;
}
```

**总结：const在*左边，即为指向常量的指针，不能通过指针改变其指向的值，但是可以改变这个指针的指向。**



**数组指针与指针数组**

数组指针：

```c++
//数组指针
//指向数组的指针
void test3()
{
    int arr[5] = {1, 2, 3, 4, 5};
    //首元素的地址
    cout << arr << endl;
    //数组的首地址
    cout << &arr << endl;
    
    cout << endl;
    cout << arr + 1 << endl;
    cout << &arr + 1 << endl;
    
    //定义数组指针要确定指向的数组的元素类型和个数
    int (*p)[5] = &arr;
    for(int i = 0; i < 5; ++i){
        cout << (*p)[i] << endl;
    }
}
```

指针数组：

```c++
//指针数组（比较重要）
//存放元素为指针的数组
void test4()
{
    int a = 1, b = 2, c = 3;
    int *p1 = &a;
    int *p2 = &b;
    int *p3 = &c;
    int *arr[3] = {p1, p2, p3};
    
    for(int i = 0; i < 3; ++i){
        cout << *arr[i] << endl;
    }
}
```

**函数指针与指针函数**

函数指针：

```c++
//函数指针（重要）
//指向函数的指针
void func(int a, int b)
{
    cout << "func():" << a << endl;
}

void test5()
{
    //定义函数指针的时候要确定
    //这个指针指向的函数的返回类型和参数
    void (*p)(int, int) = func;
    p(3, 4);
    
    //完整的写法
    void (*p2)(int, int) = &func;
    (*p2)(5, 9);
}
```

指针函数：

```c++
//指针函数
//返回值为指针的函数
//要注意返回的指针，其指向的值生命周期应该比函数更长
int gNum = 10;
int *func2()
{
    return &gNum;
}

void test6()
{
    cout << func2() << endl;
    cout << &gNum << endl;
    cout << *func2() << endl;
}
```

### 4. `new/delete`与`malloc/free`的区别是什么？（面试常考）

【答】

（1）malloc/free是库函数；new/delete是表达式，后两者使用时不是函数的写法；

（2）new表达式的返回值是相应类型的指针，malloc返回值是void*；

（3）malloc申请的空间不会进行初始化，获取到的空间是有脏数据的，但new表达式申请空间时可以直接初始化；

（4）malloc的参数是字节数，new表达式不需要传递字节数，会根据相应类型自动获取空间大小。

### 5. 若执行下面的程序时，从键盘上输入5，则输出是（）

```c++
int main(int argc, char **argv)
{
    int x;
    cin >> x;
    if(x++ > 5){
        cout << x << endl;
    }
    else{
        cout << x-- << endl;
    }
    return 0;
}
```

【答】6（正确）

### 6. 写出下面程序的结果。

```c++
int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int *ptr = (int *)(&a + 1);
    printf("%d, %d", *(a + 1), *(ptr - 1));
}
```

【答】2, 1（错误）

正解：2, 5

### 7. 在自定义命名空间MySpace中定义swap函数，能够实现两个int数据的交换，并跨模块调用swap函数，验证其功能。

【答】space.cc

```c++
namespace MySpace
{
void swap(int &x, int &y)
{
    int tmp = y;
    y = x; x = tmp;
}
};//end of namespace MySpace
```

test1.cc

```c++
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
```

test2.cc

```c++
#include <iostream>
#include "space.cc"
using std::cout;
using std::endl;

namespace MySpace
{
extern void swap(int &x, int &y);
};//end of namespace MySpace

int main()
{
    int x = 3, y = 4;
    MySpace::swap(x, y);
    cout << x << " " << y << endl;
    return 0;
}
```

疑问：在test2.cc中，也需要使用#include "space.cc"？

### 总结

第6题：涉及到&运算符和整型数组，所以未得出结果。

第7题：不确定test2.cc的编写是否正确。

## 1002 C++基础篇之类和对象02

### 1. 什么是函数重载？其实现原理是什么？如何进行`C`与`C++`的混合编程？

【答】

**函数重载**

C++允许多个函数拥有相同的名字，只要它们的参数列表不同就可以，这就是函数重载。借助重载，一个函数名可以有多种用途。

在同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。重载函数通常用来命名一组功能相似的函数，这样做减少了函数名的数量，对于程序的可读性有很大的好处。注意：C语言中不支持函数重载，C++才支持函数重载。

```c++
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
```

实现函数重载的条件：

**函数参数的数量、类型、顺序任一不同则可以构成重载。**

只有返回类型不同，参数完全相同，是不能构成重载的。

**实现原理**

实现原理：名字改编——当函数名称相同时，会根据参数的类型、顺序、个数进行改编。

- g++ -c Overload.cc
- nm Overload.o

查看目标文件，可以发现原本的函数名都被改编成与参数相关的函数名。

编译器的名字改编机制将函数的名字改编成了与参数信息相关的名字。

而C语言没有名字改编机制。

C++的函数重载提供了一个便利，以前C语言要想实现各种不同类型参数的计算需要定义多个不同名字的函数，在调用函数时要注意参数的信息和函数名匹配。

C++有了函数重载，想要对不同类型的参数进行计算时，就可以使用同一个函数名字（代码层面的同名，编译器会处理成不同的函数名）。

缺点在于，C++编译器进行编译时比C的编译器多了一个步骤，效率有所降低。

**混合编程**

extern "C"

在C/C++混合编程的场景下，可以在C++代码中对部分内容按照C的方式编译。

```c++
extern "C" void func()//用extern"C"修饰单个函数
{
    
}
//如果是多个函数都希望用C的方式编译
//或是需要使用C语言的库文件
//都可以放到如下{}中
extern "C"
{
    //......
}
```

```c++
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
```

### 2. 什么是`inline`函数？`inline`与带参数的宏定义之间的区别是什么？

【答】

**inline函数**

在C++中，内联（inline）函数，用来减少程序的执行时间。内联函数作为编译器优化手段的一种技术，在降低运行时间上非常有用。

内联函数是C++的增强特性之一，用来降低程序的运行时间。当内联函数收到编译器的指示时，即可发生内联：编译器将使用函数的定义体来替代函数调用语句，**这种替代行为发生在编译阶段而非程序运行阶段。**

定义函数时，在函数的最前面以关键字“inline”声明函数，该函数即可称为内联函数（内联声明函数）。

```c++
inline int max(int x, int y)
{
    return x > y ? x : y;
}
```

inline.cc

```c++
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
```

**区别**

（1）宏函数：只是进行字符串的替换，并没有函数的开销，对于比较短小的代码适合使用；但没有类型检查，存在安全隐患，而且比较容易写错。

（2）inline函数：如果使用普通函数的方式又会增加开销，所以一些时候可以采用内联函数（结合了宏函数和普通函数的优点）。inline函数本质也是字符串替换（编译时），所以不会增加开销，但是有类型检查，比较安全。

### 3. 在自定义命名空间MySpace中定义add函数，能够实现多个数据的加法（两个int、一个double一个int、一个int一个double、三个int），并跨模块调用add函数，使用using声明机制验证其功能。还可以适当给函数参数赋默认值，进行缺省调用的练习。

【答】代码

（1）space.cc

```c++
namespace MySpace
{
int add(int x, int y)
{
    return x + y;
}
double add(double x, int y)
{
    return x + y;
}
double add(int x, double y)
{
    return x + y;
}
int add(int x, int y, int z)
{
    return x + y + z;
}
};//end of namespace MySpace
```

test1.cc

```c++
#include <iostream>
#include "space.cc"
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
    cout << add(x, y) << endl;
    cout << add(k, x) << endl;
    cout << add(x, k) << endl;
    cout << add(x, y, z) << endl;
    return 0;
}
```

（2）Practice-缺省调用

space.cc

```c++
namespace MySpace
{
int add(int x, int y = 3)
{
    return x + y;
}
double add(double x, int y)
{
    return x + y;
}
double add(int x, double y)
{
    return x + y;
}
int add(int x, int y, int z)
{
    return x + y + z;
}
};//end of namespace MySpace
```

test1.cc

```c++
#include <iostream>
#include "space.cc"
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
```

### 总结

- 考虑自定义命名空间MySpace跨模块调用的问题。

## 1003 C++基础篇之类和对象03

### 1. 定义析构函数时，应该注意（ ）。（单选题）

A.其名与类名完全相同

B.返回类型是void类型

C.无形参，也不可重载

D.函数体中必须有delete语句

【答】C

### 2. 在（ ）情况下适宜采用`inline`定义内联函数。（多选题）

A.函数体含有循环语句

B.函数体含有递归语句

C.函数代码少、频繁调用

D.函数代码多、不常调用

E.需要加快程序执行速度

【答】CE

### 3. C++内存布局是怎样的？可以具体阐述一下么？

【答】64位系统，理论空间达到16EB（2^64），但是受硬件限制，并不会达到这么多；

以32位系统为例，一个进程在执行时，能够访问的空间是**虚拟地址空间**。理论上为2^32，即4G，有1G左右的空间是内核态，剩下的3G左右的空间是用户态。从高地址到低地址可以分为五个区域：

- 栈区：操作系统控制，由高地址向低地址生长，编译器做了优化，显示地址时栈区和其他区域保持一致的方向。
- 堆区：程序员分配，由低地址向高地址生长，堆区与栈区没有明确的界限。
- 全局/静态区：读写段（数据段），存放全局变量、静态变量。
- 文字常量区：只读段，存放程序中直接使用的常量，如const char *p = "hello"; hello这个内容就存在文字常量区。
- 程序代码区：只读段，存放函数体的二进制代码。

### 4. 一个空类占据的空间有多大？会自动创建哪些函数呢？

【答】空类对象所占空间为1个字节，这仅仅是编译器的一种占位机制。

函数：构造函数、析构函数、拷贝构造函数、赋值运算符函数。

### 5. 什么是拷贝构造函数，其形态是什么，参数可以修改吗？

【答】

**拷贝构造函数**

对于内置类型而言，使用一个变量初始化另一个变量是很常见的操作

```c++
int x = 1;
int y = x;
```

那么对于自定义类型，我们也希望能有这样的效果，如

```c++
Point pt1(1, 2);
Point pt2 = pt1;
pt2.print();
```

发现这种操作也是可以通过的。执行Point pt2 = pt1;语句时，pt1对象已经存在，而pt2对象还不存在，所以也是这句创建了pt2对象，既然涉及到对象的创建，就必然需要调用构造函数，而这里会调用的就是拷贝构造函数（复制构造函数）。

**形态**

拷贝构造函数的形式是固定的：**类名（const 类名 &）**

1. 该函数是一个构造函数——构造函数也是构造！
2. 该函数用一个已经存在的同类型的对象，来初始化新对象，即对对象本身进行复制

没有显式定义拷贝构造函数，`Point pt2 = pt1;`这条复制语句依然可以通过，说明编译器自动提供了默认的拷贝构造函数。其形式是：

```c++
Point(const Point &rhs)
: _ix(rhs._ix)
, _iy(rhs._iy)
{}
```

拷贝构造函数看起来非常简单，接下来尝试对Computer类的对象进行同样的复制操作。发现同样可以编译通过，但运行报错，原因如下。

```c++
Computer pc("Acer", 4500);
Computer pc2 = pc;//调用拷贝构造函数
```

如果是默认的拷贝构造函数，pc2会对pc的_brand进行**浅拷贝**，指向同一片内存；pc2被销毁时，会调用析构函数，将这片堆空间进行回收；pc再销毁时，析构函数中又会试图回收这片空间，出现double free问题。

所以，如果拷贝构造函数需要显式写出时（该类有指针成员申请堆空间），在自定义的拷贝构造函数中要换成**深拷贝**的方式，先申请空间，再复制内容。

```c++
Computer::Computer(const Computer &rhs)
: _brand(new char[strlen(rhs._brand) + 1]())
, _price(rhs._price)
{
    strcpy(_brand, rhs._brand);
}
```

**参数**

不可以修改。

**1、拷贝构造函数不可以去掉引用符号。**

——类名（const 类名）形式，首先编译器不允许这样写，直接报错。

如果拷贝函数的参数中去掉引用符号，进行拷贝时调用拷贝构造函数的过程中会发生“实参和形参都是对象，用实参初始化形参”（拷贝构造第二种调用时机），会再一次调用拷贝构造函数。形成递归调用，直到栈溢出，导致程序崩溃。

**2、拷贝构造函数不可以去掉const。**

——类名（类名 &）形式 编译器不会报错

加const的第一个用意：为了确保右操作数的数据成员不被改变

如果不加const，那么如下操作是可以通过的，不合理。

```c++
Point(Point &rhs)
: _ix(rhs._ix)
, _iy(rhs._iy)
{
    rhs._ix = 0;
    rhs._iy = 0;
    cout << "Point(const Point &rhs)" << endl;
}
```

加const的第二个用意：为了能够复制临时对象的内容，因为非const引用不能绑定临时变量（右值）

如果拷贝构造函数中去掉const

```c++
Computer &rhs = Computer("apple", 12000); //error
```

```c++
Point(Point &rhs)
: _ix(rhs._ix)
, _iy(rhs._iy)
{
    cout << "Point(const Point &rhs)" << endl;
}
```

```c++
//不能取地址的是右值
//临时变量、临时对象、匿名变量、匿名对象
Point pt4 = Point(2, 3);
pt4.print();
```

### 6. 什么情况下，会调用拷贝构造函数?

【答】

拷贝构造函数的调用时机（重点）

**1、当使用一个已经存在的对象初始化另一个同类型的新对象时；**

**2、当函数参数（实参和形参的类型都是对象），形参与实参结合时（实参初始化形参）；**

——为了避免这次不必要的拷贝，可以使用引用作为参数。

```c++
//类似于值传递
//会发生复制
//函数参数设为引用可以避免不必要的复制
void func1(Point pt)
{
    pt.print();
}
void test1()
{
    Point pt1(3, 4);
    func1(pt1);
}
```

**3、当函数的返回值是对象，执行return语句时（编译器有优化）。**

——为了避免这次多余的拷贝，可以使用引用作为返回值，但一定要确保返回值的生命周期大于函数的生命周期。

```c++
//拷贝构造的第三种调用时机
Point func2()
{
    Point pt2(8, 7);
    //执行return语句时会发生复制
    return pt2;
}
void test2()
{
    func2();
}
```

```c++
//拷贝构造的第三种调用时机
//函数返回值设为引用避免不必要的复制
Point pt2(8, 7);
Point &func2()
{
    //执行return语句时会发生复制
    return pt2;
}
void test2()
{
    func2();
}
```

第三种情况直接编译并不会显示拷贝构造函数的调用，但是底层实际是调用了的，加上去优化参数进行编译可以看到效果。

```c++
g++ CopyComputer.cc -fno-elide-constructors
```

### 7. 对于全局对象、静态对象、局部对象、堆上的对象，析构函数的调用时机是怎样的？请编写代码进行验证。

【答】顺序：**1. 堆上的对象 2. 局部对象 3. 静态对象 4. 全局对象**

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char *brand, double price)
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        strcpy(_brand, brand);
    }
    void setBrand(const char *brand)
    {
        strcpy(_brand, brand);
    }
    void setPrice(float price)
    {
        _price = price;
    }
    void print()
    {
        cout << _brand << endl;
        cout << _price << endl;
    }
    ~Computer()
    {
        if(_brand){
            cout << _brand << ": ";
            delete []_brand;
            _brand = nullptr;//设为空指针，安全回收
        }
        cout << "~Computer()" << endl;
    }
private:
    char *_brand;
    double _price;
};

Computer pc1("1:ASUS", 5000);
void test1()
{
    static Computer pc2("2:XiaoMi", 4500);
    Computer pc3("3:Huawei", 6000);

    int *p = new int(1);
    delete p;
    p = nullptr;

    Computer *p2 = new Computer("4:apple", 20000);
    delete p2;
    p2 = nullptr;
}

int main()
{
    test1();
    return 0;
}
```

输出结果：

```html
4:apple: ~Computer()
3:Huawei: ~Computer()
2:XiaoMi: ~Computer()
1:ASUS: ~Computer()
```

构造函数和析构函数的调用时机（重点）

**全局对象**

每当程序开始运行，在主函数main接受程序控制权之前，就调用构造函数创建全局对象，**整个程序结束时**，自动调用全局对象的析构函数。

**静态对象**

当程序流程到达该对象定义处调用构造函数，在**整个程序结束时**调用析构函数。

**局部对象**

每当程序流程到达该对象的定义处就调用构造函数，在**程序离开局部对象的作用域**时调用对象的析构函数。

**堆上的对象**

每当创建该对象时调用构造函数，在**使用delete删除该对象时，调用析构函数。**

```c++
Computer pc1("ASUS", 5000);
void test1()
{
    static Computer pc2("XiaoMi", 4500);
    Computer pc3("Huawei", 6000);
    
    int *p = new int(1);
    delete p;
    p = nullptr;
    
    Computer *p2 = new Computer("apple", 20000);
    delete p2;
    p2 = nullptr;
}
```

### 总结

- 析构函数，其名比类名多`~`；返回类型、形参，不清楚。
- 一个空类，会自动创建的函数。
- 全局对象、静态对象、局部对象、堆上的对象，析构函数调用时机的验证代码。

## 1004 C++基础篇之类和对象04

### 1. 写出以下程序运行的结果。

```cpp
class Sample
{
public:
      Sample();
      void Display();
private:
      int i;
      static int k;
};

Sample::Sample() 
{
	i=0;
	k++;
}

void Sample::Display() 
{
   cout << "i=" << i << ",k=" << k << endl;
}

int Sample::k=0;

int main( ) 
{
    Sample a, b;
    a.Display();
    b.Display();
    
    return 0;
}
```

【答】运行结果

```html
i=0,k=1
i=0,k=2
```

正解：

```c++
i=0,k=2
i=0,k=2
```

### 2. 写出以下程序运行的结果。

```cpp
class Point	
{
public:
    Point(int xx = 0, int yy = 0) 
	{
		X = xx;
		Y = yy;
		cout << "point构造函数被调用" << endl;
	}

   	Point(Point &p);
   	
   	int GetX() 
   	{
   		return X;
   	}
   	
   	int GetY() 
   	{
   		return Y;
   	}

private:
	int X,Y;
};

Point::Point(Point &p)	
{
	X = p.X;
	Y = p.Y;
	cout << "X = " << X << " Y=" << Y << "Point拷贝构造函数被调用" << endl;
}

class Distance	
{
public:	
	Distance(Point xp1, Point xp2);
	double GetDis()
	{
		return dist;
	}
private:	
	Point p1,p2;
	double dist;
};

Distance::Distance(Point xp1, Point xp2)
: p1(xp1)
, p2(xp2)
{
	cout << "Distance构造函数被调用" << endl;
	double x = double(p1.GetX() - p2.GetX());
	double y = double(p1.GetY() - p2.GetY());
	dist = sqrt(x * x + y * y);
}

int main()
{
	Point myp1(1,1), myp2(4,5);
	Distance myd(myp1, myp2);
	cout << "The distance is:" ;
	cout << myd.GetDis() << endl;
	
	return 0;
}
```

【答】

运行结果

```html
The distance is:5
```

正解：

```c++
point构造函数被调用
point构造函数被调用
X = 4 Y=5Point拷贝构造函数被调用
X = 1 Y=1Point拷贝构造函数被调用
X = 1 Y=1Point拷贝构造函数被调用
X = 4 Y=5Point拷贝构造函数被调用
Distance构造函数被调用
The distance is:5
```

### 3. this指针是什么? 有什么作用呢？

【答】

**this指针**

编译器在生成程序时加入了获取对象首地址的相关代码，将获取的**首地址**存放在了寄存器中，这就是this指针。

this指针的本质是一个常量指针`Type* const pointer`；它储存了调用它的对象的地址，不可被修改。这样成员函数才知道自己修改的成员变量是哪个对象的。

**this**是一个隐藏的指针，可以在类的成员函数中使用，它可以用来指向调用对象。当一个对象的成员函数被调用时，编译器会隐式地传递该对象的地址作为this指针。

**this指针指向本对象**

```c++
//返回类型是Point&
//函数名是operator=
//参数是const Point &
//this不能显式地在参数列表中写出
//因为编译器一定会加入一个this指针作为第一个参数
Point &operator=(const Point &rhs)
{
    //可以通过this指针修改其指向的对象的内容
    //不能修改this指针的指向
    //因为this指针是常量指针
    this->_ix = rhs._ix;
    this->_iy = rhs._iy;
    //返回值是，本对象
    return *this;
}
//当对象调用print函数时，
//编译器会自动地添加一个参数：this指针
//this指针指向当前对象（调用本成员函数的对象）
void print()
{
    cout << "()" << this->_ix
         << "," << this->_iy
         << ")" << endl;
}
```

**作用**

this指针的生命周期开始于成员函数的执行开始。当一个非静态成员函数被调用时，this指针被自动设置为指向调用该函数的对象实例。在成员函数执行期间，this指针一直有效。它**可以被用来访问调用对象的成员变量和成员函数**。this指针的生命周期结束于成员函数的执行结束。当成员函数返回时，this指针的作用范围就结束了。

- 对象调用函数时，是**通过this指针**找到自己本对象的数据成员的。

- this指针，代表的是**指向本对象**。

- this指针在参数列表中的位置（默认自动加入，不要手动写出）是：**参数列表的第一位**。

- this指针的形式（常量指针）是：**类名 * const this**。

```c++
Point &operator=(const Point &rhs)
{
    this->_ix = rhs._ix;
    this->_iy = rhs._iy;
    cout << "Point &operator=(const Point &)" << endl;
    return *this;
}
```

成员函数中可以加上this指针，展示本对象通过this指针找到本对象的数据成员。

### 4. 静态数据成员的初始化在哪里，需要注意什么？

【答】

**初始化**

C++允许使用static（静态存储）修饰数据成员，这样的成员**在编译时就被创建并初始化**的（与之相比，对象是在运行时被创建的），且其实例只有一个，被所有该类的对象共享，就像住在同一宿舍里的同学共享一个房间号一样。静态数据成员和之前介绍的静态变量一样，当程序执行时，该成员已经存在，一直到程序结束，任何该类对象都可对其进行访问，静态数据成员存储在全局/静态区，并不占据对象的存储空间。

静态数据成员被整个类的所有对象共享。

```c++
class Computer{
public:
    //...
private:
    char *_brand;
    double _price;
    //数据成员的类型前面加上static关键字
    //表示这是一个static数据成员（共享）
    static double _totalPrice;
};
double Computer::_totalPrice = 0;
```

**注意**

静态成员规则

1. private的静态数据成员无法在类之外直接访问（显然）
2. <span style=color:red;background:yellow>**对于静态数据成员的初始化，必须放在类外**</span>（一般紧接着类的定义，这是规则1的特殊情况）
3. 静态数据成员初始化时不能在数据类型前面加static，在数据成员名前面要加上类名+作用域限定符
4. 如果有多条静态数据成员，那么它们的初始化顺序需要与声明顺序一致（规范）
5. 静态成员在访问时可以通过对象访问，**也可以直接通过类名::成员名的形式**（更常用）

### 5. 定义一个学生类，其中有3个数据成员：学号、姓名、年龄，以及若干成员函数。同时编写main函数，使用这个类，实现对学生数据的复制、赋值与输出。

【答】代码：

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Student
{
public:
    Student(int id, int age, const char *name)
    : _id(id)
    , _age(age)
    , _name(new char[strlen(name) + 1]())
    {
        strcpy(_name, name);
    }
    Student(const Student &rhs)
    : _id(rhs._id)
    , _age(rhs._age)
    , _name(new char[strlen(rhs._name) + 1]())
    {
        strcpy(_name, rhs._name);
        cout << "拷贝构造函数" << endl;
    }
    /*
     * 赋值运算符函数
     * 1. 考虑自复制问题
     * 2. 回收左操作数原本申请的堆空间
     * 3. 深拷贝（以及其他的数据成员的复制）
     * 4. 返回*this
     * */
    Student &operator=(const Student &rhs)
    {
        if(this != &rhs){
            if(_name){
                delete []_name;
            }
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _id = rhs._id;
            _age = rhs._age;
            cout << "赋值运算符函数" << endl;
        }
        return *this;
    }
    ~Student()
    {
        if(_name){
            delete []_name;
            _name = nullptr;
        }
        cout << "~Student()" << endl;
    }
    void print() const
    {
        cout << "id: " << _id << endl
             << "name: " << _name << endl
             << "age: " << _age << endl;
    }
private:
    int _id;
    int _age;
    char *_name;
};

int main()
{
    Student stu1(202401, 21, "Zhang San");
    stu1.print();
    Student stu2(stu1);
    stu2.print();
    Student stu3(202402, 19, "Li Si");
    stu2 = stu3;
    stu2.print();
    return 0;
}
```

### 6. 实现单例的Point类（将单例对象创建在堆上）

【答】代码：

```c++
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
```

结果：

```html
Point(int,int)
(1,2)
(10,20)
~Point()
<<<delete heap
```

### 7. 实现一个单例的Computer类，包含品牌和价格信息。

【答】代码：

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
    static Computer * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Computer("xiaomi",5000);
        }
        return _pInstance;
    }

    void init(const char * brand,double price){
        if(_brand){
            delete [] _brand;
        }
        _brand = new char[strlen(brand) +1]();
        strcpy(_brand,brand);
        _price = price;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
        cout << "<<<delete heap" << endl;
    }

    void print(){
        cout << "brand:" << _brand << endl;
        cout << "price:" << _price << endl;
    }
private:
    Computer(const char * brand, double price)
        : _brand(new char[strlen(brand) + 1]())
          , _price(price)
    {
        cout << "Computer(const char *,double)" << endl;
        strcpy(_brand, brand);
    }

    Computer(const Computer & rhs) = delete;
    Computer & operator=(const Computer & rhs) = delete;

    ~Computer(){
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
        cout << "~Computer()" << endl;
    }
private:
    char * _brand;
    double _price;
    static Computer * _pInstance;
};
Computer * Computer::_pInstance = nullptr;

void test1(){
    Computer::getInstance()->init("Apple", 15000);
    Computer::getInstance()->print();
    Computer::destroy();
}

int main()
{
    test1();
    return 0;
}
```

### 总结

- 第2题执行顺序
- this指针及其作用
- 学生类：构造函数、复制构造函数、赋值运算符函数、析构函数。代码编写
- 单例类Point，将单例对象创建在堆上。代码编写
- 单例类Computer。代码编写

## 1005 C++基础篇之类和对象05

### 1. 执行以下程序，若输入abcd 1234，则输出（ ）。（单选题）

```cpp
char *str;
cin >> str;
cout << str;
```

A. abcd

B. abcd 1234

C. 1234

D. 输出乱码或错误

【答】A

正解：D

### 2. 执行以下程序，若输入abcd 1234，则输出（ ）。（单选题）

```cpp
char a[200] = {0};
cin.getline(a, 200, ' ');
cout << a;
```

A. abcd

B. abcd 1234

C. 1234

D. 输出乱码或错误

【答】A

### 3. 当流失效时，如何重置流的状态，并重新再正常使用流呢？

【答】IO操作与生俱来的一个问题是可能会发生错误，一些错误是可以恢复的，另一些是不可以的。在C++标准库中，用iostate来表示**流的状态**，不同编译器iostate的实现可能不一样，不过都有四种状态：

- <span style=color:red;background:yellow>**badbit **</span>表示发生**系统级的错误**，如不可恢复的读写错误。通常情况下一旦 badbit 被置位，流就无法再使用了。

- <span style=color:red;background:yellow>**failbit **</span>表示发生**可恢复的错误**，如期望读取一个int数值，却读出一个字符等错误。这种问题通常是可以修改的，流还可以继续使用。

- <span style=color:red;background:yellow>**eofbit**</span>表示**到达流结尾位置**， 此时eofbit 和 failbit 都会被置位。

- <span style=color:red;background:yellow>**goodbit **</span>表示流处于**有效状态**。流在有效状态下，才能正常使用。如果 badbit 、 failbit 和 eofbit 任何一个被置位，则流无法正常使用。

这四种状态都定义在类 ios_base 中，作为其数据成员存在。

C++标准库定义了三个预定义的标准输入输出流对象，分别是 `std::cin`、`std::cout` 和 `std::cerr`。

流提取符 “>>” 从流中提取数据时通常跳过输入流中的空格、 tab 键、换行符等空白字符。只有在输入完数据再按回车键后，该行数据才被送入键盘<font color=red>**缓冲区**</font>，形成输入流，提取运算符 “>>” 才能从中提取数据。需要注意保证从流中读取数据能正常进行。

例子，每次从cin中获取一个字符，代码如下。

```c++
void printStreamStatus(std::istream & is){ 
    cout << "is's goodbit:" << is.good() << endl;
    cout << "is's badbit:" << is.bad() << endl;
    cout << "is's failbit:" << is.fail() << endl;
    cout << "is's eofbit:" << is.eof() << endl;
}

void test0(){
    printStreamStatus(cin);  //goodbit状态
    int num = 0;    
    cin >> num;   
    cout << "num:" << num << endl;
    printStreamStatus(cin);  //进行一次输入后再检查cin的状态
}
```

如果没有进行正确的输入，输入流会进入failbit的状态，无法正常工作，需要**恢复流的状态**。

查看C++参考文档，需要**利用<span style=color:red;background:yellow>clear和ignore</span>函数**配合，实现这个过程。

```c++
if(!cin.good()){
    //恢复流的状态
    cin.clear();
    //清空缓冲区，才能继续使用
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout << endl;
    printStreamStatus(cin);
}
```

```c++
void test0()
{
    int num = 10;
    cout << "执行输入操作前检查流的状态" << endl;
    checkStreamStatus(cin);
    
    cout << endl;
    cin >> num;
    cout << "执行输入操作后检查流的状态" << endl;
    checkStreamStatus(cin);
    
    cout << endl;
    if(!cin.good()){
        //恢复流的状态
        cin.clear();
        //还需要清空缓冲区，才能继续使用
        /* cin.ignore(1024, '\n'); */
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        checkStreamStatus(cin);
    }
    
    string line;
    cin >> line;
    cout << "line: " << line << endl;
    
    //没有进行正常输入，会将num设为0
    cout << "num: " << num << endl;
}
```

完成一个输入整型数据的实现（如果是非法输入则继续要求输入）：

```c++
void readInt(int &num)
{
    cout << "请输入一个int型数据" << endl;
    cin >> num;
    while(!cin.eof()){
        if(cin.bad()){
            cout << "cin has broken!" << endl;
            return;
        }else if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入一个int型数据" << endl;
            cin >> num;
        }else{
            cout << "num: " << num << endl;
            break;
        }
    }
}

void test0()
{
    int num = 0;
    readInt(num);
}
```

### 4. 创建存放Point对象的vector，尝试进行遍历

【答】代码：

```c++
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
```

运行结果：

```html
Point构造函数被调用
Point构造函数被调用
Point构造函数被调用
-------------------
Point拷贝构造函数被调用
Point拷贝构造函数被调用
Point拷贝构造函数被调用
3,4: ~Point()
Point拷贝构造函数被调用
Point拷贝构造函数被调用
Point拷贝构造函数被调用
3,4: ~Point()
4,5: ~Point()
-------------------
X = 3, Y = 4
X = 4, Y = 5
X = 5, Y = 6
5,6: ~Point()
4,5: ~Point()
3,4: ~Point()
3,4: ~Point()
4,5: ~Point()
5,6: ~Point()
```

### 5. 创建存放“存放int数据的vector”的vector，尝试进行遍历，并体会vector对象和元素的存储位置

【答】代码：

```c++
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> vec1 = {1, 2, 3};
    vector<int> vec2 = {2, 3, 4, 5};
    vector<vector<int>> vec;
    vec.push_back(vec1);
    vec.push_back(vec2);
    for(size_t i = 0; i < vec.size(); ++i){
        for(size_t j = 0; j < vec[i].size(); ++j){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

运行结果：

```html
1 2 3 
2 3 4 5
```

存储位置：

元素依次存放在vec1和vec2中；vec中依次存放vec1和vec2。

### 6. 利用文件输入流实现能够读取一个文件全部内容的程序

【答】代码：

```c++
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;

/* 读取一个文件的全部内容 */
/* 还可以在创建输入流对象时指定ate模式，省去第一步将游标置流末尾处的操作 */
void test0(){
    string filename = "6.cc";
    ifstream ifs(filename);

    if(!ifs){
        cerr << "ifs open file fail!";
        return;
    }
    
    //读取一个文件的所有内容先要获取文件的大小
    //将游标放到了文件的最后（尾后）
    ifs.seekg(0,std::ios::end);
    long length = ifs.tellg();//获取尾后下标，实际就是总的字符数
    cout << length << endl;

    char * pdata = new char[length]();
    //需要将游标再放置到文件开头
    ifs.seekg(0,std::ios::beg);
    ifs.read(pdata,length);

    //content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    cout << "content:" << content << endl;
    /* cout << pdata << endl; */
    ifs.close();
}

/* 最终版本 */
void test1()
{
    //文件游标置于末尾
    ifstream ifs("6.cc", std::ios::ate);

    if(!ifs.good()){
        cerr << "ifstream open file failed!" << endl;
        return;
    }

    //为了获取字符数
    long length = ifs.tellg();
    cout << "length:" << length << endl;

    char *pdata = new char[length + 1]();

    //文件游标再移到开始位置
    //从文件游标的位置往后读
    ifs.seekg(0);
    ifs.read(pdata, length);

    cout << pdata << endl;
}

int main()
{
    test1();
    return 0;
}
```

按行读取：

使用`<string>`提供的getline方法。

```c++
string filename = "test.cc";
ifstream ifs(filename);
string line;
while(getline(ifs, line)){
    cout << line << endl;
}
ifs.close();
```

### 7. 安装log4cpp，尝试将log4cpp官网的示例代码跑通

【答】**log4cpp的安装**

下载压缩包

下载地址：https://sourceforge.net/projects/log4cpp/files/

安装步骤

```c++
$ tar xzvf log4cpp-1.1.4.tar.gz
$ cd log4cpp
$ ./configure  //进行自动化构建，自动生成makefile
$ make
$ sudo make install  //安装  把头文件和库文件拷贝到系统路径下
//安装完后
//默认头文件路径：/usr/local/include/log4cpp
//默认lib库路径：/usr/local/lib
```

打开log4cpp官网[Log for C++ Project (sourceforge.net)](https://log4cpp.sourceforge.net/)

拷贝simple example的内容，编译运行

编译指令：<span style=color:red;background:yellow>**g++ log4cppTest.cc -llog4cpp -lpthread**</span>

---

<font color=red>**可能报错：找不到动态库**</font>

解决方法：

```c++
cd /etc
```

---

目录中的3个文件

```c++
* ld.so.cache
* ld.so.conf
* ld.so.conf.d/
```

---

```c++
sudo vim ld.so.conf
```

---

将默认的lib库路径写入，再重新加载

```html
ld.so.conf+
1 include /etc/ld.so.conf.d/*.conf
2 /usr/local/lib
```

```c++
sudo ldconfig
```

让动态链接库为系统所共享。

ld.so.cache 执行了sudo ldconfig之后，会更新该缓存文件，会将所有动态库信息写入到该文件。当可执行程序需要加载相应动态库时，会从这里查找。

完成这些操作后，再使用上面的编译指令去编译示例代码。

**代码跑通**

```c++
// main.cpp

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

int main(int argc, char** argv) {
	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
	appender1->setLayout(new log4cpp::BasicLayout());

	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
	appender2->setLayout(new log4cpp::BasicLayout());

	log4cpp::Category& root = log4cpp::Category::getRoot();
	root.setPriority(log4cpp::Priority::WARN);
	root.addAppender(appender1);

	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
	sub1.addAppender(appender2);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}
```

官网结果：

```c++
1352973121 ERROR  : root error
1352973121 ERROR sub1 : sub1 error
1352973121 WARN sub1 : sub1 warn
1352973121 WARN  : 1 + 1 == two ?
1352973121 ERROR  : Streamed root error
1352973121 ERROR sub1 : Streamed sub1 error
1352973121 WARN sub1 : Streamed sub1 warn
1352973121 ERROR  : Another streamed error
```

我的结果：

```c++
1721402161 ERROR  : root error
1721402162 ERROR sub1 : sub1 error
1721402162 WARN sub1 : sub1 warn
1721402162 WARN  : 1 + 1 == two ?
1721402162 ERROR  : Streamed root error
1721402162 ERROR sub1 : Streamed sub1 error
1721402162 WARN sub1 : Streamed sub1 warn
1721402162 ERROR  : Another streamed error
```

### 总结

- 流的状态重置与重新再正常使用，代码。
- 文件输入流，读取一个文件全部内容，代码。
- log4cpp，配置完成。

## 1006 C++基础篇之类和对象06

### 1. 使用log4cpp格式化输出的信息，同时要求输出到终端、文件和回卷文件中。

提示：通过实践来感受log4cpp的使用，这是学习任何第三方库的第一步要做的事儿，先从模仿开始，再慢慢逐步理解。学会使用第三方库，是工作中的基本能力，一定要掌握方法论。

【答】代码

1-1-log4cppTest.cc

```c++
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
using namespace log4cpp;

int main(int argc, char** argv) {
    //基类指针指向派生类对象
    /* Appender *appender1 = new OstreamAppender("console", &std::cout); */
    //目的地
    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);
    //设置布局为basicLayout
	appender1->setLayout(new BasicLayout());

    //还设置了一个目的地保存到文件program.log
	FileAppender *appender2 = new FileAppender("default", "program.log");
	appender2->setLayout(new BasicLayout());

    //通过getRoot创建了根Category对象
    //并在代码中定义了引用root来表示
	Category& root = Category::getRoot();
    //通过日志记录器去设置日志系统的优先级
    //作为过滤日志的门槛
	root.setPriority(Priority::WARN);
    //通过日志记录器添加目的地
	root.addAppender(appender1);//appender1代表输出到终端

    //引用名sub1是代码中用来表示这个创建的子Category的名字
    //传入的参数sub1代表的日志信息中需要保存的日志记录器名字
    //也就是这条日志到底是来源于哪个模块
	Category& sub1 = Category::getInstance(std::string("sub1"));
    //子Category对象会继承父Category对象设置的优先级和目的地
    /* sub1.setPriority(Priority::WARN); */
	/* sub1.addAppender(appender2); */
    sub1.setAppender(appender2);
    sub1.setAdditivity(false);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}
```

1-2-log4cppPattern.cc

```c++
#include <iostream>
/* #include <fstream> */
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
using std::cout;
using std::endl;
/* using std::ofstream; */
using namespace log4cpp;

void test0()
{
    /* ofstream ofs("1-2-ofs.log", std::ios::app); */

    //1. 设置日志布局
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    //2. 创建目的地
    //输出到终端
    OstreamAppender *pos = new OstreamAppender("console", &cout);
    pos->setLayout(ptn1);

    //再创建一个目的地
    //输出到文件（方式1）
    FileAppender *pos2 = new FileAppender("file", "1-2-File.log");
    //目的地和布局要一对一绑定
    pos2->setLayout(ptn2);

    //输出到文件（方式2）
    /* OstreamAppender *pos3 = new OstreamAppender("default", &ofs); */
    /* pos3->setLayout(ptn3); */

    //再创建目的地——回卷文件
    RollingFileAppender *pos3 = new RollingFileAppender("rolling",
                                                        "1-2-rolling.log",
                                                        5 * 1024,
                                                        9);
    pos3->setLayout(ptn3);

    //3. 创建日志记录器
    Category &salesDepart = Category::getInstance("sale");
    //设置优先级
    salesDepart.setPriority(Priority::ERROR);
    //设置目的地
    salesDepart.addAppender(pos);
    salesDepart.addAppender(pos2);
    salesDepart.addAppender(pos3);

    int count = 100;
    while(count-- > 0){
        salesDepart.emerg("this is an emerg msg");
        salesDepart.fatal("this is a fatal msg");
        salesDepart.alert("this is a alert msg");
        salesDepart.crit("this is a crit msg");
        salesDepart.error("this is an error msg");
        salesDepart.warn("this is a warn msg");
        salesDepart.notice("this is a notice msg");
        salesDepart.info("this is a info msg");
        salesDepart.debug("this is a debug msg");
    }

    //回收资源
    Category::shutdown();

    /* ofs.close(); */
}

int main()
{
    test0();
    return 0;
}
```

**输出结果**

1-2-log4cppPattern.cc

```html
2024-07-20 02:13:46,148 sale [FATAL] this is an emerg msg
2024-07-20 02:13:46,148 sale [FATAL] this is a fatal msg
2024-07-20 02:13:46,148 sale [ALERT] this is a alert msg
2024-07-20 02:13:46,148 sale [CRIT] this is a crit msg
2024-07-20 02:13:46,148 sale [ERROR] this is an error msg
2024-07-20 02:13:46,148 sale [FATAL] this is an emerg msg
2024-07-20 02:13:46,148 sale [FATAL] this is a fatal msg
......
```

### 2. 用所学过的类和对象的知识，封装log4cpp，让其使用起来更方便。

要求：可以像printf一样，同时输出的日志信息中最好能有文件的名字，函数的名字及其所在的行号(这个在C/C++里面有对应的宏，可以查一下)

代码模板：

```cpp
class Mylogger
{
public:
	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);
	
private:
	Mylogger();
	~Mylogger();
    
private:
  //......
};


void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

//最终希望的效果
//LogDebug("The log is debug message");
//文件名 函数名 行号 日期 记录器名字 [优先级] 日志信息
```

【答】代码：

2-2-mylogger.cc

```c++
#include <iostream>
#include <cstring>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
using std::cout;
using std::endl;
using namespace log4cpp;

class Mylogger
{
public:
    static Mylogger *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }
    void warn(const char *msg)
    {
        root.warn(msg);
    }
    void error(const char *msg)
    {
        root.error(msg);
    }
    void debug(const char *msg)
    {
        root.debug(msg);
    }
    void info(const char *msg)
    {
        root.info(msg);
    }
    void fatal(const char *msg)
    {
        root.fatal(msg);
    }
    void crit(const char *msg)
    {
        root.crit(msg);
    }
    static void destroy()
    {
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    Mylogger()
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
    }
    ~Mylogger()
    {
        //回收资源
        Category::shutdown();
    }
    Mylogger(Mylogger &rhs) = delete;
    Mylogger &operator=(const Mylogger &rhs) = delete;
private:
    //创建日志记录器
    Category &root = Category::getRoot();
    //定义一个指针保存第一次创建的对象
    static Mylogger *_pInstance;
};
Mylogger *Mylogger::_pInstance = nullptr;

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    log->destroy();
}

class LogInfo
{
public:
    LogInfo(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        info(msg);
    }
    void info(const char *msg)
    {
        root.info(msg);
    }
    LogInfo(LogInfo &rhs) = delete;
    LogInfo &operator=(const LogInfo &rhs) = delete;
    ~LogInfo()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

class LogError
{
public:
    LogError(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        error(msg);
    }
    void error(const char *msg)
    {
        root.error(msg);
    }
    LogError(LogError &rhs) = delete;
    LogError &operator=(const LogError &rhs) = delete;
    ~LogError()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

class LogWarn
{
public:
    LogWarn(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        warn(msg);
    }
    void warn(const char *msg)
    {
        root.warn(msg);
    }
    LogWarn(LogWarn &rhs) = delete;
    LogWarn &operator=(const LogWarn &rhs) = delete;
    ~LogWarn()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

class LogDebug
{
public:
    LogDebug(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        debug(msg);
    }
    void debug(const char *msg)
    {
        root.debug(msg);
    }
    LogDebug(LogDebug &rhs) = delete;
    LogDebug &operator=(const LogDebug &rhs) = delete;
    ~LogDebug()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}
int main()
{
    test1();
    return 0;
}
```

**结果**

```c++
hello,world
1721456235 ERROR  : The log is error message
```

### 3. C++的运算符重载有哪几种形式，尝试以不同形式完成Point类对象的减法操作

【答】**形式**

C++的运算符重载的形式有三种：

1. <span style=color:red;background:yellow>**采用友元函数的重载形式**</span>
2. 采用普通函数的重载形式
3. <span style=color:red;background:yellow>**采用成员函数的重载形式**</span>

**操作**

- 采用友元函数进行重载

像减号这一类不会修改操作数的值的运算符，倾向于采用友元函数的方式重载。

```c++
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
    void print()
    {
        cout << "X = " << X
             << ", Y = " << Y << endl;
    }
    /* 重载-运算符 */
    friend Point operator-(const Point &lhs, const Point &rhs);
private:
    int X, Y;
};
//友元函数进行重载
Point operator-(const Point &lhs, const Point &rhs)
{
    return Point(lhs.X - rhs.X,
                 lhs.Y - rhs.Y);
}
int main()
{
    Point pt1(3, 4);
    Point pt2(2, 1);
    Point pt3 = pt1 - pt2;
    pt3.print();
    return 0;
}
```

- 采用普通函数进行重载

不推荐使用，因为这样做几乎完全失去了对私有成员的保护。

```c++
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
```

- 采用成员函数进行重载

```c++
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
    void print()
    {
        cout << "X = " << X
             << ", Y = " << Y << endl;
    }
    //成员函数实现
    Point operator-(const Point &rhs)
    {
        return Point(X - rhs.X, Y - rhs.Y);
    }
private:
    int X, Y;
};
int main()
{
    Point pt1(3, 4);
    Point pt2(2, 1);
    Point pt3 = pt1 - pt2;
    pt3.print();
    return 0;
}
```

### 4. 编写Base类使下列代码输出为1。提示：本题考查的其实就是运算符重载的知识点。

```c++
int i=2;
int j=7;

Base x(i);
Base y(j);
cout << (x + y == i + j) << endl;
```

【答】代码：

```c++
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    Base(int b)
        : _b(b)
    {}
    friend Base operator+(const Base &lhs, const Base &rhs);
    friend bool operator==(const Base &lhs, const int rhs);
private:
    int _b;
};
Base operator+(const Base &lhs, const Base &rhs)
{
    return Base(lhs._b + rhs._b);
}
bool operator==(const Base &lhs, const int rhs)
{
    return lhs._b == rhs;
}

int main()
{
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x + y == i + j) << endl;
    return 0;
}
```

### 5. 什么是友元？友元的存在形式有？友元有何特点？

【答】**友元**

一般来说，类的私有成员只能在类的内部访问，类之外是不能访问它们的。但如果将其他类/函数设置为类的**友元**，那么**友元类/函数就可以在前一个类的类定义之外访问其私有成员**了。<span style=color:red;background:yellow>**用friend关键字声明友元**</span>。

将类比作一个家庭，类的private 成员相当于家庭的秘密，一般的外人当然不允许探听这些秘密的，只有 friend 才有资格探听这些秘密。

**存在形式**

友元的三种形式：**普通函数、成员函数、友元类**

- 友元的普通函数形式

```c++
class Point{
public:
    Point(int x, int y)
    : _ix(x)
    , _iy(y)
    {}

    friend
    float distance(const Point & lhs, const Point & rhs);
private:
    int _ix;
    int _iy;
};

float distance(const Point & lhs, const Point & rhs){
    return sqrt((lhs._ix - rhs._ix)*(lhs._ix - rhs._ix) +
                (lhs._iy - rhs._iy)*(lhs._iy - rhs._iy));
}

void test0()
{
    Point pt(0, 0);
    Point pt2(5, 12);
    cout << distance(pt, pt2) << endl;
}
```

- 友元的成员函数形式

```c++
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
```

- 友元类

```c++
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class Point
{
public:
    Point(int x, int y)
        : _ix(x)
        , _iy(y)
    {}
    //友元类的声明
    friend class Line;
private:
    int _ix;
    int _iy;
};
class Line
{
public:
    float distance(const Point &lhs, const Point &rhs)
    {
        return sqrt(pow(lhs._ix - rhs._ix, 2) +
                    pow(lhs._iy - rhs._iy, 2));
    }
    void setX(Point &rhs, int x)
    {
        rhs._ix = x;
    }
};
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
```

**特点**

1. **友元不受类中访问权限的限制**——可访问私有成员
2. **友元破坏了类的封装性**
3. **不能滥用友元 ，友元的使用受到限制**
4. **友元是单向的**——A类是B类的友元类，则A类成员函数中可以访问B类私有成员；但并不代表B类是A类的友元类，如果A类中没有声明B类为友元类，此时B类的成员函数中并不能访问A类私有成员
5. **友元不具备传递性**——A是B的友元类，B是C的友元类，无法推断出A是C的友元类
6. **友元不能被继承**——因为友元破坏了类的封装性，为了降低影响，设计层面上友元不能被继承

### 6. 写出下列程序的结果

```c++
class B 
{  
    int y;
public:
    friend class  A;
};
class A
{ 
    int x;
public:  
    A(int a,B &r, int b)  
    {
	x=a; 
	r.y=b;
    } 
     
    void Display( B & ); 
};
void A::Display(B &r)
{
    cout<<x<<" "<<r.y<<endl;
}

int main( )
{   
    B Obj2;
    
    A Obj1(33, Obj2, 88);
    
    Obj1.Display(Obj2);
    return 0;
}
```

答：

```html
33 88
```

### 总结

- 第1题，使用log4cpp，完成。
- 第2题，封装log4cpp，已完成大部分。

- 用友元函数、普通函数、成员函数三种形式，实现了减号运算符的重载。
- 在友元的成员函数形式中，通过前向声明、在Point类定义的后面实现Line的成员函数distance，代码没有报错，运行无误。

## 1007 C++基础篇之运算符重载01

### 1. 编写一个类，实现简单的栈。栈中有以下操作，并自行写出测试用例，每个函数都需要测试到。

```cpp
class Stack {
public:
	bool empty();	//判断栈是否为空
	bool full();	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int  top();		//获取栈顶元素
//...
};
```

【答】代码：

```c++
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
```

结果：

```html
Stack is full now.
5
4
3
2
1
Stack is empty now.
```

### 2. 实现一个自定义的String类，保证main函数对正确执行。实现时，记得采用增量编写的方式，逐一测试。

```cpp
class String
{
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print();
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

int main()
{
	String str1;
	str1.print();
	

	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}
```

【答】代码：

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class String
{
public:
	String()
        : _pstr(nullptr)
    {}
	String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
	String(const String &rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }
	String &operator=(const String &rhs)
    {
        if(this != &rhs){
            if(_pstr){
                delete []_pstr;
            }
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
            cout << "赋值运算符函数" << endl;
        }
        return *this;
    }
	~String()
    {
        if(_pstr){
            delete []_pstr;
        }
        cout << "~String()" << endl;
    }
	void print()
    {
        cout << _pstr << endl;
    }
    size_t length() const
    {
        return strlen(_pstr);
    }
    const char * c_str() const
    {
        return _pstr;
    }
private:
	char * _pstr;
};

int main()
{
	/* String str1; */
	/* str1.print(); */

	String str2 = "Hello,world";
	String str3("Hello, String");
	
	/* str2.print(); */		
	/* str3.print(); */	
	
	String str4 = str3;
	/* str4.print(); */
	
	str4 = str2;
	str4.print();

    printf("%s\n", str4.c_str());
	
	return 0;
}
```

结果：

```html
赋值运算符函数
Hello,world
Hello,world
~String()
~String()
~String()
```

### 3. 统计一篇英文(`The_Holy_Bible.txt`)文章中出现的单词和词频。

**输入**：某篇文章的绝对路径。**输出**：词典文件dict.txt（词典中的内容为**每一行**都是一个“**单词 词频**”）

词典的存储格式如下。

```markup
|   a 66          |
|   abandon 77    |
|   public 88     |
|   ...........   |
|_________________|
```

代码设计：

```cpp
struct Record
{
	string _word;
	int _frequency;
};

class Dictionary
{
public:
	//......
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    vector<Record> _dict;
};
```

**提示**：因为我们需要统计圣经文件中单词以及该单词在文件中出现的次数，所以可以看去读圣经文件，然后将单词存到数据结构中，并记录单词的次数，如果单词第二次出现的时候，只需要修改单词的次数（也就是这里说的单词的频率），这样当统计完整个圣经文件后，数据都存在数据结构vector了。接着遍历vector数据结构就可以将单词以及单词次数(也就是频率)存储到另外一个文件。(当然如果不存到另外一个文件，就只能打印到终端了)

**注意**：在读圣经文件的时候，有可能字符串是不合法的，比如：abc123 abc？这样的字符串，处理方式两种：直接不统计这样的字符串或者将非法字母去掉即可。

【答】代码：

```c++
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;
using std::vector;

struct Record
{
    Record(const string & word,int frequency)
    : _word(word)
    , _frequency(frequency)
    {}

	string _word;
	int _frequency;
};

bool operator<(const Record & lhs, const Record & rhs){
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
    Dictionary(int capacity)
    {
        _dict.reserve(capacity);
    }

    void read(const string &filename){
        ifstream ifs(filename);
        
        if(!ifs){
            cerr << "ifs open file failed!" << endl;
            return;
        }

        //因为磁盘文件读写速度慢，应该尽量减少文件IO的次数
        /* string word; */
        /* while(ifs >> word){ */
        /* } */

        string line;
        while(getline(ifs, line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                //处理单词
                string newWord = dealWord(word);

                //将单词插入到vector
                insert(newWord);
            }
        }

        //对vector中的元素进行排序
        sort(_dict.begin(),_dict.end());

        ifs.close();
    }

    string dealWord(const string & word){
        for(size_t idx = 0; idx != word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();//如果有非法字符就返回空字符串
            }
        }
        return word;
    }

    void insert(const string & word){
        if(word == string())
        {
            return;
        }

        //判断这个单词是否已经在vector中了
        size_t idx = 0;
        for(; idx != _dict.size(); ++idx){
            if(word == _dict[idx]._word){
                ++_dict[idx]._frequency;
                break;
            }
        }

        if(idx == _dict.size()){
            _dict.push_back(Record(word,1));
        }
    }

    void store(const string &filename){
        ofstream ofs(filename);
        
        if(!ofs){
            cerr << "ofs open file failed!" << endl;
            return;
        }

        for(size_t idx = 0; idx != _dict.size(); ++idx){
            ofs << _dict[idx]._word << " "
                << _dict[idx]._frequency <<endl;
        }
        ofs.close();
    }
private:
    vector<Record> _dict;
};

void test0(){
    Dictionary dict(10000);
    dict.read("test.txt");
    /* dict.read("The_Holy_Bible.txt"); */
    dict.store("dictionary.dat");
}

int main()
{
    test0();
    return 0;
}
```

**结果**

文件dictionary.dat

```html
a 32
abel 8
above 6
abundantly 2
accepted 1
according 2
......
```

### 总结

- 第3题，需要重写，尤其注意排序的实现。
- 第2题，注意String()的实现。

## 1008 C++基础篇之运算符重载02

### 1. 自定义一个String类保存字符串内容，实现以下String类的各个函数，并给出相应的测试用例

```cpp
class String 
{
public:
	String();
	String(const char *);
	String(const String &);
	~String();
	String &operator=(const String &);
	String &operator=(const char *);

	String &operator+=(const String &);
	String &operator+=(const char *);
	
	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;
	
	std::size_t size() const;
	const char* c_str() const;
	
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
	
	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);
	
	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);

private:
	char * _pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);
```

【答】重载形式的选择（重要）

* 不会修改操作数的值的运算符，倾向于采用**友元函数**的方式重载
* 会修改操作数的值的运算符，倾向于采用成员函数的方式重载
* **赋值=、下标[ ]、调用()、成员访问->、成员指针访问->* 运算符必须是成员函数形式重载**
* 与给定类型密切相关的运算符，如递增、递减和解引用运算符，通常应该是成员函数形式重载
* 具有对称性的运算符可能转换任意一端的运算对象，例如相等性、位运算符等，通常应该是友元形式重载

代码：

```c++
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class String 
{
public:
    String()
        : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }
    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
    String(const String &rhs)
    {
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    ~String()
    {
        if(_pstr){
            delete []_pstr;
        }
        cout << "~String()" << endl;
    }
    String &operator=(const String &rhs)
    {
        if(this != &rhs){
            if(_pstr){
                delete []_pstr;
            }
            if(rhs._pstr){
                _pstr = new char[strlen(rhs._pstr) + 1]();
                strcpy(_pstr, rhs._pstr);
            }else{
                _pstr = nullptr;
            }
        }
        cout << "String &operator=(const String &rhs)" << endl;
        return *this;
    }
    String &operator=(const char *pstr)
    {
        if(_pstr){
            delete []_pstr;
        }
        _pstr = new char[strlen(pstr) + 1]();
        strcpy(_pstr, pstr);
        cout << "String &operator=(const char *pstr)" << endl;
        return *this;
    }

    String &operator+=(const String &rhs)
    {
        cout << "调用了operator+=函数" << endl;
        char *tmp = new char[strlen(_pstr) + 1]();
        strcpy(tmp, _pstr);
        if(_pstr){
            delete []_pstr;
        }
        _pstr = new char[strlen(tmp) + strlen(rhs._pstr) + 1]();
        strcpy(_pstr, tmp);
        strcat(_pstr, rhs._pstr);
        if(tmp){
            delete []tmp;
        }
        return *this;
    }
    String &operator+=(const char *pstr)
    {
        cout << "String &operator+=(const char *)" << endl;
        char *tmp = new char[strlen(_pstr) + 1]();
        strcpy(tmp, _pstr);
        if(_pstr){
            delete []_pstr;
        }
        _pstr = new char[strlen(tmp) + strlen(pstr) + 1];
        strcpy(_pstr, tmp);
        strcat(_pstr, pstr);
        if(tmp){
            delete []tmp;
        }
        return *this;
    }

    char &operator[](std::size_t index)
    {
        if(index < size() - 1){
            return _pstr[index];
        }else{
            cout << "out of range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    const char &operator[](std::size_t index) const
    {
        return _pstr[index];
    }

    std::size_t size() const
    {
        return sizeof(_pstr);
    }
    const char* c_str() const
    {
        return _pstr;
    }
    void print() const
    {
        cout << _pstr << endl;
    }

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend ostream &operator<<(ostream &os, const String &s);
    friend istream &operator>>(istream &is, String &s);

    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char *, const String &);
private:
    char * _pstr;
};

String operator+(const String &lhs, const String &rhs)
{
    String s;
    s._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1]();
    strcpy(s._pstr, lhs._pstr);
    strcat(s._pstr, rhs._pstr);
    return s;
}
String operator+(const String &lhs, const char *rhs)
{
    String s;
    s._pstr = new char[strlen(lhs._pstr) + strlen(rhs) + 1]();
    strcpy(s._pstr, lhs._pstr);
    strcat(s._pstr, rhs);
    return s;
}
String operator+(const char *lhs, const String &rhs)
{
    String s;
    s._pstr = new char[strlen(lhs) + strlen(rhs._pstr) + 1]();
    strcpy(s._pstr, lhs);
    strcat(s._pstr, rhs._pstr);
    return s;
}

bool operator==(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) != 0;
}

bool operator<(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

ostream &operator<<(ostream &os, const String &s)
{
    os << s._pstr << endl;
    return os;
}

istream &operator>>(istream &is, String &s)
{
    is >> s._pstr;
    return is;
}

int main()
{
    String s1;
    String s2("Hello, World");
    /* s2.print(); */
    String s3 = s2;
    s3.print();
    cout << "----------------" << endl;
    s3 = s1;
    s3 = "nihao";
    s3.print();
    cout << "----------------" << endl;
    s3 += s2;
    s3.print();
    s3 += "back";
    s3.print();
    cout << s3[3] << endl;
    cout << s3[4] << endl;
    cout << s3[5] << endl;
    cout << "----------------" << endl;
    cout << (s3 < s2) << endl;
    cout << s3;
    /* cin >> s3; */
    /* cout << s3; */
    cout << "----------------" << endl;
    String s4 = s2 + s3;
    cout << s2 << s3;
    cout << s4;
    s4 = s2 + "你好";
    cout << s4;
    s4 = "你好" + s2;
    cout << s4;
    return 0;
}
```

**输出结果**

```txt
String()
Hello, World
----------------
String &operator=(const String &rhs)
String &operator=(const char *pstr)
nihao
----------------
调用了operator+=函数
nihaoHello, World
String &operator+=(const char *)
nihaoHello, Worldback
a
o
H
----------------
0
nihaoHello, Worldback
----------------
String()
Hello, World
nihaoHello, Worldback
Hello, WorldnihaoHello, Worldback
String()
String &operator=(const String &rhs)
~String()
Hello, World你好
String()
String &operator=(const String &rhs)
~String()
你好Hello, World
~String()
~String()
~String()
~String()

```

### 总结

- 增量编写，也要注意友元函数的使用。

## 1009 C++基础篇之运算符重载03

### 1. 在类之外定义一个全局类AutoRelease，实现单例模式的自动释放

【答】代码：

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Singleton("Huawei", 5000);
        }
        return _pInstance;
    }
    void init(const char *brand, double price)
    {
        if(_brand){
            delete []_brand;
        }
        _brand = new char[strlen(brand) + 1]();
        strcpy(_brand, brand);
        _price = price;
    }
    void print()
    {
        cout << "brand: " << _brand << endl;
        cout << "price: " << _price << endl;
    }
private:
    Singleton(const char *brand, double price)
        : _brand(new char[strlen(brand) + 1]())
          , _price(price)
    {
        cout << "Singleton(const char *, double)" << endl;
        strcpy(_brand, brand);
    }
    Singleton(Singleton &rhs) = delete;
    Singleton &operator=(const Singleton &rhs) = delete;
    ~Singleton()
    {
        if(_brand){
            delete []_brand;
            _brand = nullptr;
        }
        cout << "~Singleton()" << endl;
    }
private:
    char *_brand; //电脑品牌
    double _price;//电脑价格
    //定义一个指针保存第一次创建的对象
    static Singleton *_pInstance;
private:
    friend class AutoRelease;
};
Singleton * Singleton::_pInstance = nullptr;

class AutoRelease{
public:
    AutoRelease(Singleton * p)
        : _p(p)
    { cout << "AutoRelease(Singleton*)" << endl; }

    ~AutoRelease()
    {
        cout << "~AutoRelease()" << endl;
        if(_p){
            delete _p;
            _p = nullptr;
        }
    }
private:
    Singleton * _p;
};

void test0()
{
    AutoRelease ar(Singleton::getInstance());
    Singleton::getInstance()->print();
}

int main()
{
    test0();
    return 0;
}
```

结果：

```html
Singleton(const char *, double)
AutoRelease(Singleton*)
brand: Huawei
price: 5000
~AutoRelease()
~Singleton()
```

### 2. 使用嵌套类和静态对象的方式，实现单例模式的自动释放

【答】代码：

```c++
#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
    class AutoRelease{
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Singleton(1, 2);
        }
        return _pInstance;
    }
    void init(int x, int y)
    {
        _ix = x;
        _iy = y;
    }
    void print()
    {
        cout << "(" << this->_ix
            << "," << this->_iy
            << ")" << endl;
    }
private:
    Singleton(int x, int y)
        : _ix(x)
          , _iy(y)
    {
        cout << "Singleton(int,int)" << endl;
    }
    Singleton(const Singleton &rhs) = delete;
    Singleton &operator=(const Singleton &rhs) = delete;
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
    static AutoRelease _ar;
};
Singleton* Singleton::_pInstance = nullptr;
//使用AutoRelease类的无参构造对_ar进行初始化
Singleton::AutoRelease Singleton::_ar;

void test1(){
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(10,80);
    Singleton::getInstance()->print();
}

int main()
{
    test1();
    return 0;
}
```

结果：

```html
AutoRelease()
Singleton(int,int)
(1,2)
(10,80)
~AutoRelease()
~Singleton()
```

### 3. 在我们建立了基本的写时复制字符串类的框架后，发现了一个遗留的问题。

如果str1和str3共享一片空间存放字符串内容。如果进行读操作，那么直接进行就可以了，不用进行复制，也不用改变引用计数；如果进行写操作，那么应该让str1重新申请一片空间去进行修改，不应该改变str3的内容。

cout << str1[0] << endl; //读操作
str1[0] = 'H';         //写操作
cout << str3[0] << endl;//发现str3的内容也被改变了

我们首先会想到运算符重载的方式去解决。但是str1[0]返回值是一个char类型变量。

读操作 cout << char字符 << endl;

写操作 char字符 = char字符；

无论是输出流运算符还是赋值运算符，操作数中没有自定义类型对象，无法重载。而CowString的下标访问运算符的操作数是CowString对象和size_t类型的下标，也没办法判断取出来的内容接下来要进行读操作还是写操作。

—— 提示：创建一个CowString类的内部类，让CowString的operator[]函数返回是这个新类型的对象，然后在这个新类型中对<<和=进行重载，让这两个运算符能够处理新类型对象，从而分开了处理逻辑。

【答】

### 总结

- 实现了第1题和第2题，学会了单例模式自动释放的两种重要方法。
- 第3题，没看懂。

## 1010 C++基础篇之继承01

### 1. 实现以下函数，简单模拟SSO思想的string并验证实现效果

```cpp
class String {
public:
    String(const char * pstr);
    ~String();
    char & operator[](size_t idx);

    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
	union Buffer{
		char * _pointer = nullptr;
		char _local[16];
	};
	
	size_t _size;
	size_t _capacity;
    Buffer _buffer;
};

void test0(){
    String str1("hello");
    String str2("hello,world!!!!!");
    //...
}
```

【答】代码：

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    String(const char * pstr)
    {
        cout << "String(const char * pstr)" << endl;
        if(strlen(pstr) <= sizeof(_buffer._local) - 1){//15
            strcpy(_buffer._local, pstr);
            /* cout << _buffer._local << endl; */
            _buffer._pointer = nullptr;
            _size = strlen(_buffer._local);
            _capacity = sizeof(_buffer._local);//16
        }else{
            _buffer._pointer = new char[strlen(pstr) + 1]();
            strcpy(_buffer._pointer, pstr);
            _size = strlen(_buffer._pointer);
            _capacity = strlen(_buffer._pointer) + 1;
        }
    }
    ~String()
    {
        if(_buffer._pointer){
            delete []_buffer._pointer;
        }
        cout << "~String()" << endl;
    }
/*
    char & operator[](size_t idx)
    {
        cout << "char & operator[](size_t idx)" << endl;
        if(_size <= sizeof(_buffer._local) - 1){  //15
            cout << "1" << endl;
            if(idx <= sizeof(_buffer._local) - 2){//14
                cout << "2" << endl;
                cout << _buffer._local << endl;
                return _buffer._local[idx];
            }
        }
        else{
            if(idx < _size - 1){
                return _buffer._pointer[idx];
            }
        }
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
*/
    friend
        ostream & operator<<(ostream & os,const String & rhs);
private:
    union Buffer{
        char * _pointer = nullptr;
        char _local[16];
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

void test0(){
    String str1("hello");
    /* cout << str1[2] << endl; */
    /* String str2("hello,world!!!!!"); */
    //...
}

int main()
{
    test0();
    return 0;
}
```

结果：

```html
String(const char * pstr)

~String()
```

正解：

```c++
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

//共用体的特性：
//1.所有成员都存在同一内存空间上，
//一次只能使用一个成员
//2.对union的某个成员进行写操作
//可能会导致整个union的内存被重新初始化
class String {
public:
    String(const char * pstr)
    {
        _size = strlen(pstr);
        if(_size <= 15){
            _capacity = 15;
            strcpy(_buffer._local,pstr);           
        }else{
            _capacity = strlen(pstr);
            _buffer._pointer = new char[strlen(pstr) + 1]();
            strcpy(_buffer._pointer,pstr);
        }
    }

    ~String(){
        if(_size > 15){
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }

    char & operator[](size_t idx){
        if(idx > _size - 1){
            cout << "out of range!" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
        if(_size > 15){
                return _buffer._pointer[idx];    
        }else{
                return _buffer._local[idx];
        }
    }
    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
	union Buffer{
		char * _pointer = nullptr;
		char _local[16];
	};
	
	size_t _size;
	size_t _capacity;
    Buffer _buffer;
};

ostream & operator<<(ostream & os,const String & rhs){
    if(rhs._size > 15){
        os << rhs._buffer._pointer;
    }else{
        os << rhs._buffer._local;
    }
    return os;
}


void test0(){
    String str1("hello");
    String str2("hello,world!!!!!");

    cout << str1 << endl;
    cout << &str1 << endl;
    cout << &str1[0] << endl;
    printf("%p\n",&str1[0]);
    cout << str1[0] << endl;
    str1[0] = 'H';
    cout << str1 << endl;

    cout << endl;
    cout << str2 << endl;
    cout << &str2 << endl;
    printf("%p\n",&str2[0]);
    cout << str2[0] << endl;
    str2[0] = 'X';
    cout << str2 << endl;

    cout << str2[100] << endl;
}

int main(void){
    test0();
    return 0;
}
```

### 2. 词频统计的作业再用map容器去实现一次，体验一下使用vector/map时程序执行的速度。提示：++dict[word];

【答】

正解：

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

class Dictionary
{
public:
    void read(const string &filename){
        ifstream ifs(filename);
        
        if(!ifs){
            cerr << "ifs open file failed!" << endl;
            return;
        }

        //因为磁盘文件读写速度慢，应该尽量减少文件IO的次数
        /* string word; */
        /* while(ifs >> word){ */
        /* } */

        string line;
        while(getline(ifs, line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                //处理单词
                string newWord = dealWord(word);
                
                if(newWord != string()){
                    //只要不是空字符串（对应的含有非法字符的单词）
                    //就可以用这种方式保存
                    ++_dict[newWord];
                }
            }
        }
        ifs.close();
    }

    string dealWord(const string & word){
        for(size_t idx = 0; idx != word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();//如果有非法字符就返回空字符串
            }
        }
        return word;
    }

    void store(const string &filename){
        ofstream ofs(filename);
        
        if(!ofs){
            cerr << "ofs open file failed!" << endl;
            return;
        }

        map<string, int>::iterator it = _dict.begin();
        for(;it != _dict.end();++it){
            ofs << it->first << " " << it->second << endl;
        }
        ofs.close();
    }
private:
    map<string, int> _dict;
};

void test1(){
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dictionary.dat");
}

int main(){
    test1();
    return 0;
}
```

### 总结

- 第2题，需要重做。
- 第1题，需要参考答案。

## 1011 C++基础篇之多态01

### 1. C++中有哪几种多态，简单阐述各种多态的使用情况

<span style=color:red;background:yellow>**C++支持两种多态性：编译时多态和运行时多态。**</span>

**编译时多态**：也称为**静态多态**，之前的**函数重载**、**运算符重载**就是采用的静态多态，C++编译器根据传递给函数的参数和函数名决定具体要使用哪一个函数，又称为静态联编。

**运行时多态**：在一些场合下，编译器无法在编译过程中完成联编，必须在程序运行时完成选择，因此编译器必须提供这么一套称为“动态联编”（dynamic binding）的机制，也叫动态联编。C++通过**虚函数**来实现动态联编。

### 2. 什么是重载？什么是隐藏？什么是覆盖？他们之前的区别是？

重载 (overload) ：发生在同一个类中， 当函数名称相同时 ，函数参数类型、顺序 、个数任一不同；

隐藏 (oversee) ：发生在基类派生类之间 ，函数名称相同时，就构成隐藏（参数不同也能构成隐藏）；

覆盖 (override) ：发生在基类派生类之间，基类与派生类中同时定义相同的虚函数，覆盖的是虚函数表中的入口地址，并不是覆盖函数本身。

### 3. 多基派生会产生的问题有哪些？怎样解决？

【答】（1）成员名访问冲突的二义性。

解决成员名访问冲突的方法：加类作用域（不推荐）—— 应该尽量避免。

同时，<span style=color:red;background:yellow>**如果D类中定义了同名的成员，可以对基类的这些成员造成隐藏效果**</span>，那么就可以直接通过成员名进行访问。

``` c++
    D d;
    d.A::print();
    d.B::print();
    d.C::print();
    d.print(); //ok
```

（2）存储二义性的问题（重要）。

菱形继承结构

```c++
class A
{
public:
    void print() const{
        cout << "A::print()" << endl;
    }
    double _a;
};

class B
: public A
{
public:
    double _b;
};

class C
: public A
{
public:
    double _c;
};

class D
: public B
, public C
{
public:
    double _d;
};
```

菱形继承情况下，D类对象的创建会生成一个B类子对象，其中包含一个A类子对象；还会生成一个C类子对象，其中也包含一个A类子对象。所以D类对象的内存布局中有多个A类子对象，访问继承自A的成员时会发生二义性。因为编译器需要通过基类子对象去调用，但是不知道应该调用哪个基类子对象的成员函数。

```c++
void test0()
{
    D dd;
    //只能通过A类的基类子对象调用print函数
    //但是此时一个D类对象中包含两个A类的基类子对象
    //dd.print();//error
    cout << sizeof(D) << endl;
}
```

当然，D类如果再写一个同名成员函数，会发生隐藏。

<span style=color:red;background:yellow>**解决存储二义性的方法：中间层的基类采用虚继承顶层基类的方式解决存储二义性**</span>

```c++
class A
{
public:
    void print() const{
        cout << "A::print()" << endl;
    }
    double _a;
};

class B
: virtual public A
{
public:
    double _b;
};

class C
: virtual public A
{
public:
    double _c;
};

class D
: public B
, public C
{
public:
    double _d;
};
```

采用虚拟继承的方式处理菱形继承问题，实际上改变了派生类的内存布局。B类和C类对象的内存布局中多出一个虚基类指针，位于所占内存空间的起始位置，同时继承自A类的内容被放在了这片空间的最后位置。D类对象中只会有一份A类的基类子对象。

### 4. 构建一个类Person，包含字符串成员name（姓名），整型数据成员age（年龄），成员函数 display()用来输出name和age。

构造函数包含两个参数，用来对name和age初始化。

构建一个类Employee由Person派生，包含department（部门），实型数据成员salary（工资），成员函数display()用来输出职工姓名、年龄、部门、工资，其他成员根据需要自己设定。主函数中定义3个Employee类对象，内容自己设定，将其姓名、年龄、部门、工资输出。要求：用char*来保存字符串内容，并能实现Employee对象的复制、赋值操作。

【答】

派生类的访问权限如下：

1. 不管什么继承方式，派生类内部都不能访问基类的私有成员；
2. 不管什么继承方式，派生类内部除了基类的私有成员不可以访问，其他的都可以访问；
3. 不管什么继承方式，派生类对象在类外除了公有继承基类中的公有成员可以访问外，其他的都不能访问。

**(记忆：1.私有的成员在类外无法直接访问； 2.继承方式和基类成员访问权限做交集)**

代码：

```c++
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Person
{
public:
    Person(const char *name, int age)
        : _name(new char[strlen(name) + 1]())
          , _age(age)
    {
        strcpy(_name, name);
    }
    void display()
    {
        cout << "name: " << _name
            << ", age: " << _age << endl;
    }
    ~Person()
    {
        if(_name){
            delete []_name;
        }
    }
public:
    char *_name;
    int _age;
};

class Employee
: public Person
{
public:
    Employee(const char *name, int age,
             const char *department, double salary)
        : Person(name, age)
          , _department(new char[strlen(department) + 1])
          , _salary(salary)
    {
        strcpy(_department, department);
    }
    Employee(const Employee &rhs)
        : Person(rhs._name, rhs._age)
          , _department(new char[strlen(rhs._department) + 1]())
          , _salary(rhs._salary)
    {
        strcpy(_department, rhs._department);
    }
    Employee &operator=(const Employee &rhs)
    {
        if(this != &rhs){
            if(_name){
                delete []_name;
            }
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
            if(_department){
                delete []_department;
            }
            _department = new char[strlen(rhs._department) + 1]();
            strcpy(_department, rhs._department);
            _salary = rhs._salary;
        }
        return *this;
    }
    void display()
    {
        cout << "name: " << _name
            << ", age: " << _age
            << ", department: " << _department
            << ", salary: " << _salary << endl;
    }
    ~Employee()
    {
        if(_department){
            delete []_department;
        }
    }
private:
    char *_department;
    double _salary;
};

int main()
{
    Employee e1("张三", 23, "C++部门", 13000);
    Employee e2("李四", 25, "C++部门", 15000);
    Employee e3 = e2;
    e2 = e1;
    e1.display();
    e2.display();
    e3.display();
    return 0;
}
```

结果：

```html
name: 张三, age: 23, department: C++部门, salary: 13000
name: 张三, age: 23, department: C++部门, salary: 13000
name: 李四, age: 25, department: C++部门, salary: 15000
```

### 5. 编写程序：给定以下抽象类Figure，通过该图形类扩展生成3个不同的图形Rectangle、Circle、Triangle，体会使用纯虚函数的好处。

```cpp
class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是:" 
         << fig.getArea() << endl ;
}

void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}
```

【答】代码：

```c++
#include <iostream>
#include <string>
#include <cmath>
using std::cout;
using std::endl;
using std::string;

const double PI = 3.141592653;

class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是: " 
         << fig.getArea() << endl ;
}

class Rectangle //矩形
: public Figure
{
public:
    Rectangle(double len, double wid)
    : _length(len)
    , _width(wid)
    {}
    string getName() const override
    {
        return "矩形";
    }
    double getArea() const override
    {
        return _length * _width;
    }
private:
      double _length;
      double _width;
};

class Circle
: public Figure
{
public:
    Circle(double r)
    : _radius(r)
    {}
    string getName() const override
    {
        return "圆形";
    }
    double getArea() const override
    {
        return PI * _radius * _radius;
    }
private:
    double _radius;
};

class Triangle
: public Figure
{
public:
    Triangle(double a, double b, double c)
    : _a(a)
    , _b(b)
    , _c(c)
    {}
    string getName() const override
    {
        return "三角形";
    }
    double getArea() const override
    {
        double p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }
private:
    double _a, _b, _c;
};

void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}

int main()
{
    test();
    return 0;
}
```

结果：

```html
矩形的面积是: 200
圆形的面积是: 706.858
三角形的面积是: 6
```

### 总结

- 第4题，代码题，需要确保理解。
- 第5题，代码题。
- 需要理解虚函数、纯虚函数。



## 1012 C++基础篇之多态02

### 1. 文本查询

该程序将读取用户指定的任意文本文件【china_daily.txt】，然后允许用户从该文件中查找单词。查询的结果是该单词出现的次数，并列出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行一次。行号按升序显示。

要求：

```cpp
a. 它必须允许用户指明要处理的文件名字。
b. 程序将存储该文件的内容，以便输出每个单词所在的原始行。
vector<string> lines;//O(1)
c. 它必须将每一行分解为各个单词，并记录每个单词所在的所有行。
在输出行号时，应保证以升序输出，并且不重复。
map<string, set<int> > wordNumbers;
map<string, int> dict;
d. 对特定单词的查询将返回出现该单词的所有行的行号。
e. 输出某单词所在的行文本时，程序必须能根据给定的行号从输入
文件中获取相应的行。
```

示例：
使用提供的文件内容，然后查找单词 "element"。输出的前几行为：

```cpp
---------------------------------------------
element occurs 125 times.
(line 62) element with a given key.
(line 64) second element with the same key.
(line 153) element |==| operator.
(line 250) the element type.
(line 398) corresponding element.
---------------------------------------------
```

程序接口[可选]:

```cpp
class TextQuery
{
public:
//......
void readFile(const string filename);
void query(const string & word);//

private:
//......
vector<string> _lines;//O(1)
map<string, set<int> > _wordNumbers;//the the
map<string, int> _dict;//
};
```

//程序测试用例

```cpp
int main(int argc, char *argv[])
{
    string queryWord("hello");

    TextQuery tq;
    tq.readFile("test.dat");
    tq.query(queryWord);
    return 0;
}
```

【答】

代码：

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::set;
using std::string;
using std::istringstream;
using std::ifstream;
using std::ofstream;

class TextQuery
{
public:
    void readFile(const string filename)
    {
        ifstream ifs(filename);
        string line;
        while(getline(ifs, line)){
            lines.push_back(line);
        }
        ifs.close();
        int lineNum = 1;
        for(auto &line : lines){
            istringstream iss(line);
            string word;
            while(iss >> word){
                string newWord = dealWord(word);
                if(newWord != string()){
                    ++dict[newWord];
                    wordNumbers[newWord].insert(lineNum);
                }
            }
            ++lineNum;
        }
        ofstream ofs("dict-query.dat");
        map<string, int>::iterator it = dict.begin();
        for(; it != dict.end(); ++it){
            ofs << it->first << " "
                << it->second << endl;
        }
        ofs.close();
    }
private:
    string dealWord(string word)
    {
        for(size_t idx = 0; idx < word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();
            }
            if(isupper(word[idx])){
                word[idx] = tolower(word[idx]);
            }
        }
        return word;
    }
public:
    void query(const string &word)
    {
        cout << word << " occurs "
             << dict[word] << " times." << endl;
        for(auto &n : wordNumbers[word]){
            cout << "    (line " << n << ") ";
            cout << lines[n - 1] << endl;
        }
    }
private:
    vector<string> lines;//O(1)
    map<string, set<int>> wordNumbers;//the the
    map<string, int> dict;//
};

int main(int argc, char *argv[])
{
    string queryWord;
    cin >> queryWord;
    TextQuery tq;
    tq.readFile(argv[1]);
    tq.query(queryWord);
    return 0;
}
```

结果：

```txt
cs@cs-vm:~/code/cpp$ ./a.out china_daily.txt 
china
china occurs 2 times.
    (line 11) Stock Connect, said Gao Ting, chief China equities strategist at UBS Securities.
    (line 34) Zhao Wenli, an analyst at China Merchants Securities (HK) Co Ltd, said in a
```

### 2. 使用tinyXml2解析RSS文件，并生成一个网页库pagelib.txt

```markup
tinyXml2 -- https://github.com/leethomason/tinyxml2
rss      -- https://coolshell.cn/feed
         -- http://www.runoob.com/rss/rss-tutorial.html
```

参考接口：

```cpp
struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

class RssReader {
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
};   
```

要求：最后生成一个 pagelib.txt, 其格式:

```markup
<doc>
	<docid>1</docid>
	<title>...</title>
	<link>...</link>
	<description>...</description>
	<content>...</content>
</doc>
<doc>
	<docid>2</docid>
	<title>...</title>
	<link>...</link>
	<description>...</description>
	<content>...</content>
</doc>
<doc>
  ...
</doc>
```

思路提示：

RSS文件解析作业思路：

​    xml -->rss-->tinyxml2(使用该库对rss文件进行解析)--> std::regex(使用正则表达式去除html标签)

RSS文件就是一个树形结构

```markup
<rss>
    <channel>
       <item>
  	 <title>xxx</title>
 	 <link>   </link>
  	 <description>   </description>
 	 <content:encoded>   </content:encoded>
       </item>
       <item>
    	 <title>  </title>
    	 <link>   </link>
    	 <description>   </description>
         <content:encoded>   </content:encoded>
       </item>
       <item>
        ...
       </item>
    </channel>
</rss>
```

【答】

代码：

```c++
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include "tinyxml2.h"
#include "tinyxml2.cpp"
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using std::ofstream;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
    XMLDocument doc;
};
RssReader::RssReader()
{
    doc.LoadFile("coolshell.xml");
}
void RssReader::parseRss()
{
    XMLElement *itemElement = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    while(itemElement){
        XMLElement *titleElement = itemElement->FirstChildElement("title");
        XMLText* textNode = titleElement->FirstChild()->ToText();
        const char *title = textNode->Value();
        /* cout << title << endl; */

        XMLElement *linkElement = itemElement->FirstChildElement("link");
        textNode = linkElement->FirstChild()->ToText();
        const char *link = textNode->Value();
        /* cout << link << endl; */

        XMLElement *descriptionElement = itemElement->FirstChildElement("description");
        textNode = descriptionElement->FirstChild()->ToText();
        const char *description = textNode->Value();
        regex tagRegex("<[^>]+>");
        string descriptionRes = regex_replace(description, tagRegex, "");
        /* cout << descriptionRes << endl; */

        XMLElement *contentElement = itemElement->FirstChildElement("content:encoded");
        textNode = contentElement->FirstChild()->ToText();
        const char *content = textNode->Value();
        string contentRes = regex_replace(content, tagRegex, "");
        /* cout << contentRes << endl; */

        RssItem item;
        item.title = title;
        item.link = link;
        item.description = descriptionRes;
        item.content = contentRes;

        _rss.push_back(item);
        itemElement = itemElement->NextSiblingElement();
    }
}
void RssReader::dump(const string & filename)
{
    ofstream ofs(filename);
    int count = 1;
    for(size_t i = 0; i < _rss.size(); ++i){
        ofs << "<doc>" << endl;
        ofs << "    <docid>" << count++ << "</docid>" << endl;
        ofs << "    <title>" << _rss[i].title << "</title>" << endl;
        ofs << "    <link>"  << _rss[i].link << "</link>" << endl;
        ofs << "    <description>" << _rss[i].description << "</description>" << endl;
        ofs << "    <content>" << _rss[i].content << "</content>" << endl;
        ofs << "</doc>" << endl;
    }
    ofs << endl;
    ofs.close();
}
int main()
{
    RssReader r;
    r.parseRss();
    r.dump("pagelib.txt");
    return 0;
}
```

结果：

```html
<doc>
    <docid>1</docid>
    <title>是微服务架构不香还是云不香？</title>
    <link>https://coolshell.cn/articles/22422.html</link>
    <description>这两天技术圈里热议的一件事就是Amazon的流媒体平台Prime Video在2023年3月22日发布了一篇技术博客《规模化Prime Video的音视频监控服...
 Read More  Read More
The post 是微服务架构不香还是云不香？ first appeared on 酷 壳 - CoolShell.</description>
    <content>
......
```

### 总结

- 文本查询，需要重新看。

## 1013 C++基础篇之多态03

### 1. 根据给定的程序，写出执行结果

```cpp
#include <iostream>
using std::endl;
using std::cout;

class A
{
public:
	A(int i,int j) 
	{
		a=i;
		b=j;
	}
	void move(int i,int j) 
	{
		a += i;
		b += j;
	}
	void disp() 
	{ 
		cout << "(" << a << "," << b << ")" << endl;
	}
private:
	int a,b;
};

class B
: public A
{
public:
	B(int i,int j,int k,int l)
	:A(i,j)
	,x(k)
	,y(l)
	{ 
	}
	
	void disp() 
	{
		cout << x << "," << y << endl;
	}
	void fun() 
	{
		move(3,5);
	}

private:
	int x,y;
};

int main()
{
	A m(1,2);
	m.disp();
	B d(3,4,5,6);
	d.fun();
	d.A::disp();
	d.disp();

	return 0;

}
```

【答】

```html
(1,2)
(6,9)
5,6
```

### 2. 根据给定的程序，写出执行结果

```cpp
#include<iostream>

using std::endl;
using std::cout;

class Base1
{
public:
    virtual void fun()
    {
		cout<<"--Base1--\n";
	}
};

class Base2
{
public:
    void fun()
    {
		cout<<"--Base2--\n";
	}
};

class Derived
:public Base1
,public Base2
{
public:
    void fun()
    {
        cout<<"--Derived--\n";
    }
};

int main()
{
    Base1 obj1, *ptr1;
    Base2 obj2, *ptr2;
    Derived obj3; 
	
    ptr1=&obj1;         	
    ptr1->fun(); 
    
    ptr2=&obj2;
    ptr2->fun();
    
    ptr1=&obj3;
    ptr1->fun();
    
    ptr2=&obj3;
    ptr2->fun();
    
    return 0;

}
```

【答】

```html

```



### 3. 根据给定的程序，写出执行结果

```cpp
class A
{
public:
 void FuncA()
 {
     printf( "FuncA called\n" );
 }
 virtual void FuncB()
 {
     printf( "FuncB called\n" );
 }
};

class B 
: public A
{
public:
 void FuncA()
 {
     A::FuncA();
     printf( "FuncAB called\n" );
 }
    
 virtual void FuncB()
 {
     printf( "FuncBB called\n" );
 }
};

int main( void )
{
	B	b;
	A	*pa;
	pa = &b;
	A *pa2 = new A;
	pa->FuncA(); （ 3） 
	pa->FuncB(); （ 4）
	pa2->FuncA(); （ 5）
	pa2->FuncB();
	delete pa2;
	

	return 0；

}
```

【答】



### 4. 根据给定的程序，写出执行结果

```cpp
class Base
{
public:
    Base(int j)
    : i(j) 
    {
        
    }
    virtual  ~Base() 
    {
        
    }
    
    void func1() 
    {
        i *= 10;
        func2();
    }
    
    int getValue()
    {
        return  i;
    }
    
protected:
    virtual void func2()
    {
        i++;
    }
    
protected:
    int i;
};

class Child
: public Base
{
public:
    Child(int j)
    : Base(j) 
    {
        
    }
    void func1()
    {
        i *= 100;
        func2();
    }
    
protected:
    void func2()
    {
        i += 2;
    }
};

int main() 
{
    Base * pb = new Child(1);
    pb->func1();
    cout << pb->getValue() << endl; 
    
	delete pb; 
    
	return 0；
} 
```

【答】



### 5. 文本查询

该程序将读取用户指定的任意文本文件【china_daily.txt】， 然后允许用户从该文件中查找单词。查询的结果是该单词出现的次数，并列 出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行 一次。行号按升序显示。

要求：

```cpp
a. 它必须允许用户指明要处理的文件名字。
b. 程序将存储该文件的内容，以便输出每个单词所在的原始行。
提示：vector<string> lines;//O(1) 完美hash 或 map<int, string> lines;//O(logN)
c. 它必须将每一行分解为各个单词，并记录每个单词所在的所有行。 在输出行号时，应保证以升序输出，并且不重复。
提示：map<string, set<int> > word2Line;
d. 对特定单词的查询将返回出现该单词的所有行的行号。
e. 输出某单词所在的行文本时，程序必须能根据给定的行号从输入
文件中获取相应的行。
```

示例：
使用提供的文件内容，然后查找单词 "element"。输出的前几行为：
\---------------------------------------------
​ element occurs 125 times.
​ (line 62) element with a given key.
​ (line 64) second element with the same key.
​ (line 153) element |==| operator.
​ (line 250) the element type.
​ (line 398) corresponding element.

\---------------------------------------------

程序接口[可选]:

```cpp
class TextQuery
{
public:
    void readFile(const string filename);
    void query(const string & word);
private:
    //......
};
    			
//程序测试用例
int main(int argc, char *argv[])
{
    string  queryWord("hello");
    			   
    TextQuery tq;
    tq.readFile(argv[1]);
    tq.query(queryWord);			   
    return 0;
}
```

【答】

代码

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::set;
using std::string;
using std::istringstream;
using std::ifstream;
using std::ofstream;

class TextQuery
{
public:
    void readFile(const string filename)
    {
        ifstream ifs(filename);
        if(!ifs){
            cerr << "ifs open file error." << endl;
            return;
        }
        string line;
        while(getline(ifs, line)){
            lines.push_back(line);
        }
        ifs.close();
        int lineNum = 1;
        for(auto &line : lines){
            istringstream iss(line);
            string word;
            while(iss >> word){
                string newWord = dealWord(word);
                if(newWord != string()){
                    ++dict[newWord];
                    wordNumbers[newWord].insert(lineNum);
                }
            }
            ++lineNum;
        }
        ofstream ofs("query-dict.dat");
        if(!ofs){
            cerr << "ofs open file error." << endl;
            return;
        }
        map<string, int>::iterator it = dict.begin();
        for(; it != dict.end(); ++it){
            ofs << it->first << " "
                << it->second << endl;
        }
        ofs.close();
    }
private:
    string dealWord(string word)
    {
        for(size_t idx = 0; idx < word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();
            }
            if(isupper(word[idx])){
                word[idx] = tolower(word[idx]);
            }
        }
        return word;
    }
public:
    void query(const string &word)
    {
        cout << word << " occurs "
             << dict[word] << " times." << endl;
        for(auto &n : wordNumbers[word]){
            cout << "    (line " << n << ") ";
            cout << lines[n - 1] << endl;
        }
    }
private:
    vector<string> lines;//O(1)
    map<string, set<int>> wordNumbers;//the the
    map<string, int> dict;//
};

int main(int argc, char *argv[])
{
    string queryWord;
    cin >> queryWord;
    TextQuery tq;
    tq.readFile(argv[1]);
    tq.query(queryWord);
    return 0;
}
```

结果

```output
cs@cs-vm:~/code/cpp$ ./a.out china_daily.txt 
china
china occurs 2 times.
    (line 11) Stock Connect, said Gao Ting, chief China equities strategist at UBS Securities.
    (line 34) Zhao Wenli, an analyst at China Merchants Securities (HK) Co Ltd, said in a 
cs@cs-vm:~/code/cpp$ 
```

### 6. 一个类有几张虚函数表？请详细说明

【答】**虚函数表（虚表）可以理解为是一个数组，存放的是一个个虚函数的地址**

一个类可以没有虚函数表（没有虚函数就没有虚函数表）；

可以有一张虚函数表（<font color=red>**即使这个类有多个虚函数，将这些虚函数的地址都存在虚函数表中**</font>）；

也可以有多张虚函数表（继承多个有虚函数的基类）

### 7. 带虚函数的单继承结构下，虚函数地址的存放规则是怎样？请用代码验证

【答】



### 8. 带虚函数的多继承结构下，虚函数地址的存放规则是怎样？

【答】



### 9. 使用函数模板实现两个整数类型数据相加、两个double型数据相加、两个存放int型元素的set融合、两个C风格字符串拼接。



### 总结



## 1014 C++基础篇之移动语义

### 1. 利用可变模板参数实现一个函数模板，用来计算多个整型、浮点型数据的加法，返回类型为double





### 2. 什么是右值引用？C++11为什么要引入右值引用？

【答】

```cpp
右值引用只能绑定右值
int && r_ref = 10;
int && r_ref2 = a; //error
```





### 3. std::move函数的作用是什么？

【答】std::move函数的作用是显式的将一个左值转换为右值，<span style=color:red;background:yellow>**其实现本质上就是一个强制转换**</span>。当将一个左值显式转换为右值后，原来的左值对象就无法正常工作了，必须要重新赋值才可以继续使用。

### 4. 为采用深拷贝方式实现的String类添加移动构造函数和移动赋值运算符函数，并进行测试。

String(String &&rhs);

String & operator=(String &&rhs);

【答】



### 5. 使用类模板模拟RAII的思想，使其管理堆上的Computer资源

【答】



### 总结



## 1015 C++基础篇之智能指针

### 1. C++提供了哪几种智能指针，其各自的特点是什么？请通过代码进行练习、验证。

【答】c++11提供了以下几种智能指针，位于头文件&lt;memory&gt;，它们都是类模板。

```cpp
//std::auto_ptr      c++0x
//std::unique_ptr    c++11
//std::shared_ptr    c++11
//std::weak_ptr      c++11
```

特点：

**auto_ptr**是最简单的智能指针，使用上存在缺陷，已经被C++17弃用了。

**unique_ptr**对auto_ptr进行了改进。

**特点1：不允许复制或者赋值**

具备对象语义。

**特点2：独享所有权的智能指针**

将auto_ptr的缺陷摒弃了，具有对象语义，语法层面不允许复制、赋值。

**特点3：作为容器元素**

要利用**移动语义**的特点，可以直接传递unique_ptr的右值作为容器的元素。如果传入左值形态的unique_ptr，会进行复制操作，而unique_ptr是不能复制的。

**shared_ptr**

**特征1：共享所有权的智能指针**

可以使用**引用计数**记录对象的个数。

**特征2：可以进行复制或者赋值**

表明具备值语义。

**特征3：也可以作为容器的元素**

作为容器元素的时候，即可以传递左值，也可以传递右值。（区别于unique_ptr只能传右值）

**特征4：也具备移动语义**

表明也有移动构造函数与移动赋值函数。

**weak_ptr**是弱引用的智能指针，它是shared_ptr的一个补充，使用它进行复制或者赋值时，并不会导致引用计数加1，是为了解决shared_ptr的问题而诞生的。

weak_ptr知道所托管的对象是否还存活，如果存活，必须要提升为shared_ptr才能对资源进行访问，不能直接访问。

### 2. unique_ptr和shared_ptr需要注意哪些误用的情况，应该如何解决（避免），请通过代码进行说明。





### 3. 理解shared_ptr的循环引用问题（面试容易问到），掌握解决的方法，通过代码验证

【答】

解决方法：

——循环引用的解法，将Parent类或Child类中的任意一个shared_ptr换成weak_ptr类型的智能指针。

比如：将Parent类中的shared_ptr类型指针换成weak_ptr。

栈上的childPtr对象先销毁，会使堆上的Child对象的引用计数减1，因为这个Child对象的引用计数本来就是1，所以减为了0，回收这个Child对象，造成堆上的Parent对象的引用计数也减1,；

再当parentPtr销毁时，会再让堆上的Parent对象的引用计数减1，所以也能够回收。





### 总结

## 1016 C++基础篇之标准模板库01

### 1. 实现C++ primer 15.9中的文本查询扩展的作业，可以查某个单词在某行出现、某个单词在某行没有出现、某两个单词在某行出现、某两个单词至少有一个出现、三个单词的查询等等。(即实现查询单词的与、或、非操作)

【答】



### 2. STL包括哪些组件？各自具有哪些特点？

【答】

1. 容器：用来存放数据的。将其成为数据结构。

2. 迭代器：看成是一种广义的指针。可以用来访问容器中的元素。

3. 适配器：起到适配的作用。

4. 算法：普通函数。

5. 函数对象（仿函数）：做定制化操作。

6. 空间配置器：对空间进行申请与释放。（使用 + 原理 + 源码）

### 3. STL中的容器包括哪些？各自具有哪些特点？

【答】

（1）序列式容器   vector、deque、list

vector、deque、list三者的初始化、遍历、尾部插入与删除、头部插入与删除(deque、list)(这里要讲vector与deque的底层实现)、中间插入insert(vector、deque会有失效)、清空元素、list的特殊操作(sort、merge、splice、unique、reverse)。

（2）关联式容器  set、map

(set、multiset、map、multimap)：底层实现使用红黑树。初始化、遍历、查找(count,find)、插入(insert)(set与map需要判断插入是不是成功)，自定义类型需要去对Compare进行改写(std::less、std::greater、函数对象)。

（3）无序关联式容器  unordered_set、unordered_map

无序关联式容器的底层实现使用的是哈希表，关于哈希表有几个概念需要了解：哈希函数、哈希冲突、解决哈希冲突的方法、装载因子(装填因子、负载因子)

（4）容器适配器 priority_queue

优先级队列默认使用std::less,但是体现出来是一个大根堆。

### 4. 序列式容器包括哪些？他们之间有哪些异同？

【答】vector、deque、list

vector不支持在头部进行插入与删除 ==> 探讨vector的**底层实现**，三个指针：

_M_start：指向第一个元素的位置

_M_finish：指向最后一个元素的下一个位置

_M_end_of_storage：指向当前分配空间的最后一个位置的下一个位置。

![image-20240806004327532](D:/GitHub/Linux-Cpp-Development/docs/cppbase2-image/image-20240806004327532.png)

探索deque的**底层实现**：

物理上是不连续的，逻辑上是连续的。中控器数组、多个连续的小片段、迭代器是一个类。

中控器数组是一个二级指针，包括中控器的大小。

小片段内部是连续的，但是片段与片段之间是不连续的。

迭代器是一个类，deque有两个迭代器指针，一个指向第一个小片段，一个指向最后一个小片段。

### 5. 创建和初始化vector的方法，每种都给出一个实例？当然也可以把deque与list写出来

【答】

**vector**

（1）**默认构造**：创建一个空的`vector`。

```cpp
cpp复制代码

std::vector<int> vec1; // 空的vector
```

（2）**指定大小的构造**：创建一个指定大小的`vector`，元素使用默认值初始化（对于内置类型如int，默认值为0）。

```cpp
cpp复制代码

std::vector<int> vec2(10); // 包含10个0的vector
```

（3）**使用指定值初始化**：创建一个指定大小并用特定值初始化的`vector`。

```cpp
cpp复制代码

std::vector<int> vec3(10, 5); // 包含10个5的vector
```

（4）**使用迭代器初始化**：从另一个容器或数组的一部分复制元素。

```cpp
int arr[] = {1, 2, 3, 4, 5};  
std::vector<int> vec4(arr, arr + 5); // 包含arr中5个元素的vector
```

（5）**列表初始化**（C++11及以后）：

```cpp
cpp复制代码

std::vector<int> vec5 = {1, 2, 3, 4, 5}; // 使用花括号初始化
```

**deque**

`deque`（双端队列）的构造和初始化方法与`vector`非常相似：

（1）**默认构造**：

```cpp
cpp复制代码

std::deque<int> deq1; // 空的deque
```

（2）**指定大小的构造**：

```cpp
cpp复制代码

std::deque<int> deq2(10); // 包含10个0的deque
```

（3）**使用指定值初始化**：

```cpp
cpp复制代码

std::deque<int> deq3(10, 5); // 包含10个5的deque
```

（4）**使用迭代器初始化**：

```cpp
int arr[] = {1, 2, 3, 4, 5};  
std::deque<int> deq4(arr, arr + 5); // 包含arr中5个元素的deque
```

（5）**列表初始化**：

```cpp
cpp复制代码

std::deque<int> deq5 = {1, 2, 3, 4, 5}; // 使用花括号初始化
```

**list**

`list`（链表）的构造和初始化也类似：

（1）**默认构造**：

```cpp
cpp复制代码

std::list<int> lst1; // 空的list
```

（2）**使用指定值初始化多个元素**（注意：`list`没有直接指定大小的构造函数，但可以通过插入操作添加多个元素）：

```cpp
std::list<int> lst2(10, 5); // 错误！list没有这样的构造函数  
// 但可以这样做：  
std::list<int> lst2a;  
for (int i = 0; i < 10; ++i) {  
    lst2a.push_back(5); // 插入10个5  
}
```

（3）**使用迭代器初始化**（通常用于复制另一个容器或数组的元素）：

```cpp
int arr[] = {1, 2, 3, 4, 5};  
std::list<int> lst3(arr, arr + 5); // 错误！list没有这样的构造函数  
// 但可以这样做：  
std::list<int> lst3a(arr, arr + 5); // 使用std::initializer_list构造函数（C++11起）  
// 或者  
std::list<int> lst3b;  
for (int i : arr) {  
    lst3b.push_back(i); // 插入arr中的元素  
}
```

（4）**列表初始化**：

```cpp
cpp复制代码

std::list<int> lst4 = {1, 2, 3, 4, 5}; // 使用花括号初始化
```

### 总结

- 

## 1017 C++基础篇之标准模板库02

### 1. 下面程序有什么错误？

```cpp
list<int> lst; 
list<int>::iterator iter1 = lst.begin(), iter2 = lst.end(); 
while(iter1 < iter2)
{    
     //....
}
```

【答】

```txt
【文心一言】
在 C++ 的标准库中，std::list 是一个双向链表，它不支持像 std::vector 那样的随机访问迭代器。因此，你不能直接使用 < 或 > 操作符来比较 std::list 的迭代器，因为这些操作符是为随机访问迭代器（如 std::vector 的迭代器）设计的。

对于 std::list，你需要使用 != 来检查迭代器是否不相等，即它们是否指向不同的元素。如果你想要遍历整个 std::list，你应该从 begin() 迭代器开始，直到它等于 end() 迭代器。
```



### 2. 如果c1与c2是两个容器，下面的比较操作有什么限制？if(c1 < c2)

【答】

```txt
【参考：文心一言】
可以用于std::vector、std::deque等支持随机访问的容器，不能用于std::list、std::forward_list等不支持随机访问的容器，否则编译报错。
```



### 3. 使用模板实现一个快速排序算法

```cpp
template<typename T,typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size, Compare com);     
    void quick(int left, int right, Compare &com);     
    int partition(int left, int right, Compare &com);     
    void print(); 
private:    
    vector<T> _vec; 
};
```

【答】





### 总结



## 1018 C++基础篇之标准模板库03

### 1. 使用模板实现一个堆排序算法。

使用模板的框架如下：

```cpp
template <typename T, typename Compare = std::less<T>> 
class HeapSort 
{ 
public:  
    HeapSort(T *arr, size_t size);  
    void heapAdjust(size_t ,size_t);  
    void sort();
    void print();  
private:  
    vector<T> _vec;
    Compare _cmp;
};
```

【答】



### 2. 关联式容器有哪些？各自具有哪些特点？（熟悉基本操作）

【答】map





### 3. 无序关联式容器有哪些？各自具有哪些特点？

【答】



### 4. 使用map重写词频统计作业。（之前使用的vector，可以比较他们的速率）

【答】





### 总结



## 1019 C++基础篇之标准模板库04

### 1. 使用unordered_map重写词频统计作业。再比较一下使用map和vector时所花费的时间，体会这几种容器的区别。

【答】

代码：

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::unordered_map;

struct Record
{
    Record(string w, int f) : _word(w), _frequency(f){}
	string _word;
	int _frequency;
};

bool operator<(const Record &lhs, const Record &rhs)
{
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs){
            cerr << "ifs open file error." << endl;
            return;
        }
        string line;
        while(getline(ifs, line)){
            istringstream iss(line);
            string word;
            while(ifs >> word){
                string newWord = dealWord(word);
                if(newWord != string()){
                    ++_dict[newWord];
                }
            }
        }
        ifs.close();
        for(auto &n : _dict){
            _dict2.push_back(Record(n.first, n.second));
        }
        sort(_dict2.begin(), _dict2.end());
    }
private:
    string dealWord(string word)
    {
        for(size_t idx = 0; idx != word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();
            }
        }
        return word;
    }
public:
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs){
            cerr << "ofs open file error." << endl;
            return;
        }
        for(size_t idx = 0; idx != _dict2.size(); ++idx){
            ofs << _dict2[idx]._word << " "
                << _dict2[idx]._frequency << endl;
        }
        ofs.close();
    }
private:
    unordered_map<string, int> _dict;
    vector<Record> _dict2;
};

void test()
{
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dict-unordered_map.dat");
}

int main()
{
    test();
    return 0;
}
```



### 2. 使用unordered_map/map实现单词转换程序。

给定一个string，将它转换为另一个string。程序的输入是两个文件，第一个文件保存的是一些规则，用来转换第二个文件中的文本。每条规则由两部分组成：一个可能出现在输入文件中的单词和一个用来替换它的短语。表达的含义是，每当第一个单词出现在输入中时，我们就将它替换为对应的短语，第二个输入文件包含要转换的文本。（C++ primer 11.3.6）

提示：

规则文件：map.txt文件，其实就是第一个单词，被后面的一串所替换。

待转换文本：file.txt文件，该文件中的单词如果出现在map.txt文件的第一个单词的话，就用map.txt的后面一串替代。

结果：最后结果其实就是，将file.txt文件中的并且出现在map.txt中第一个单词转换为map.txt后面的一串。例如：where r u的输出结果就是where are you. r替换为are，u替换为you

```text
//file.txt
where r u
y dont u send me a pic
k thk l8r
```

```text
//map.txt
brb be right back
k okay?
y why
r are
u you
pic picture
thk thanks!
l8r later
```

【答】

代码：

结果：



### 3. Leetcode 146 LURCache的实现

https://leetcode-cn.com/problems/lru-cache/

请你设计并实现一个满足 LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

【答】

代码：



结果：



### 总结





## 1020 C++基础篇之标准模板库05

### 1. 容器、迭代器、算法之间的关系是怎样的？他们是如何结合在一起的？





### 2. 什么是迭代器失效问题？该问题是如何产生的？怎样避免产生迭代器失效问题



### 3. Leetcode 127题

https://leetcode-cn.com/problems/word-ladder/

字典 wordList 中从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：

每一对相邻的单词只差一个字母。
 对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
sk == endWord
给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0 。

【答】

代码：

结果：



### 总结

- 

## 1021 C++基础篇之标准模板库06

### 1. 阅读源码：结合STL中std::allocator的源码阅读《STL源码剖析》的第二章内容





### 2. 了解std::allocator的用法之后,实现自定义的Vector类

接口形式：

```c++
template<typename T> 
class Vector 
{ 
public:     
    Vector();     
    ~Vector();          
    void push_back(const T &);      
    void pop_back();         
    int size();     
    int capacity(); 
private:     
    void reallocate();//重新分配内存,动态扩容要用的 
private:         
    static std::allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};

     
 Vector模型
 ______________________________
 |_|_|_|_|_|____________________|
 ↑          ↑                    ↑
 _start   _finish            _end_of_storage
```

答：





### 3. 什么是回调函数，注册回调函数，执行回调函数？(掌握std::bind用法,非常重要)

std::bind的实现原理阅读材料

http://www.cnblogs.com/xusd-null/p/3698969.html
https://www.tuicool.com/articles/iMZ7ba



### 总结

- 

## 1022 C++基础篇之标准模板库07

### 1. HDU：拯救

```c++
拯救 -- 考虑使用优先级队列来做 http://acm.hdu.edu.cn/showproblem.php?pid=1242

公主被恶人抓走，被关押在牢房的某个地方。牢房用N*M (N, M <= 200)的矩阵来表示。矩阵中的每项可以代表道路（@）、墙壁（#）、和守卫（x）。
英勇的骑士（r）决定孤身一人去拯救公主（a）。我们假设拯救成功的表示是“骑士到达了公主所在的位置”。由于在通往公主所在位置的道路中可能遇到守卫，骑士一旦遇到守卫，必须杀死守卫才能继续前进。
现假设骑士可以向上、下、左、右四个方向移动，每移动一个位置需要1个单位时间，杀死一个守卫需要花费额外的1个单位时间。同时假设骑士足够强壮，有能力杀死所有的守卫。

给定牢房矩阵，公主、骑士和守卫在矩阵中的位置，请你计算拯救行动成功需要花费最短时间。

Input
第一行为一个整数S，表示输入的数据的组数（多组输入）
随后有S组数据，每组数据按如下格式输入
1、两个整数代表N和M, (N, M <= 200).
2、随后N行，每行有M个字符。"@"代表道路，"a"代表公主，"r"代表骑士，"x"代表守卫, "#“代表墙壁。
Output
如果拯救行动成功，输出一个整数，表示行动的最短时间。
如果不可能成功，输出"Impossible”
Sample Input
2
7 8
#@#####@
#@a#@@r@
#@@#x@@@
@@#@@#@#
#@@@##@@
@#@@@@@@
@@@@@@@@
13 40
@x@@##x@#x@x#xxxx##@#x@x@@#x#@#x#@@x@#@x
xx###x@x#@@##xx@@@#@x@@#x@xxx@@#x@#x@@x@
#@x#@x#x#@@##@@x#@xx#xxx@@x##@@@#@x@@x@x
@##x@@@x#xx#@@#xxxx#@@x@x@#@x@@@x@#@#x@#
@#xxxxx##@@x##x@xxx@@#x@x####@@@x#x##@#@
#xxx#@#x##xxxx@@#xx@@@x@xxx#@#xxx@x#####
#x@xxxx#@x@@@@##@x#xx#xxx@#xx#@#####x#@x
xx##@#@x##x##x#@x#@a#xx@##@#@##xx@#@@x@x
x#x#@x@#x#@##@xrx@x#xxxx@##x##xx#@#x@xx@
#x@@#@###x##x@x#@@#@@x@x@@xx@@@@##@@x@@x
x#xx@x###@xxx#@#x#@@###@#@##@x#@x@#@@#@@
#@#x@x#x#x###@x@@xxx####x@x##@x####xx#@x
#x#@x#x######@@#x@#xxxx#xx@@@#xx#x#####@
Sample Output
13
7
```

答：



### 2. Leetcode 20题

https://leetcode-cn.com/problems/valid-parentheses/

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。

【答】

代码：

结果：



### 总结

- 



















































