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

