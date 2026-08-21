#include<iostream>
using namespace std;

class studnet {
    public:
    string name;
    int age;
    string gender;

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
    }
};

int main() {
    studnet student1;
    student1.name = "John Doe";
    student1.age = 20;
    student1.gender = "Male";
    student1.displayInfo();
    return 0;
}