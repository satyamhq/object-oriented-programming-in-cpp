# CSE202 — Object Oriented Programming
## UNIT III: Data File Operations, Constructors, Destructors and File Handling

---

## Part A: Data File Operations

### 1. Opening and Closing Files

C++ file handling uses classes from `<fstream>`:
- `ofstream` — output file stream (writing)
- `ifstream` — input file stream (reading)
- `fstream` — both reading and writing

```cpp
#include <fstream>
using namespace std;

ofstream fout;
fout.open("data.txt");     // open for writing
// ... operations
fout.close();                 // always close after use

// or directly via constructor
ofstream fout2("data.txt");
fout2.close();
```

### 2. Modes of File

| Mode flag | Meaning |
|---|---|
| `ios::in` | open for reading |
| `ios::out` | open for writing |
| `ios::app` | append to end of file |
| `ios::ate` | open and move pointer to end |
| `ios::trunc` | truncate (erase) existing content |
| `ios::binary` | open in binary mode |

```cpp
fstream file("data.txt", ios::in | ios::out | ios::app);
```

### 3. File Stream Functions

| Function | Purpose |
|---|---|
| `open()` | opens a file |
| `close()` | closes a file |
| `is_open()` | checks if file successfully opened |
| `eof()` | true when end-of-file reached |
| `<<` / `>>` | write/read formatted data |
| `getline()` | read a line |
| `read()` / `write()` | binary read/write |
| `seekg()` / `seekp()` | move get/put pointer |
| `tellg()` / `tellp()` | return current get/put pointer position |

### 4. Reading/Writing of Files

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("data.txt");
    if (!fout) { cout << "Error opening file\n"; return 1; }
    fout << "Hello File Handling\n" << 42 << endl;
    fout.close();

    ifstream fin("data.txt");
    string line;
    while (getline(fin, line))
        cout << line << endl;
    fin.close();
    return 0;
}
```

### 5. Sequential vs Random Access File Processing

- **Sequential access**: data is read/written in order, from start to end (default behavior).
- **Random access**: uses `seekg()`/`seekp()` to jump directly to any byte position, allowing non-linear read/write — essential for binary record files.

```cpp
fstream file("records.dat", ios::in | ios::out | ios::binary);
file.seekg(0, ios::beg);      // move to start
file.seekg(20, ios::cur);      // move 20 bytes forward from current
file.seekg(-10, ios::end);     // move 10 bytes back from end
cout << file.tellg();           // current position of get pointer
```

### 6. Binary File Operations

Binary files store data in the internal binary representation of variables/objects (not human-readable text) — faster and more compact, essential for storing objects directly.

```cpp
struct Record { int id; char name[20]; };

// writing binary
ofstream fout("rec.dat", ios::binary);
Record r = {1, "Aman"};
fout.write((char*)&r, sizeof(r));
fout.close();

// reading binary
ifstream fin("rec.dat", ios::binary);
Record r2;
fin.read((char*)&r2, sizeof(r2));
fin.close();
cout << r2.id << " " << r2.name;
```

### 7. Classes and File Operations / Structures and File Operations

Objects of a class (or instances of a struct) can be written to and read from binary files directly using `write()`/`read()`, since they occupy contiguous memory (as long as they have no pointers or dynamically-allocated members — otherwise only the pointer value gets saved, not the pointed-to data).

```cpp
class Student {
    int roll;
    char name[20];
public:
    void setData(int r, string n) { roll = r; strcpy(name, n.c_str()); }
    void display() { cout << roll << " " << name << endl; }
};

int main() {
    Student s;
    s.setData(1, "Neha");

    ofstream fout("students.dat", ios::binary);
    fout.write((char*)&s, sizeof(s));
    fout.close();

    Student s2;
    ifstream fin("students.dat", ios::binary);
    fin.read((char*)&s2, sizeof(s2));
    s2.display();
    return 0;
}
```

---

## Part B: Constructors, Destructors and File Handling

### 1. Manager Functions (Constructors and Destructor)

Also called "special member functions" — automatically invoked to manage the lifecycle of an object: **construction** (initialization) and **destruction** (cleanup).

### 2. Default Constructor

A constructor with no parameters (or all parameters have default values). If no constructor is defined by the programmer, the compiler auto-generates one.

```cpp
class Box {
    int side;
public:
    Box() { side = 0; cout << "Default constructor called\n"; }
};
```

### 3. Constructor with Default Arguments

```cpp
class Box {
    int side;
public:
    Box(int s = 10) { side = s; }   // acts as default constructor too
};

