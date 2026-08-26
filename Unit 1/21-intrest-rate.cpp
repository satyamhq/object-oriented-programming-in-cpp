#include<iostream>
using namespace std;
class Bank{
    public:
    static double interestRate; // static member variable to hold the interest rate
    static void displayRate(){
        cout << "Intrest rate of the bank:" << interestRate << "%";
    }
}

double Bank::interestRate = 7.5;
int main(){
    Bank::displayRate();
}
