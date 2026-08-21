# CSE202 — Object Oriented Programming
## UNIT II: Pointers, Reference Variables, Arrays and String Concepts

---

### 1. Void Pointer

A `void*` is a **generic pointer** that can hold the address of any data type but cannot be dereferenced directly (it must first be **type-cast** to a specific pointer type).

```cpp
int i = 10;
float f = 3.14;
void *ptr;

ptr = &i;
cout << *(int*)ptr;      // must cast before dereferencing
ptr = &f;
cout << *(float*)ptr;
```

### 2. Pointer Arithmetic

Only certain operations are valid on pointers: `++`, `--`, `+n`, `-n`, and subtracting two pointers of the same type. Adding an integer `n` to a pointer moves it forward by `n * sizeof(type)` bytes.

```cpp
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;          // p points to arr[0]
cout << *p << endl;      // 10
p++;                       // now points to arr[1]
cout << *p << endl;      // 20
cout << *(p + 2) << endl; // arr[3] = 40
```

### 3. Pointer to Pointer

A pointer that stores the address of another pointer (double indirection).

```cpp
int x = 5;
int *p = &x;
int **pp = &p;   // pointer to pointer

cout << **pp;      // dereference twice -> 5
```

### 4. Problems with Pointers

| Problem | Description | Fix |
|---|---|---|
| **Dangling pointer** | Points to memory that has been freed/deallocated (or to a local variable that has gone out of scope) | Set pointer to `nullptr` after `delete` |
| **Wild pointer** | Declared but not initialized — contains a garbage address | Always initialize pointers |
| **Null pointer assignment** | Dereferencing a `nullptr` causes undefined behavior/crash | Check `if (p != nullptr)` before dereferencing |

```cpp
int *p1;                 // wild pointer (uninitialized)

int *p2 = new int(5);
delete p2;                // memory freed
// *p2 is now dangling — undefined behavior
p2 = nullptr;              // safe practice

int *p3 = nullptr;
if (p3) cout << *p3;      // guarded — avoids null pointer dereference
```

### 5. Classes Containing Pointers & Pointer to Objects

When a class contains a pointer member (e.g., for dynamically allocated memory), special care is needed for copy constructor/destructor (see Unit III — **deep copy** vs **shallow copy**).

```cpp
class Box {
    int *data;
public:
    Box(int val) { data = new int(val); }
    ~Box() { delete data; }
    void show() { cout << *data; }
};

int main() {
    Box b1(10);
    Box *ptr = &b1;    // pointer to object
    ptr->show();          // access via arrow operator
}
```

### 6. `this` Pointer

Every non-static member function has an implicit pointer called `this`, which points to the object that invoked the function. Used to:
- Resolve naming conflicts between member variables and parameters
- Return the current object (`return *this;`) for method chaining
- Pass current object's address to another function

```cpp
class Point {
    int x, y;
public:
    Point(int x, int y) {
        this->x = x;    // resolves ambiguity between member and parameter
        this->y = y;
    }
    Point& setX(int x) {
        this->x = x;
        return *this;      // enables chaining: p.setX(5).setY(10);
    }
};
```

### 7. Array of Objects

```cpp
class Student {
    int roll;
public:
    void setRoll(int r) { roll = r; }
    void show() { cout << roll << " "; }
};

int main() {
    Student arr[3];              // array of 3 objects, default constructor called 3 times
    for (int i = 0; i < 3; i++) arr[i].setRoll(i + 1);
    for (int i = 0; i < 3; i++) arr[i].show();
}
```

### 8. The Standard C++ `string` Class

Part of `<string>`, `std::string` manages a dynamic character array internally (no manual memory management needed, unlike C-style `char[]`).

**Defining and assigning string objects:**
```cpp
#include <string>
string s1 = "Hello";
string s2("World");
string s3 = s1 + " " + s2;   // concatenation via overloaded +
```

**Common member functions:**

| Function | Purpose |
|---|---|
| `length()` / `size()` | number of characters |
| `substr(pos, len)` | extract substring |
| `find(str)` | index of first occurrence (or `string::npos`) |
| `append(str)` | add to end |
| `insert(pos, str)` | insert at position |
| `erase(pos, len)` | remove characters |
| `replace(pos, len, str)` | replace part of string |
| `c_str()` | returns C-style `const char*` |
| `compare(str)` | lexicographic comparison |
| `empty()` | true if length is 0 |

**Modifiers example:**
```cpp
string s = "Hello World";
cout << s.length() << endl;              // 11
cout << s.substr(6, 5) << endl;           // World
cout << s.find("World") << endl;          // 6
s.replace(0, 5, "Hi");                     // "Hi World"
s.erase(0, 3);                              // "orld"
s.insert(0, "W");                           // "World"
```

### 9. Pointer vs Reference Variable

| Pointer | Reference |
|---|---|
| Can be `nullptr` (unassigned) | Must be initialized when declared |
| Can be reassigned to point elsewhere | Cannot be re-bound after initialization |
| Needs `*` to dereference | Used directly, like a normal variable |
| Has its own memory address | Just an alias — usually no separate memory |
| Supports pointer arithmetic | No arithmetic possible |
| Declared as `int *p` | Declared as `int &r` |

### 10. Multidimensional Arrays

**Inside `main()`:**
```cpp
int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++)
        cout << matrix[i][j] << " ";
    cout << endl;
}
```

**Inside a class:**
```cpp
class Matrix {
    int data[2][2];
public:
    void input() {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                cin >> data[i][j];
    }
    void display() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) cout << data[i][j] << " ";
            cout << endl;
        }
    }
};
```

### 11. Pointer to Data Member

