#include<iostream>
using namespace std;

class Student {
public:
    static int count; // static member variable to keep track of the number of students
    Student() {
        count++; // increment the count whenever a new student object is created
    }
};

int Student::count = 0; // initialize the static member variable
int main() {
    Student s1, s2, s3; // create three student objects

    cout << "Total number of students: " << Student::count << endl; // access the static member variable using the class name

    return 0;
}