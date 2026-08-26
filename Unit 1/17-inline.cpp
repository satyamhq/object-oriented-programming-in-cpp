#include <iostream>
using namespace std;

inline int square(int n){   // inline function only for small functions to reduce function call overhead
    return n * n;
}
int main(){
    int num;
    cout << "Enter a number: ";
    cin >> num;

    int result = square(num);
    cout << "The square of " << num << " is: " << result << endl;

    return 0;
}