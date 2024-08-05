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

