# CSE202 — Object Oriented Programming
## UNIT I: Concepts and Basics of C++ Programming, Functions

---

## Part A: Concepts and Basics of C++ Programming

### 1. Introduction to OOP and OOP Languages

**Procedural Programming** organizes code as a sequence of instructions/functions operating on data. Data and functions are separate; data is usually global or passed around, so many functions can freely access and change it. Examples: C, Pascal, FORTRAN.

**Object Oriented Programming (OOP)** organizes code around **objects** that bundle data (attributes) and behavior (methods) together. It emphasizes:

- **Encapsulation** – binding data and functions together, hiding internal details
- **Abstraction** – exposing only essential features, hiding implementation
- **Inheritance** – deriving new classes from existing ones
- **Polymorphism** – same interface, different implementations

**OOP Languages**: C++, Java, Python, C#, Smalltalk.

### 2. Procedural vs Object-Oriented Paradigm

| Procedural | Object Oriented |
|---|---|
| Program divided into functions | Program divided into objects |
| Data moves freely between functions | Data hidden, accessed via methods |
| No data hiding (mostly global data) | Supports data hiding (private members) |
| Adding new data/function is hard | Easy to add new objects/classes |
| Follows top-down approach | Follows bottom-up approach |
| Overloading not supported | Functions/operators can be overloaded |
| Examples: C, Pascal | Examples: C++, Java |

### 3. Reading/Writing Data using `cin` and `cout`

`cin` and `cout` are objects of classes `istream` and `ostream` respectively, defined in `<iostream>`. They use the **insertion operator `<<`** (output) and **extraction operator `>>`** (input), which are overloaded operators.

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    string name;

    cout << "Enter your name: ";
    cin >> name;                 // reads a single word (stops at whitespace)

    cout << "Enter your age: ";
    cin >> age;

    cout << "Hello " << name << ", you are " << age << " years old." << endl;
    return 0;
}
```

- `cin >>` skips leading whitespace and stops at the next whitespace — not good for reading full sentences with spaces (use `getline(cin, str)` instead).
- `endl` flushes the output buffer and inserts a newline; `"\n"` just inserts a newline (faster).

### 4. Classes and Objects

A **class** is a user-defined blueprint/template that defines the properties (data members) and behaviors (member functions) that objects of that type will have.
An **object** is an instance of a class — actual memory is allocated for an object, not for a class.

```cpp
class Student {
private:
    int roll;
    string name;

public:
    void setData(int r, string n) {   // member function
        roll = r;
        name = n;
    }
    void display() {
        cout << roll << " " << name << endl;
    }
};

int main() {
    Student s1;          // object creation
    s1.setData(1, "Amit");
    s1.display();
    return 0;
}
```

### 5. Accessing Class Members

- Members are accessed via the **dot (`.`) operator** for objects, and the **arrow (`->`) operator** for pointers to objects.
- Access specifiers control visibility:
  - `private` — accessible only inside the class (default for `class`)
  - `protected` — accessible inside the class and derived classes
  - `public` — accessible from anywhere the object is visible

```cpp
Student s1;
s1.setData(1, "Amit");     // dot operator

Student *p = &s1;
p->display();               // arrow operator
```

### 6. Differences: Structures, Unions, Enumerations, and Classes

| Feature | Structure | Union | Enumeration | Class |
|---|---|---|---|---|
| Default access | public | public | — | private |
| Memory | Each member gets own memory | All members share same memory | Constants stored as int | Each member gets own memory |
| Purpose | Group different data types | Save memory, one active member at a time | Named integer constants | Data + behavior encapsulation |
| Can have member functions | Yes (C++) | Yes (C++) | No | Yes |
| Keyword | `struct` | `union` | `enum` | `class` |

```cpp
struct Point { int x, y; };          // default public
union Data   { int i; float f; };    // shares memory
enum Color   { RED, GREEN, BLUE };   // RED=0, GREEN=1, BLUE=2
class Box    { int side; };          // default private
```

**Key size difference:** `sizeof(union)` = size of its largest member; `sizeof(struct)` = sum of all members (plus padding).

### 7. Inline and Non-inline Member Functions

- **Inline function**: the compiler *may* replace the function call with the actual function body to avoid function-call overhead. Any function **defined inside the class body** is inline by default. Functions defined outside using the scope resolution operator (`::`) need the explicit `inline` keyword to request inlining.
- **Non-inline (normal) function**: defined outside the class, compiled as a normal function call (jump/return overhead).

```cpp
class Demo {
public:
    void show() { cout << "Inline by default\n"; }   // implicitly inline

