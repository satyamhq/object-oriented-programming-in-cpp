#include <iostream>
using namespace std;

void Calculate(int m1, int m2, int m3, int &total, double &average) {
    total = m1 + m2 + m3;
    average = total / 3.0;
}

char findGrade(double average) {
    if (average >= 90)
        return 'A';
    else if (average >= 80)
        return 'B';
    else if (average >= 70)
        return 'C';
    else if (average >= 60)
        return 'D';
    else
        return 'F';
}

int main() {
    int m1, m2, m3, total;
    double average;

    cout << "Enter three marks: ";
    cin >> m1 >> m2 >> m3;

    Calculate(m1, m2, m3, total, average);

    cout << "Total Marks: " << total << endl;
    cout << "Average Marks: " << average << endl;
    cout << "Grade: " << findGrade(average) << endl;

    return 0;
}