#include<iostream>
using namespace std;
void findValues(int a, int b, int c, int*largest, int*smallest) {
    *largest = a;
    *smallest = a;

    if (b > *largest) {
        *largest = b;
    }
    if (c > *largest) {
        *largest = c;
    }

    if (b < *smallest) {
        *smallest = b;
    }
    if (c < *smallest) {
        *smallest = c;
    }
}
int main() {
    int num1, num2, num3;
    int largest, smallest;

    cout << "Enter three numbers: ";
    cin >> num1 >> num2 >> num3;

    findValues(num1, num2, num3, &largest, &smallest);

    cout << "Largest number: " << largest << endl;
    cout << "Smallest number: " << smallest << endl;

    return 0;
}