#include <iostream>
using namespace std;

class rectangle_area {
public:
    int length;
    int breadth;

    int area() {
        return length * breadth;
    }
};

int main() {
    rectangle_area rectangle1;

    rectangle1.length = 5;
    rectangle1.breadth = 10;

    cout << "Area of rectangle: " << rectangle1.area() << endl;

    return 0;
}