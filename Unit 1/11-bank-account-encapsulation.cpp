#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance = 0;

public:
    string name;

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!" << endl;
        } else if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        }
    }
};

int main() {
    BankAccount account1;

    account1.name = "Satyam Kumar";

    account1.deposit(1000);
    account1.withdraw(300);
    account1.withdraw(800); // Insufficient balance

    return 0;
}