#include <iostream>
using namespace std;

class Bank {
public:
    static double interestRate;

    static void displayRate() {
        cout << "Interest rate of the bank: " << interestRate << "%";
    }
};  // semicolon required here

double Bank::interestRate = 7.5;

int main() {
    Bank::displayRate();
    return 0;
}