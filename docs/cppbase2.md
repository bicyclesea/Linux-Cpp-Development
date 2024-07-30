# C++基础（2）

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

【答】

问题：

1. 成员名访问冲突的二义性

2. 存储二义性的问题（重要）

问题1：成员名访问冲突的二义性。

解决成员名访问冲突的方法：加类作用域（不推荐）—— 应该尽量避免。

同时，<span style=color:red;background:yellow>**如果D类中定义了同名的成员，可以对基类的这些成员造成隐藏效果**</span>，那么就可以直接通过成员名进行访问。

``` c++
    D d;
    d.A::print();
    d.B::print();
    d.C::print();
    d.print(); //ok
```

问题2：存储二义性的问题（重要）

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

构造函数包含两个参数，用来对name和age初始化。构建一个类Employee由Person派生，包含department（部门），实型数据成员salary（工资）,成员函数display（）用来输出职工姓名、年龄、部门、工资，其他成员根据需要自己设定。主函数中定义3个Employee类对象，内容自己设定，将其姓名、年龄、部门、工资输出。要求：用char*来保存字符串内容，并能实现Employee对象的复制、赋值操作。

【答】

派生类的访问权限如下：

1. 不管什么继承方式，派生类内部都不能访问基类的私有成员；
2. 不管什么继承方式，派生类内部除了基类的私有成员不可以访问，其他的都可以访问；
3. 不管什么继承方式，派生类对象在类外除了公有继承基类中的公有成员可以访问外，其他的都不能访问。

**(记忆：1.私有的成员在类外无法直接访问； 2.继承方式和基类成员访问权限做交集)**

代码：

```c++
##include <iostream>
##include <cstring>
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
##include <iostream>
##include <string>
##include <cmath>
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
##include <iostream>
##include <vector>
##include <map>
##include <set>
##include <string>
##include <sstream>
##include <cstring>
##include <fstream>
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
##include <iostream>
##include <string>
##include <vector>
##include <regex>
##include <fstream>
##include "tinyxml2.h"
##include "tinyxml2.cpp"
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
##include <iostream>
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
##include<iostream>

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
##include <iostream>
##include <vector>
##include <map>
##include <set>
##include <string>
##include <sstream>
##include <cstring>
##include <fstream>
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

1、容器：用来存放数据的。将其成为数据结构。

2、迭代器：看成是一种广义的指针。可以用来访问容器中的元素。

3、适配器：起到适配的作用。

4、算法：普通函数。

5、函数对象（仿函数）：做定制化操作。

6、空间配置器：对空间进行申请与释放。（使用 + 原理 + 源码）

### 3. STL中的容器包括哪些？各自具有哪些特点？

【答】

- 序列式容器   vector、list
- 关联式容器  set、map
- 无序关联式容器  unordered_set、unordered_map

### 4. 序列式容器包括哪些？他们之间有哪些异同？

【答】vector、list



### 5. 创建和初始化vector的方法，每种都给出一个实例？当然也可以把deque与list写出来

【答】初始化的方法：创建无参对象、count个value、迭代器范围、大括号、拷贝或者移动。三种容器的初始化方式是一样的。



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



### 2. 如果c1与c2是两个容器，下面的比较操作有什么限制？if(c1 < c2)

【答】



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
##include <iostream>
##include <string>
##include <vector>
##include <fstream>
##include <sstream>
##include <unordered_map>
##include <algorithm>
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



## 1022 C++基础篇之标准模板库07

### 1. HDU：拯救

```c++
拯救 -- 考虑使用优先级队列来做 http://acm.hdu.edu.cn/showproblem.php?pid=1242

公主被恶人抓走，被关押在牢房的某个地方。牢房用N*M (N, M <= 200)的矩阵来表示。矩阵中的每项可以代表道路（@）、墙壁（##）、和守卫（x）。
英勇的骑士（r）决定孤身一人去拯救公主（a）。我们假设拯救成功的表示是“骑士到达了公主所在的位置”。由于在通往公主所在位置的道路中可能遇到守卫，骑士一旦遇到守卫，必须杀死守卫才能继续前进。
现假设骑士可以向上、下、左、右四个方向移动，每移动一个位置需要1个单位时间，杀死一个守卫需要花费额外的1个单位时间。同时假设骑士足够强壮，有能力杀死所有的守卫。

给定牢房矩阵，公主、骑士和守卫在矩阵中的位置，请你计算拯救行动成功需要花费最短时间。

Input
第一行为一个整数S，表示输入的数据的组数（多组输入）
随后有S组数据，每组数据按如下格式输入
1、两个整数代表N和M, (N, M <= 200).
2、随后N行，每行有M个字符。"@"代表道路，"a"代表公主，"r"代表骑士，"x"代表守卫, "##“代表墙壁。
Output
如果拯救行动成功，输出一个整数，表示行动的最短时间。
如果不可能成功，输出"Impossible”
Sample Input
2
7 8
##@########@
##@a##@@r@
##@@##x@@@
@@##@@##@##
##@@@###@@
@##@@@@@@
@@@@@@@@
13 40
@x@@###x@##x@x##xxxx###@##x@x@@##x##@##x##@@x@##@x
xx#####x@x##@@###xx@@@##@x@@##x@xxx@@##x@##x@@x@
##@x##@x##x##@@###@@x##@xx##xxx@@x###@@@##@x@@x@x
@###x@@@x##xx##@@##xxxx##@@x@x@##@x@@@x@##@##x@##
@##xxxxx###@@x###x@xxx@@##x@x######@@@x##x###@##@
##xxx##@##x###xxxx@@##xx@@@x@xxx##@##xxx@x########
##x@xxxx##@x@@@@###@x##xx##xxx@##xx##@########x##@x
xx###@##@x###x###x##@x##@a##xx@###@##@###xx@##@@x@x
x##x##@x@##x##@###@xrx@x##xxxx@###x###xx##@##x@xx@
##x@@##@#####x###x@x##@@##@@x@x@@xx@@@@###@@x@@x
x##xx@x#####@xxx##@##x##@@#####@##@###@x##@x@##@@##@@
##@##x@x##x##x#####@x@@xxx######x@x###@x######xx##@x
##x##@x##x#########@@##x@##xxxx##xx@@@##xx##x########@
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











































