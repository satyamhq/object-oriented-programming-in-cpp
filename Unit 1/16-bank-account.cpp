#include <iostream>
using namespace std;

class Bank {
public:
    string name;
    double balance;

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient balance!" << endl;
    }
};

int main() {
    Bank b;

    b.name = "Satyam";
    b.balance = 5000;

    b.deposit(2000);
    b.withdraw(1000);

    cout << "Name: " << b.name << endl;
    cout << "Balance: " << b.balance << endl;

    return 0;
}