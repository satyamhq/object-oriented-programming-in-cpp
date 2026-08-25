#include<iostream>
using namespace std;

struct Student {
    string name;
    int age;
    float marks1;
    float marks2;
    float marks3;
};

int main(){
    Student students[3];

    // Input
    for(int i=0; i<3; i++){
        cout << "Enter student name: ";
        cin >> students[i].name;

        cout << "Enter age: ";
        cin >> students[i].age;

        cout << "Enter marks for subject 1: ";
        cin >> students[i].marks1;

        cout << "Enter marks for subject 2: ";
        cin >> students[i].marks2;

        cout << "Enter marks for subject 3: ";
        cin >> students[i].marks3;
    }

    // Display name, age, and marks in one line
    cout << "\nStudents Details:\n";
    for(int i=0; i<3; i++){
        cout << students[i].name << " - Age: " << students[i].age 
             << ", Marks: " << students[i].marks1 
             << ", " << students[i].marks2 
             << ", " << students[i].marks3 << endl;
    }

    return 0;
}