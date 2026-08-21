#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int marks;
};

int main() {
    Student students[3];

    // Input
    for (int i = 0; i < 3; i++) {
        cout << "Enter student name: ";
        cin >> students[i].name;

        cout << "Enter marks: ";
        cin >> students[i].marks;
    }

    // Display name and marks in one line
    cout << "\nStudents and Marks:\n";

    for (int i = 0; i < 3; i++) {
        cout << students[i].name << " - " << students[i].marks << endl;
    }

    // Find highest marks
    int highest = 0;
    int highestIndex = 0;

    for (int i = 0; i < 3; i++) {
        if (students[i].marks > highest) {
            highest = students[i].marks;
            highestIndex = i;
        }
    }

    cout << "\nHighest Marks: "
         << students[highestIndex].name
         << " - " << students[highestIndex].marks << endl;

    return 0;
}