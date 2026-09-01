#include <iostream>
using namespace std;

class Number {
    int num;

public:
    // Constructor
    Number(int n) {
        num = n;
    }

    // Display function
    void display() {
        cout << "Number: " << num << endl;
    }

    // Friend function
    friend void findGreatest(Number n1, Number n2);
};

// Function to find the greatest number
void findGreatest(Number n1, Number n2) {
    if (n1.num > n2.num)
        cout << "The greatest number is: " << n1.num << endl;
    else if (n2.num > n1.num)
        cout << "The greatest number is: " << n2.num << endl;
    else
        cout << "Both numbers are equal." << endl;
}

int main() {
    int a, b;

    cout << "Enter first number: ";
    cin >> a;

    cout << "Enter second number: ";
    cin >> b;

    Number n1(a);
    Number n2(b);

    findGreatest(n1, n2);

    return 0;
}