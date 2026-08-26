#include <iostream>
using namespace std;

inline int greaterNumber(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int num1, num2;

    cout << "Enter the first number: ";
    cin >> num1;

    cout << "Enter the second number: ";
    cin >> num2;

    int result = greaterNumber(num1, num2);
    cout << "The greater number is: " << result << endl;

    return 0;
}