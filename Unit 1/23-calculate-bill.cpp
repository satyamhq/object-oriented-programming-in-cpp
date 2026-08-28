#include <iostream>
#include <iomanip>
using namespace std;

float calculateBill(float units) {
    float bill;

    if (units <= 100)
        bill = units * 5;
    else if (units <= 200)
        bill = (100 * 5) + ((units - 100) * 7);
    else
        bill = (100 * 5) + (100 * 7) + ((units - 200) * 10);

    return bill;
}

int main() {
    string name;
    float units, bill;

    cout << "Enter customer name: ";
    cin >> name;

    cout << "Enter electricity units consumed: ";
    cin >> units;

    bill = calculateBill(units);

    cout << "\n";
    cout << left << setw(20) << "Customer Name" << " : " << name << endl;
    cout << left << setw(20) << "Units Consumed" << " : " << units << endl;
    cout << left << setw(20) << "Electricity Bill" << " : Rs. "
         << fixed << setprecision(2) << bill << endl;

    return 0;
}