    void greet();   // declaration only
};

inline void Demo::greet() {                            // explicit inline
    cout << "Explicitly inline\n";
}
```
> Note: `inline` is only a *request* to the compiler — the compiler can ignore it (e.g., for recursive or very large functions).

### 8. Static Data Members and Static Member Functions

- **Static data member**: shared by all objects of the class — only one copy exists regardless of how many objects are created. Must be defined (memory allocated) outside the class.
- **Static member function**: can be called without any object, using the class name. Can access **only static data members** (no `this` pointer).

```cpp
class Counter {
private:
    static int count;   // declaration
public:
    Counter() { count++; }
    static int getCount() { return count; }   // static member function
};

int Counter::count = 0;   // definition/initialization outside class

int main() {
    Counter a, b, c;
    cout << Counter::getCount();   // 3 — called using class name
}
```

### 9. Features of Input/Output Streams

C++ I/O is stream-based (`<iostream>`), meaning data flows as a sequence of bytes.

- `istream` — input stream (`cin`)
- `ostream` — output stream (`cout`)
- `iostream` — both input and output (`cin`/`cout` combined class hierarchy)
- Supports **operator overloading** of `<<` and `>>` for user-defined types
- **Manipulators** (`endl`, `setw`, `setprecision`) control formatting
- Predefined streams: `cin`, `cout`, `cerr` (unbuffered error), `clog` (buffered error)

---

## Part B: Functions

### 1. Functions with Default Parameters/Arguments

A default argument is a value automatically assigned by the compiler if the caller does not provide one. Default values must be given from **right to left** (trailing parameters).

```cpp
void greet(string name, string greeting = "Hello") {
    cout << greeting << ", " << name << "!\n";
}

int main() {
    greet("Amit");             // Hello, Amit!
    greet("Amit", "Hi");       // Hi, Amit!
}
```

### 2. Inline Functions

```cpp
inline int square(int x) {
    return x * x;
}
```
Used for small, frequently called functions to save the overhead of a function call. Compiler may still choose not to inline (e.g., function has loops, recursion, is too large).

### 3. Manipulator Functions

Manipulators modify the format of I/O stream data. Defined in `<iomanip>`.

| Manipulator | Purpose |
|---|---|
| `endl` | newline + flush |
| `setw(n)` | sets field width |
| `setprecision(n)` | sets decimal precision |
| `setfill(c)` | sets fill character |
| `fixed` | fixed-point notation |
| `left` / `right` | alignment |

```cpp
#include <iomanip>
cout << setw(10) << setfill('*') << 25 << endl;   // ********25
cout << fixed << setprecision(2) << 3.14159;       // 3.14
```

### 4. Function Overloading and Scope Rules

**Function overloading**: multiple functions with the same name but different parameter lists (number/type/order of parameters). Return type alone cannot distinguish overloads.

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }
```

**Scope rules**: A variable declared inside a block is local to that block. The **scope resolution operator `::`** is used to access a global variable when a local variable of the same name exists, or to define a class member function outside the class.

```cpp
int x = 10;              // global
void demo() {
    int x = 20;           // local, hides global
    cout << x;             // 20
    cout << ::x;            // 10 (global via scope resolution)
}
```

### 5. Friend Function and Friend Class

A **friend function/class** is granted access to the `private` and `protected` members of a class even though it is not a member of that class. Friendship is **not mutual** and **not inherited**.

