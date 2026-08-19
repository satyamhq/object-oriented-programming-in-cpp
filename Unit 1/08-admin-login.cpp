#include<iostream>
using namespace std;

int main(){
    int username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if(username == 12505700 && password == 123456789){
        cout << "Login successful!" << endl;
    }
    else{
        cout << "Invalid username or password." << endl;
    }

    return 0;
}