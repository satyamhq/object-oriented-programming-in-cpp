#include<iostream>
using namespace std;

int main(){
    float length, width;
    float area, perimeter;

    cout << "Enter the length of the rectangle: ";
    cin >> length;

    cout << "Enter the width of the rectangle: ";
    cin >> width;

    area = length * width;
    perimeter = 2 * (length + width);

    cout << "The area of the rectangle is: " << area << endl;
    cout << "The perimeter of the rectangle is: " << perimeter << endl;

    return 0;
}