Box b1;        // side = 10
Box b2(5);     // side = 5
```

### 4. Parameterized Constructor

Accepts arguments to initialize an object with specific values at creation time.

```cpp
class Point {
    int x, y;
public:
    Point(int a, int b) { x = a; y = b; }
    void show() { cout << x << "," << y; }
};

Point p(3, 4);
```

### 5. Copy Constructor

Initializes an object using another object of the same class. Signature: `ClassName(const ClassName &obj)`. Invoked when:
- An object is initialized from another object: `Box b2 = b1;` or `Box b2(b1);`
- An object is passed by value to a function
- An object is returned by value from a function

```cpp
class Box {
    int side;
public:
    Box(int s) { side = s; }
    Box(const Box &b) {                       // copy constructor
        side = b.side;
        cout << "Copy constructor called\n";
    }
    void show() { cout << side; }
};

Box b1(5);
Box b2 = b1;    // copy constructor invoked
```

**Shallow Copy vs Deep Copy** (critical when class has pointer members):
- **Shallow copy** (default compiler-generated): copies pointer *values* — both objects' pointers point to the *same* memory. Dangerous — double free / dangling pointer risk.
- **Deep copy** (user-defined copy constructor): allocates *new* memory and copies the actual data — safe, independent copies.

```cpp
class Buffer {
    int *data;
public:
    Buffer(int val) { data = new int(val); }
    // Deep copy constructor
    Buffer(const Buffer &b) {
        data = new int(*b.data);    // new memory allocated, value copied
    }
    ~Buffer() { delete data; }
    void show() { cout << *data; }
};
```

### 6. Destructors

A special member function that is automatically called when an object goes out of scope or is explicitly deleted. Used to release resources (dynamic memory, file handles, etc.).

- Name: `~ClassName()`
- No return type, no parameters
- Cannot be overloaded (only one destructor per class)
- Called in **reverse order** of construction for multiple objects

```cpp
class Demo {
public:
    Demo() { cout << "Constructed\n"; }
    ~Demo() { cout << "Destroyed\n"; }
};

int main() {
    Demo d1, d2;
}   // Destructor order: d2 destroyed first, then d1
```

### 7. Initializer Lists

A more efficient way to initialize data members — especially required for `const` members, reference members, and members without a default constructor. Members are initialized *before* the constructor body executes.

```cpp
class Point {
    const int x;
    int &yRef;
    int z;
public:
    Point(int a, int &b, int c) : x(a), yRef(b), z(c) {
        // body — x and yRef MUST be set via initializer list (can't be assigned in body)
    }
};
```

Initializer lists are also more efficient for class-type members (avoids default-construct-then-assign, does direct construction):
```cpp
class Engine { public: Engine() { cout << "Engine default\n"; } Engine(int hp){ cout<<"Engine("<<hp<<")\n"; } };
class Car {
    Engine e;
public:
    Car() : e(300) {}   // directly constructs Engine with 300, avoids default + reassignment
};
```

---

## Solved Coding Questions

**Q1. Write a program to write student records to a text file and then read and display them.**
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("students.txt");
    fout << "101 Aman 89\n102 Riya 92\n103 Karan 76\n";
    fout.close();

    ifstream fin("students.txt");
    int roll, marks;
    string name;
    cout << "Roll\tName\tMarks\n";
    while (fin >> roll >> name >> marks)
        cout << roll << "\t" << name << "\t" << marks << endl;
    fin.close();
    return 0;
}
```

**Q2. Demonstrate the different modes of file (write, append, read) on the same file.**
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream f1("log.txt", ios::out);       // create/overwrite
    f1 << "First entry\n";
    f1.close();

    ofstream f2("log.txt", ios::app);        // append mode
    f2 << "Second entry (appended)\n";
    f2.close();

    ifstream f3("log.txt", ios::in);
    string line;
    while (getline(f3, line)) cout << line << endl;
    f3.close();
    return 0;
}
```

**Q3. Write a program to store and retrieve `Employee` objects using binary file operations.**
```cpp
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Employee {
    int id;
    char name[20];
public:
    void input() {
        cout << "ID: "; cin >> id;
        cout << "Name: "; cin >> name;
    }
    void display() { cout << id << " - " << name << endl; }
};

int main() {
    Employee e;
    e.input();

    ofstream fout("emp.dat", ios::binary);
    fout.write((char*)&e, sizeof(e));
    fout.close();

    Employee e2;
    ifstream fin("emp.dat", ios::binary);
    fin.read((char*)&e2, sizeof(e2));
    e2.display();
    fin.close();
    return 0;
}
```

**Q4. Write a program to demonstrate all types of constructors (default, parameterized, copy) and a destructor with output showing the call order.**
```cpp
#include <iostream>
using namespace std;

