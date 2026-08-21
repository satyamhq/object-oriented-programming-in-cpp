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
};

int main() {
    BankAccount account1;

    account1.name = "Satyam Kumar";

    account1.deposit(1000);
    account1.deposit(-500); // Invalid deposit

    return 0;
}