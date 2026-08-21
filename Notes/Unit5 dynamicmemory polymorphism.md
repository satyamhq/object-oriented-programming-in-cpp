# CSE202 — Object Oriented Programming
## UNIT V: Dynamic Memory Management and Polymorphism

---

### 1. Dynamic Memory Allocation using `new` and `delete`

C++ allows memory to be allocated/deallocated at **runtime** (heap memory) using `new` and `delete`, unlike C's `malloc()`/`free()` — `new`/`delete` also automatically call constructors/destructors.

```cpp
int *p = new int;            // allocate single int
int *arr = new int[10];      // allocate array of 10 ints
*p = 25;

delete p;                     // free single object
delete[] arr;                 // free array (must use [] to match new[])

// with class objects
class Box { public: Box(){cout<<"Box created\n";} ~Box(){cout<<"Box destroyed\n";} };
Box *b = new Box();           // constructor called
delete b;                      // destructor called
```

**Important:** always match `new` with `delete`, and `new[]` with `delete[]` — mismatching causes **undefined behavior**.

### 2. Virtual Destructors

If a base class pointer holds a derived class object and is deleted, the base class destructor alone is called **unless the base destructor is `virtual`** — leading to a **memory leak** (derived part of the object never destroyed).

```cpp
class Base {
public:
    virtual ~Base() { cout << "Base destructor\n"; }   // virtual!
};
class Derived : public Base {
public:
    ~Derived() { cout << "Derived destructor\n"; }
};

int main() {
    Base *b = new Derived();
    delete b;      // With virtual dtor: Derived destructor, then Base destructor (correct!)
                    // Without virtual: only Base destructor called (memory leak / bug)
}
```
**Rule of thumb**: if a class has any virtual function, or is meant to be used polymorphically as a base class, give it a virtual destructor.

### 3. Compile-Time vs Run-Time Polymorphism

| | Compile-time (Static) | Run-time (Dynamic) |
|---|---|---|
| Also called | Early binding | Late binding |
| Achieved via | Function overloading, operator overloading | Virtual functions |
| Resolved | At compile time | At run time |
| Speed | Faster | Slightly slower (vtable lookup) |
| Flexibility | Less flexible | More flexible |

```cpp
// Compile-time: function overloading
void print(int i) { cout << "int: " << i; }
void print(double d) { cout << "double: " << d; }

// Run-time: virtual functions
class Shape { public: virtual void draw() { cout << "Shape\n"; } };
class Circle : public Shape { public: void draw() override { cout << "Circle\n"; } };

int main() {
    Shape *s = new Circle();
    s->draw();     // "Circle" — decided at runtime based on actual object type
}
```

### 4. Virtual Functions

A member function declared with the `virtual` keyword in the base class, intended to be **overridden** in derived classes. Enables **runtime polymorphism** via a mechanism called the **vtable (virtual table)** — each object with virtual functions carries a hidden pointer (`vptr`) to its class's vtable, which stores the correct function addresses.

```cpp
class Animal {
public:
    virtual void sound() { cout << "Some sound\n"; }
};
class Dog : public Animal {
public:
    void sound() override { cout << "Bark\n"; }
};

int main() {
    Animal *a = new Dog();
    a->sound();      // "Bark" — resolved at runtime (dynamic binding)
}
```

### 5. Dynamic Constructors

Refers to allocating memory dynamically *within* a constructor (e.g., for arrays/strings whose size is only known at runtime) — this allows the object's internal storage to be sized dynamically rather than fixed at compile time.

```cpp
class String {
    char *str;
public:
    String(const char *s) {
        str = new char[strlen(s) + 1];   // dynamic allocation inside constructor
        strcpy(str, s);
    }
    ~String() { delete[] str; }
    void show() { cout << str << endl; }
};
```

### 6. Abstract Class and Concrete Class

- **Abstract class**: a class with at least one **pure virtual function** — cannot be instantiated directly; serves as an interface/base for derived classes.
- **Concrete class**: a class that implements all inherited pure virtual functions (or has none) — can be instantiated normally.

```cpp
class Shape {                        // abstract class
public:
    virtual double area() = 0;        // pure virtual function
};

class Circle : public Shape {         // concrete class
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() override { return 3.14159 * radius * radius; }
};

int main() {
    // Shape s;         // ERROR: cannot instantiate abstract class
    Circle c(5);
    cout << c.area();
}
```

### 7. Introduction to Self-Referential Class

A class that contains a pointer to an object of its **own type**. Fundamental to building linked data structures (linked lists, trees).

