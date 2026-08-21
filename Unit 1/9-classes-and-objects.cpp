// Class = Blueprint
// Object = Real instance created from the blueprint

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
    student1.name = "Satyam Kumar";
    student1.age = 18;
    student1.gender = "Male";
    student1.displayInfo();
    return 0;
}