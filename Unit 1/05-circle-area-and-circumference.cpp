#include<iostream>
#include<cmath>
using namespace std;

int main(){
    float radius;
    float area;
    float circumference;

    cout << "Enter the radius of the circle: ";
    cin >> radius;

    area = M_PI * radius * radius;
    circumference = 2 * M_PI * radius;

    cout << "The area of the circle is: " << area << endl;
    cout << "The circumference of the circle is: " << circumference << endl;

    return 0;
}