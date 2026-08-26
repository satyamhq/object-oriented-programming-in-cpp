#include<iostream>
using namespace std;

class Employees {
    public:
    static int employeeID;
    static int companyCode;
        Employees() {
            employeeID++;
        }
        void display() {
            cout << "Employee ID: " << employeeID << endl;
            cout << "Company Code: " << companyCode << endl;
        }
};

int Employees::employeeID = 0;
int Employees::companyCode = 1234;