C++ allows pointers that point to a **member** of a class (not a specific object's member — a member "offset" that works across objects). Declared with `ClassName::*`.

```cpp
class Test {
public:
    int a;
    void show() { cout << "show()\n"; }
};

int main() {
    int Test::*dataPtr = &Test::a;      // pointer to data member
    Test t;
    t.*dataPtr = 100;                     // access via object
    cout << t.*dataPtr << endl;          // 100

    Test *tp = &t;
    cout << tp->*dataPtr << endl;         // 100, via object pointer
}
```

---

## Solved Coding Questions

**Q1. Write a program to demonstrate different types of pointers: void pointer, wild pointer (fixed), dangling pointer (fixed), and pointer to pointer.**
```cpp
#include <iostream>
using namespace std;

int main() {
    // void pointer
    int i = 25;
    void *vptr = &i;
    cout << "Void pointer value: " << *(int*)vptr << endl;

    // pointer to pointer
    int *p = &i;
    int **pp = &p;
    cout << "Double dereference: " << **pp << endl;

    // dangling pointer, handled safely
    int *dp = new int(50);
    delete dp;
    dp = nullptr;                 // avoid dangling reference
    if (dp == nullptr) cout << "Pointer safely nulled after delete\n";

    return 0;
}
```

**Q2. Write a program to process a 2D array (matrix addition) and an array of objects.**
```cpp
#include <iostream>
using namespace std;

class Employee {
    int id;
    string name;
public:
    void setData(int i, string n) { id = i; name = n; }
    void display() { cout << id << " - " << name << endl; }
};

int main() {
    // Multidimensional array processing
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            c[i][j] = a[i][j] + b[i][j];

    cout << "Matrix Sum:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) cout << c[i][j] << " ";
        cout << endl;
    }

    // Array of objects
    Employee emp[2];
    emp[0].setData(101, "Riya");
    emp[1].setData(102, "Karan");
    for (int i = 0; i < 2; i++) emp[i].display();

    return 0;
}
```

**Q3. Write a program using the C++ `string` class to reverse a string and check if it's a palindrome (without using `<algorithm>`).**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s, rev = "";
    cout << "Enter a string: ";
    getline(cin, s);

    for (int i = s.length() - 1; i >= 0; i--)
        rev += s[i];

    cout << "Reversed: " << rev << endl;
    cout << (s == rev ? "Palindrome" : "Not a Palindrome") << endl;
    return 0;
}
```

**Q4. Demonstrate the `this` pointer for method chaining (a simple `Builder`-style class).**
```cpp
#include <iostream>
using namespace std;

class Pizza {
    string size, topping;
public:
    Pizza& setSize(string s) { this->size = s; return *this; }
    Pizza& setTopping(string t) { this->topping = t; return *this; }
    void show() { cout << size << " pizza with " << topping << endl; }
};

int main() {
    Pizza p;
    p.setSize("Large").setTopping("Cheese").show();   // chained calls
    return 0;
}
```

**Q5. Write a program to demonstrate pointer to a data member of a class.**
```cpp
#include <iostream>
using namespace std;

class Account {
public:
    double balance;
};

int main() {
    double Account::*bp = &Account::balance;
    Account acc;
    acc.*bp = 5000.50;
    cout << "Balance: " << acc.*bp << endl;
    return 0;
}
```

---

## Practice Coding Questions (Unsolved)

1. Write a program that uses pointer arithmetic to find the sum of all elements in an array without using array indexing (`arr[i]`).
2. Write a program demonstrating a dangling pointer bug (comment explaining why it's dangerous) and then show the corrected safe version.
3. Create a class `Person` with a `char*` name pointer (allocated dynamically). Show how printing two objects that share the same pointer (shallow copy) can cause issues.
4. Write a program to input and display a `3x3` matrix using a class, and compute its transpose.
5. Write a program using `std::string` functions (`find`, `substr`, `replace`) to check how many times a word occurs in a sentence.
6. Write a program comparing pointer and reference behavior: pass an object both ways to functions that try to modify it.
7. Write a program that creates an array of 5 `Book` objects (with `title` and `price`), and finds the most expensive book using a pointer to iterate the array.
8. Demonstrate pointer to a member function (not just data member) that calls different functions based on user input.

---

## Viva / Interview Questions

1. What is a void pointer, and why must it be typecast before dereferencing?
2. What is the difference between a dangling pointer and a wild pointer?
3. How do you safely avoid a dangling pointer after calling `delete`?
4. What does `p++` actually do when `p` is an `int*`? How many bytes does it move by?
5. What is the difference between `*ptr++` and `(*ptr)++`?
6. What is a pointer to a pointer? Give a real use case.
7. What is the `this` pointer, and is it available in static member functions? Why/why not?
8. Why do we return `*this` from a member function? What pattern does this enable?
9. What happens when you create an array of objects — which constructor is called, and how many times?
10. How is `std::string` different from a C-style `char[]` string in terms of memory management?
11. What does `string::npos` represent, and when is it returned?
12. Why can't reference variables be reassigned once initialized, while pointers can?
13. What is the difference between deep memory address arithmetic on `int*` vs `char*` for the same offset?
14. What is a pointer to a data member? How is its syntax and usage different from a normal pointer?
15. Explain the difference in declaration syntax between a pointer to a data member and a pointer to a member function.
16. When accessing a class member through an object pointer, why do we use `->` instead of `.`?
17. What is the significance of `nullptr` over using `0` or `NULL` in modern C++?
18. What issues can arise from mixing pointer arithmetic with multidimensional arrays?
19. In a 2D array `int arr[2][3]`, what does `arr[i]` evaluate to (as a type)?
20. Why is passing a large object by pointer/reference preferred over passing by value in function calls?