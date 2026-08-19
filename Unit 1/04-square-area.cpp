#include <iostream>
using namespace std;

int main(){
    int squre_area;
    int size_of_square;

    cout << "Enter the size of the square: ";
    cin >> size_of_square;

    squre_area = size_of_square * size_of_square;

    cout << "The area of the square is: " << squre_area << endl;

    return 0;
}