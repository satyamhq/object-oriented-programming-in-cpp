#include <iostream>
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

// Define and initialize static variables
int Employees::employeeID = 0;
int Employees::companyCode = 1001;

int main() {
    Employees e1;
    e1.display();

    Employees e2;
    e2.display();

    Employees e3;
    e3.display();

    return 0;
}