```cpp
class Box {
    int width;
public:
    Box(int w) : width(w) {}
    friend void printWidth(Box b);   // friend function declaration
    friend class BoxPrinter;         // friend class
};

void printWidth(Box b) {
    cout << b.width;   // can access private member
}

class BoxPrinter {
public:
    void show(Box b) { cout << b.width; }
};
```

### 6. Reference Variables

A reference is an **alias** — another name for an existing variable. Must be initialized at declaration and cannot be reassigned to refer to a different variable.

```cpp
int a = 10;
int &ref = a;   // ref is an alias for a
ref = 20;        // a becomes 20 too
```

### 7. Call by Value, Call by Address, Call by Reference

| Aspect | Call by Value | Call by Address (Pointer) | Call by Reference |
|---|---|---|---|
| What's passed | Copy of value | Address of variable | Alias of variable |
| Original modified? | No | Yes (via dereferencing) | Yes |
| Syntax | `func(x)` | `func(&x)`, param `int *p` | `func(x)`, param `int &r` |
| Memory overhead | Extra copy made | No extra copy | No extra copy |

```cpp
void byValue(int x)   { x = 100; }              // original unaffected
void byAddress(int *x){ *x = 100; }              // original changed
void byReference(int &x){ x = 100; }             // original changed

int main() {
    int a = 5;
    byValue(a);      cout << a << " "; // 5
    byAddress(&a);   cout << a << " "; // 100
    a = 5;
    byReference(a);  cout << a;         // 100
}
```

### 8. Recursion (Function and Member Function)

A function that calls itself, directly or indirectly, to solve a problem by breaking it into smaller sub-problems. Requires a **base case** to terminate.

```cpp
// Simple recursive function
int factorial(int n) {
    if (n == 0) return 1;         // base case
    return n * factorial(n - 1);  // recursive case
}

// Recursive member function
class MathOps {
public:
    int fib(int n) {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    }
};
```

---

## Solved Coding Questions

**Q1. Write a program to define a class `Rectangle` with private data members `length` and `breadth`, and member functions to set values and calculate area.**
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length, breadth;
public:
    void setDimensions(double l, double b) {
        length = l;
        breadth = b;
    }
    double area() {
        return length * breadth;
    }
};

int main() {
    Rectangle r;
    r.setDimensions(5.0, 3.0);
    cout << "Area: " << r.area() << endl;
    return 0;
}
```

**Q2. Demonstrate inline vs non-inline member functions and a static function counting objects created.**
```cpp
#include <iostream>
using namespace std;

class Item {
    static int objectCount;
public:
    Item() { objectCount++; }
    void show() { cout << "Inline function\n"; }  // inline (defined in class)
    void greet();                                    // non-inline, declared here

    static int getCount() { return objectCount; }   // static member function
};

int Item::objectCount = 0;

void Item::greet() {                 // non-inline definition
    cout << "Non-inline function\n";
}

int main() {
    Item a, b, c;
    a.show();
    a.greet();
    cout << "Total objects: " << Item::getCount() << endl;
    return 0;
}
```

**Q3. Write a program to implement function overloading to add 2 integers, 2 doubles, and 3 integers.**
```cpp
#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }

int main() {
    cout << add(2, 3) << endl;
    cout << add(2.5, 3.5) << endl;
    cout << add(1, 2, 3) << endl;
    return 0;
}
```

**Q4. Write a program to demonstrate a friend function accessing private data of two classes (to compare them).**
```cpp
#include <iostream>
using namespace std;

class Celsius;

class Fahrenheit {
    double temp;
public:
    Fahrenheit(double t) : temp(t) {}
    friend void compare(Fahrenheit f, Celsius c);
};

class Celsius {
    double temp;
public:
    Celsius(double t) : temp(t) {}
    friend void compare(Fahrenheit f, Celsius c);
};

void compare(Fahrenheit f, Celsius c) {
    double converted = (f.temp - 32) * 5 / 9;
    cout << (converted == c.temp ? "Equal temperatures" : "Different temperatures") << endl;
}

