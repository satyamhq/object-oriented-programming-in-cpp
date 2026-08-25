#include <iostream>
using namespace std;

struct TrafficLight {
    int red = 1;
    int yellow = 2;
    int green = 3;
};

int main() {
    TrafficLight light;
    
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Stop! The signal is red." << endl;
            break;

        case 2:
            cout << "Wait! The signal is yellow." << endl;
            break;

        case 3:
            cout << "Go! The signal is green." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}