class Demo {
    int val;
public:
    Demo() { val = 0; cout << "Default constructor\n"; }
    Demo(int v) { val = v; cout << "Parameterized constructor: " << val << endl; }
    Demo(const Demo &d) { val = d.val; cout << "Copy constructor: " << val << endl; }
    ~Demo() { cout << "Destructor for value " << val << endl; }
    void show() { cout << "Value: " << val << endl; }
};

int main() {
    Demo d1;             // default
    Demo d2(10);          // parameterized
    Demo d3 = d2;          // copy
    d1.show(); d2.show(); d3.show();
    return 0;
}   // destructors called in reverse order: d3, d2, d1
```

**Q5. Write a program demonstrating shallow copy (bug) vs deep copy (fix) for a class holding dynamic memory.**
```cpp
#include <iostream>
using namespace std;

class ShallowBox {
public:
    int *data;
    ShallowBox(int v) { data = new int(v); }
    // no custom copy constructor -> compiler default = shallow copy
    ~ShallowBox() { delete data; }
};

class DeepBox {
public:
    int *data;
    DeepBox(int v) { data = new int(v); }
    DeepBox(const DeepBox &d) { data = new int(*d.data); }   // deep copy
    ~DeepBox() { delete data; }
};

int main() {
    {
        DeepBox a(5);
        DeepBox b = a;     // safe: independent memory
        cout << "Deep copy: " << *a.data << " " << *b.data << endl;
    }   // both destructors safely delete their own memory

    // ShallowBox b1(5); ShallowBox b2 = b1; // would cause double-free crash on destruction
    return 0;
}
```

**Q6. Demonstrate initializer lists with a `const` member and a reference member.**
```cpp
#include <iostream>
using namespace std;

class Circle {
    const double PI;
    int &radiusRef;
public:
    Circle(int &r) : PI(3.14159), radiusRef(r) {}   // must use initializer list
    double area() { return PI * radiusRef * radiusRef; }
};

int main() {
    int r = 5;
    Circle c(r);
    cout << "Area: " << c.area() << endl;
    return 0;
}
```

---

## Practice Coding Questions (Unsolved)

1. Write a program to count the number of lines, words, and characters in a text file.
2. Write a program that uses `seekg()`/`tellg()` to read a specific record (by index) directly from a binary file of `Product` objects, without reading all previous records.
3. Write a menu-driven program to add, view, and delete a student record from a binary file (deletion = rewrite file skipping that record).
4. Write a class `Matrix` where a parameterized constructor allocates a 2D dynamic array; implement a proper deep-copy constructor and destructor.
5. Write a program with 3 objects created in `main()` using default, parameterized, and copy constructors respectively, and observe/print the destruction order.
6. Write a program to merge the contents of two text files into a third file.
7. Create a class `ImmutablePoint` with `const` x and y members, initialized only via an initializer list; try (and explain why it fails) to assign to `x` inside the constructor body.
8. Write a program to append new records to an existing binary file of `Employee` objects without overwriting the old ones.

---

## Viva / Interview Questions

1. What is the difference between `ios::app` and `ios::ate`?
2. Why must binary files be opened with `ios::binary`, and what goes wrong if you don't?
3. What is the difference between `seekg()` and `seekp()`?
4. What does `tellg()` return, and when would you use it?
5. Explain sequential vs random access file processing with an example use case for each.
6. Why do we typecast the address of an object to `(char*)` when using `write()`/`read()`?
7. What problem occurs if you try to write an object containing a `string` or pointer member directly using binary `write()`?
8. What is a default constructor, and does the compiler always generate one?
9. What is the difference between a parameterized constructor and a constructor with default arguments — can one replace the other?
10. When exactly is the copy constructor invoked (list at least 3 scenarios)?
11. What is the difference between shallow copy and deep copy? Why is shallow copy dangerous for classes with pointer members?
12. What is the signature of a copy constructor, and why is the parameter passed by reference (`const ClassName&`) instead of by value?
13. Can a destructor be overloaded? Why or why not?
14. In what order are destructors called for multiple local objects going out of scope, and why?
15. Why must `const` and reference data members be initialized only through an initializer list?
16. What's the performance benefit of using an initializer list over assignment in the constructor body for a class-type member?
17. What is a "manager function" broadly — which functions fall under this term?
18. What happens if two objects with shallow-copied pointers both go out of scope? (Explain the double-free issue.)
19. Why is `is_open()` important to check before performing file operations?
20. How would you detect and handle end-of-file (`eof()`) correctly while reading records in a loop?