int main() {
    Fahrenheit f(98.6);
    Celsius c(37);
    compare(f, c);
    return 0;
}
```

**Q5. Write a program demonstrating call by value, call by address, and call by reference (swap two numbers each way).**
```cpp
#include <iostream>
using namespace std;

void swapByValue(int a, int b) {
    int t = a; a = b; b = t;
}
void swapByAddress(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}
void swapByReference(int &a, int &b) {
    int t = a; a = b; b = t;
}

int main() {
    int x = 10, y = 20;

    swapByValue(x, y);
    cout << "By Value: " << x << " " << y << endl;      // unchanged

    swapByAddress(&x, &y);
    cout << "By Address: " << x << " " << y << endl;     // swapped

    swapByReference(x, y);
    cout << "By Reference: " << x << " " << y << endl;   // swapped again
    return 0;
}
```

**Q6. Write a recursive member function to compute the factorial of a number, and an iterative Fibonacci for comparison.**
```cpp
#include <iostream>
using namespace std;

class MathUtils {
public:
    long factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
    int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
};

int main() {
    MathUtils m;
    cout << "5! = " << m.factorial(5) << endl;
    for (int i = 0; i < 8; i++) cout << m.fibonacci(i) << " ";
    return 0;
}
```

---

## Practice Coding Questions (Unsolved)

1. Write a class `BankAccount` with private data members `accNo` and `balance`, member functions `deposit()`, `withdraw()`, and `showBalance()`. Use default arguments for `withdraw()` so it withdraws a minimum balance if not specified.
2. Define a `union` and a `struct` with the same members; use `sizeof()` on both and explain the size difference in a comment.
3. Write a program using a static data member to assign a unique auto-incrementing ID to every object of a class `Employee`.
4. Overload a function `volume()` to compute the volume of a cube (1 param), a rectangular box (3 params), and a cylinder (2 params, using `double`).
5. Write a program with two classes `Box` and `BoxPrinter`, where `BoxPrinter` is declared a friend class of `Box` and can print its private dimensions.
6. Write a recursive function to compute the **GCD** of two numbers using the Euclidean algorithm.
7. Write a program to demonstrate the difference in output when a variable is passed by value vs by reference to a function that increments it.
8. Use manipulators (`setw`, `setfill`, `setprecision`) to print a formatted table of 5 students' names and marks.

---

## Viva / Interview Questions

1. What is the difference between a class and an object?
2. Why is data hiding important in OOP?
3. What is the default access specifier for a `class` and for a `struct`?
4. Can a `struct` have member functions and constructors in C++? How is it different from C's `struct`?
5. What is the difference between a `union` and a `struct` in terms of memory allocation?
6. What happens if you don't initialize a static data member outside the class?
7. Can a static member function access non-static data members? Why or why not?
8. Why does `inline` behave only as a *request* to the compiler? Give a scenario where inlining is rejected.
9. What is function overloading? What are the rules for a valid overload (can return type alone differentiate)?
10. What is the difference between a friend function and a member function in terms of the implicit `this` pointer?
11. Is friendship inherited or reciprocal (mutual) in C++? Justify.
12. What's the difference between a pointer and a reference variable? (Can be answered fully after Unit II, but the basic idea: reference must be initialized and can't be null/reassigned.)
13. Why is call-by-reference generally more efficient than call-by-value for large objects?
14. What is the base case in recursion, and what happens if it's omitted?
15. What is the difference between `cin >>` and `getline(cin, str)`?
16. Differentiate between `endl` and `"\n"`.
17. What is scope resolution operator `::` used for? Give two distinct uses.
18. Why can't default arguments be given from left to right skipping the rightmost parameters? e.g. `void f(int a = 5, int b)` is invalid — why?
19. What is the difference between procedural programming and object-oriented programming?
20. Explain how recursion uses the call stack internally, and what causes a stack overflow in deep recursion.