```cpp
class Node {
public:
    int data;
    Node *next;      // pointer to same class type — self-referential
    Node(int d) : data(d), next(nullptr) {}
};

int main() {
    Node n1(10), n2(20);
    n1.next = &n2;                      // link nodes
    cout << n1.data << " " << n1.next->data;
}
```

### 8. Pure Virtual Functions

A virtual function with **no body** in the base class, declared with `= 0`. Forces every concrete derived class to provide its own implementation. Makes the containing class **abstract**.

```cpp
class Animal {
public:
    virtual void sound() = 0;   // pure virtual — no implementation
};
// class must override sound() to be instantiable
```

### 9. Early Binding vs Late Binding

- **Early (static) binding**: function call resolved at compile time (normal function calls, non-virtual member functions).
- **Late (dynamic) binding**: function call resolved at run time (virtual functions accessed via base class pointer/reference).

```cpp
class Base {
public:
    void normalFunc() { cout << "Base normal\n"; }      // early binding
    virtual void virtualFunc() { cout << "Base virtual\n"; }  // late binding
};
class Derived : public Base {
public:
    void normalFunc() { cout << "Derived normal\n"; }
    void virtualFunc() override { cout << "Derived virtual\n"; }
};

int main() {
    Base *b = new Derived();
    b->normalFunc();     // "Base normal" — early binding, decided by pointer TYPE
    b->virtualFunc();     // "Derived virtual" — late binding, decided by OBJECT type
}
```

### 10. Memory Leak and Allocation Failures

- **Memory leak**: dynamically allocated memory that is never `delete`d — the program loses all references to it, wasting memory until program exit.
- **Allocation failure**: `new` throws `std::bad_alloc` if memory cannot be allocated (heap exhausted). Use `try-catch` or `new(nothrow)` to handle gracefully.

```cpp
void leak() {
    int *p = new int(5);
    // missing delete p; -> memory leak every time this function is called
}

// Handling allocation failure
#include <new>
int main() {
    try {
        int *arr = new int[100000000000];   // extremely large
    } catch (bad_alloc &e) {
        cout << "Allocation failed: " << e.what() << endl;
    }

    int *p = new(nothrow) int[100000000000];  // returns nullptr instead of throwing
    if (!p) cout << "Allocation failed (nothrow)\n";
}
```

---

## Solved Coding Questions

**Q1. Write a program demonstrating `new`/`delete` for both single variables and dynamic arrays, and a class object.**
```cpp
#include <iostream>
using namespace std;

class Item {
public:
    Item() { cout << "Item created\n"; }
    ~Item() { cout << "Item destroyed\n"; }
};

int main() {
    int *p = new int(42);
    cout << *p << endl;
    delete p;

    int *arr = new int[5]{1,2,3,4,5};
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;
    delete[] arr;

    Item *it = new Item();
    delete it;
    return 0;
}
```

**Q2. Demonstrate the difference between having a virtual destructor and not having one (memory leak demonstration via output).**
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() { cout << "Base destructor\n"; }
};
class Derived : public Base {
    int *data;
public:
    Derived() { data = new int[100]; cout << "Derived constructor, memory allocated\n"; }
    ~Derived() { delete[] data; cout << "Derived destructor, memory freed\n"; }
};

int main() {
    Base *b = new Derived();
    delete b;    // Because ~Base() is virtual, ~Derived() runs too -> no leak
    return 0;
}
```

**Q3. Write a program to demonstrate compile-time polymorphism (overloading) and run-time polymorphism (virtual functions) side by side.**
```cpp
#include <iostream>
using namespace std;

// Compile-time
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
};

// Run-time
class Shape {
public:
    virtual void draw() { cout << "Drawing generic shape\n"; }
};
class Square : public Shape {
public:
    void draw() override { cout << "Drawing square\n"; }
};
class Triangle : public Shape {
public:
    void draw() override { cout << "Drawing triangle\n"; }
};

int main() {
    Calculator c;
    cout << c.add(2, 3) << " " << c.add(2.5, 3.5) << endl;   // compile-time resolved

    Shape *shapes[2];
    shapes[0] = new Square();
    shapes[1] = new Triangle();
    for (int i = 0; i < 2; i++) shapes[i]->draw();             // runtime resolved
    return 0;
}
```

**Q4. Write a program demonstrating an abstract class and a concrete class (Shape hierarchy with area()).**
```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;      // pure virtual
    virtual void display() { cout << "Area: " << area() << endl; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double l, double w) : l(l), w(w) {}
    double area() override { return l * w; }
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() override { return 3.14159 * r * r; }
};

