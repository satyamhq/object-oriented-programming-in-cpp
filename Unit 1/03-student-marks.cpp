#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    int age;
    float marks1, marks2, marks3;

    cout << "Enter name: ";
    cin >> name;

    cout << "Enter age: ";
    cin >> age;

    cout << "Enter marks for subject 1: ";
    cin >> marks1;

    cout << "Enter marks for subject 2: ";
    cin >> marks2;

    cout << "Enter marks for subject 3: ";
    cin >> marks3;

    float avg = (marks1 + marks2 + marks3) / 3.0f;

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Marks1: " << marks1 << endl;
    cout << "Marks2: " << marks2 << endl;
    cout << "Marks3: " << marks3 << endl;
    cout << "Average marks is: " << avg << endl;

    return 0;
}