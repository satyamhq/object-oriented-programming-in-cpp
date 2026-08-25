#include <iostream>
using namespace std;

union Employee {
    string name;
    int age;
    double salary;
};

int main() {
    Employee emp;

    emp.name = "Satyam";
    cout << "Name: " << emp.name << endl;

    emp.age = 20;
    cout << "Age: " << emp.age << endl;

    emp.salary = 50000;
    cout << "Salary: " << emp.salary << endl;

    return 0;
}