int main() {
    Shape *shapes[2] = { new Rectangle(4, 5), new Circle(3) };
    for (int i = 0; i < 2; i++) shapes[i]->display();
    return 0;
}
```

**Q5. Write a program to build a self-referential class implementing a simple singly linked list (insert + display).**
```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
    Node *head;
public:
    LinkedList() : head(nullptr) {}

    void insert(int val) {
        Node *newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node *temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    void display() {
        Node *temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    ~LinkedList() {                  // clean up to avoid memory leak
        Node *temp = head;
        while (temp) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    LinkedList list;
    list.insert(10); list.insert(20); list.insert(30);
    list.display();
    return 0;
}
```

**Q6. Write a program demonstrating early binding vs late binding explicitly, with commentary output.**
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    void staticFn() { cout << "Base::staticFn (early binding)\n"; }
    virtual void dynamicFn() { cout << "Base::dynamicFn (late binding)\n"; }
};

class Derived : public Base {
public:
    void staticFn() { cout << "Derived::staticFn\n"; }
    void dynamicFn() override { cout << "Derived::dynamicFn\n"; }
};

int main() {
    Base *b = new Derived();
    b->staticFn();     // Base::staticFn -> resolved by pointer type at compile time
    b->dynamicFn();    // Derived::dynamicFn -> resolved by object type at runtime
    delete b;
    return 0;
}
```

**Q7. Write a program to safely handle allocation failure using `try-catch` and `nothrow`.**
```cpp
#include <iostream>
#include <new>
using namespace std;

int main() {
    try {
        int *bigArr = new int[1000000000000];  // will likely throw bad_alloc
    } catch (const bad_alloc &e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    int *p = new(nothrow) int[1000000000000];
    if (p == nullptr)
        cout << "Allocation failed, returned nullptr (nothrow)\n";
    else
        delete[] p;

    return 0;
}
```

---

## Practice Coding Questions (Unsolved)

1. Write a program to dynamically allocate an array of `Student` objects (size taken from user input at runtime), fill it, display it, then properly deallocate.
2. Create an abstract class `Employee` with a pure virtual `calculateSalary()`, and two concrete derived classes `Manager` and `Developer` with different salary formulas. Use a base class pointer array to compute all salaries polymorphically.
3. Demonstrate a memory leak by deliberately omitting a `delete`, then fix it — comment explaining the difference.
4. Build a self-referential `TreeNode` class and implement a simple binary search tree `insert()` and in-order `display()`.
5. Write a program using a virtual destructor in a 3-level inheritance chain (`Base → Middle → Derived`) and show the destruction order when deleted via a `Base*`.
6. Write a program demonstrating dynamic constructors — a custom `MyString` class that allocates exactly the memory it needs based on input length.
7. Create a `Shape` class hierarchy with `Shape` as abstract, having pure virtual `area()` and `perimeter()`; implement `Circle`, `Square`, and `Triangle`.
8. Write a program that intentionally triggers `bad_alloc` and handles it gracefully with a user-friendly error message.

---

## Viva / Interview Questions

1. Why is `new`/`delete` preferred over `malloc()`/`free()` in C++ for objects?
2. What happens if you use `delete` instead of `delete[]` on a dynamically allocated array?
3. What is a memory leak, and how would you detect one in a real project?
4. Why must a base class destructor be `virtual` when the class is intended to be used polymorphically?
5. What is the vtable/vptr mechanism, and how does it enable runtime polymorphism?
6. What's the difference between early binding and late binding? Give one example of each.
7. Can a constructor be virtual? Why or why not?
8. What is a pure virtual function, and what is its syntax?
9. What is an abstract class? Can it have a constructor, and if so, why (since it can't be instantiated)?
10. What's the difference between an abstract class and a concrete class in terms of instantiation?
11. What is a self-referential class? Name two data structures that fundamentally depend on it.
12. What exception does `new` throw when memory allocation fails? How do you catch it?
13. What is `new(nothrow)`, and how does its failure behavior differ from plain `new`?
14. Why does calling a non-virtual function through a base class pointer NOT show polymorphic behavior?
15. What is the difference between compile-time and run-time polymorphism in terms of performance?
16. If a class has any virtual functions, why is it good practice to also give it a virtual destructor even if the destructor itself does nothing special?
17. Explain what happens step-by-step when you `delete` a `Derived` object through a `Base*` with a non-virtual destructor.
18. Can an abstract class have non-pure virtual (regular) member functions along with pure virtual ones?
19. Why can't you create an object of an abstract class directly, but you CAN create a pointer of that type?
20. What is the difference between object slicing and normal polymorphic behavior, and how does using pointers/references avoid slicing?