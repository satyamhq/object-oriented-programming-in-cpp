#include <iostream>
using namespace std;

long long factorialIterative(int n) {
    long long result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

long long factorialRecursive(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * factorialRecursive(n - 1);
}

int main() {
    int n;

    cout << "Enter a non-negative number: ";
    cin >> n;

    if (n < 0) {
        cout << "Factorial is not defined for negative numbers." << endl;
        return 1;
    }

    cout << "Iterative factorial: "
         << factorialIterative(n) << endl;

    cout << "Recursive factorial: "
         << factorialRecursive(n) << endl;

    return 0;
}