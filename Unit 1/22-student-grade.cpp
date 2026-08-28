#include <iostream>
#include <iomanip>
using namespace std;

inline float calculateAverage(float total, int subjects) {
    return total / subjects;
}

char findGrade(float average, float passMarks = 40) {
    if (average < passMarks)
        return 'F';
    else if (average < 60)
        return 'D';
    else if (average < 70)
        return 'C';
    else if (average < 80)
        return 'B';
    else
        return 'A';
}

int main() {
    string name;
    float marks1, marks2, marks3;
    float total, average;
    char grade;

    // Input
    cout << "Enter student name: ";
    cin >> name;

    cout << "Enter marks for Subject 1: ";
    cin >> marks1;

    cout << "Enter marks for Subject 2: ";
    cin >> marks2;

    cout << "Enter marks for Subject 3: ";
    cin >> marks3;

    // Calculate total
    total = marks1 + marks2 + marks3;

    // Calculate average
    average = calculateAverage(total, 3);

    // Find grade
    grade = findGrade(average);

    // Display result
    cout << "\n";
    cout << left << setw(15) << "Student Name" << " : " << name << endl;
    cout << left << setw(15) << "Subject 1" << " : " << marks1 << endl;
    cout << left << setw(15) << "Subject 2" << " : " << marks2 << endl;
    cout << left << setw(15) << "Subject 3" << " : " << marks3 << endl;
    cout << left << setw(15) << "Total Marks" << " : " << total << endl;
    cout << left << setw(15) << "Average" << " : "
         << fixed << setprecision(2) << average << endl;
    cout << left << setw(15) << "Grade" << " : " << grade << endl;

    return 0;
}
