# CSE202 — Object Oriented Programming
## UNIT IV: Operator Overloading, Type Conversion, and Inheritance

---

## Part A: Operator Overloading and Type Conversion

### 1. Operator Overloading — Concept

C++ allows most operators to be redefined for user-defined types (classes) so they behave meaningfully for objects, using the keyword `operator`. Achieves a natural, intuitive syntax (e.g., `c3 = c1 + c2` for complex numbers).

**Rules:**
- Cannot create new operators, only overload existing ones
- Cannot change operator precedence or associativity
- Some operators **cannot** be overloaded: `::`, `.`, `.*`, `?:`, `sizeof`
- At least one operand must be a user-defined type

### 2. Unary Operator Overloading

Operators that act on a single operand, e.g., `-`, `++`, `--`, `!`.

```cpp
class Number {
    int val;
public:
    Number(int v) { val = v; }
    Number operator-() {            // unary minus
        return Number(-val);
    }
    Number operator++() {            // pre-increment
        val++;
        return *this;
    }
    Number operator++(int) {         // post-increment (dummy int parameter)
        Number temp = *this;
        val++;
        return temp;
    }
    void show() { cout << val << endl; }
};

int main() {
    Number n(5);
    Number n2 = -n;         // calls operator-()
    n2.show();                // -5
    ++n; n.show();            // 6
    n++; n.show();            // 7
}
```

### 3. Binary Operator Overloading

Operators that act on two operands, e.g., `+`, `-`, `==`.

```cpp
class Complex {
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex &c) {          // member function version
        return Complex(real + c.real, imag + c.imag);
    }
    bool operator==(const Complex &c) {
        return real == c.real && imag == c.imag;
    }
    friend ostream& operator<<(ostream &out, const Complex &c);  // friend for cout <<
};

ostream& operator<<(ostream &out, const Complex &c) {
    out << c.real << " + " << c.imag << "i";
    return out;
}

int main() {
    Complex c1(2, 3), c2(1, 4);
    Complex c3 = c1 + c2;
    cout << c3 << endl;      // 3 + 7i
}
```
> Binary operators can be overloaded as **member functions** (left operand is implicit `this`) or as **friend/non-member functions** (needed when the left operand isn't of the class type, e.g. `cout << obj`).

### 4. Type Conversions

**a) Basic type → Class type** (via a constructor taking a single basic-type argument — a "converting constructor"):
```cpp
class Distance {
    double meters;
public:
    Distance(double m) { meters = m; }    // int/double -> Distance
    void show() { cout << meters << "m"; }
};

int main() {
    Distance d = 5.5;    // implicit conversion: double -> Distance
    d.show();
}
```

**b) Class type → Basic type** (via an overloaded **conversion operator**, `operator TypeName()`):
```cpp
class Distance {
    double meters;
public:
    Distance(double m) { meters = m; }
    operator double() { return meters; }    // Distance -> double
};

int main() {
    Distance d(10.5);
    double val = d;         // implicit conversion: Distance -> double
    cout << val;
}
```

**c) Class type → Class type** — via a converting constructor of the destination class, or a conversion operator of the source class.

---

## Part B: Inheritance

### 1. Inheritance Basics

Inheritance allows a new class (**derived/child class**) to acquire properties and behaviors of an existing class (**base/parent class**), promoting **code reusability**.

```cpp
class Animal {                       // base class
public:
    void eat() { cout << "Eating...\n"; }
};

class Dog : public Animal {          // derived class
public:
    void bark() { cout << "Barking...\n"; }
};

int main() {
    Dog d;
    d.eat();    // inherited from Animal
    d.bark();
}
```

### 2. Types of Inheritance

| Type | Description |
|---|---|
| **Simple (Single)** | One base, one derived class |
| **Multi-level** | Derived class becomes base for another class (chain: A → B → C) |
| **Multiple** | One derived class from two or more base classes |
| **Hierarchical** | Multiple derived classes from one base class |
| **Hybrid** | Combination of two or more types above |

```cpp
// Single
class A {}; class B : public A {};

// Multilevel
class A {}; class B : public A {}; class C : public B {};

// Multiple
class A {}; class B {}; class C : public A, public B {};

// Hierarchical
class A {}; class B : public A {}; class C : public A {};
```

### 3. Modes of Inheritance

| Base member access | `public` inheritance | `protected` inheritance | `private` inheritance |
|---|---|---|---|
| public member becomes | public | protected | private |
| protected member becomes | protected | protected | private |
| private member becomes | not accessible (inaccessible directly) | not accessible | not accessible |

```cpp
class Base {
public:    int a;
protected: int b;
private:   int c;
};

class Derived : public Base {   // a stays public, b stays protected, c inaccessible
};
```

### 4. Overriding Member Functions

When a derived class defines a function with the **same name and signature** as one in the base class, it "hides"/overrides the base version for objects of the derived type.

```cpp
class Base {
public:
    void show() { cout << "Base::show()\n"; }
};

class Derived : public Base {
public:
    void show() { cout << "Derived::show()\n"; }   // overrides (hides) Base's show()
};

int main() {
    Derived d;
    d.show();          // Derived::show()
    d.Base::show();   // explicitly call Base's version
}
```

### 5. Order of Execution of Constructors and Destructors

- **Constructors** are called in order: **Base class constructor first, then derived class constructor** (top-down).
- **Destructors** are called in **reverse order**: derived class destructor first, then base class destructor (bottom-up).

```cpp
class Base {
public:
    Base() { cout << "Base constructor\n"; }
    ~Base() { cout << "Base destructor\n"; }
};

class Derived : public Base {
public:
    Derived() { cout << "Derived constructor\n"; }
    ~Derived() { cout << "Derived destructor\n"; }
};

int main() {
    Derived d;
}
/* Output:
Base constructor
Derived constructor
Derived destructor
Base destructor
*/
```

### 6. Resolving Ambiguities in Inheritance

Ambiguity arises in **multiple inheritance** when two base classes have a member with the same name — the compiler can't decide which one to use. Resolved using the **scope resolution operator**.

```cpp
class A { public: void show() { cout << "A::show\n"; } };
class B { public: void show() { cout << "B::show\n"; } };
class C : public A, public B {
public:
    void show() {              // resolve ambiguity by redefining in derived class
        A::show();
        B::show();
    }
};
```

### 7. Virtual Base Class

Used to solve the **"diamond problem"** — when a class inherits from two classes that both derive from a common base, causing duplicate copies of the common base's members. Declaring the common base as `virtual` ensures only **one shared copy** exists.

```cpp
class Person {
public:
    string name;
};

class Student : virtual public Person {};
class Employee : virtual public Person {};

class TeachingAssistant : public Student, public Employee {
    // only ONE copy of Person's members, no ambiguity
};

int main() {
    TeachingAssistant ta;
    ta.name = "Aarav";     // no ambiguity, thanks to virtual inheritance
}
```
Without `virtual`, `ta.name` would be ambiguous (compiler wouldn't know whether it's from `Student`'s `Person` or `Employee`'s `Person`).

### 8. Aggregation and Composition

Both represent a **"has-a"** relationship (as opposed to inheritance's "is-a"), where one class contains an object of another class as a member.

- **Composition**: strong ownership — the contained object's lifetime is tied to the container (created/destroyed with it). Example: a `Car` **has-a** `Engine`; the engine doesn't exist independently of the car.
- **Aggregation**: weak ownership — the contained object can exist independently and may be shared. Example: a `Department` **has** `Professors`, but professors exist even if the department is dissolved.

```cpp
// Composition — Engine created and destroyed with Car
class Engine {
public:
    Engine() { cout << "Engine built\n"; }
};
class Car {
    Engine e;         // Engine object is a member — composition
public:
    Car() { cout << "Car built\n"; }
};

// Aggregation — Professor exists independently, Department just references it
class Professor {
public:
    string name;
    Professor(string n) : name(n) {}
};
class Department {
    Professor *prof;    // just a pointer/reference — aggregation
public:
    Department(Professor *p) : prof(p) {}
};

int main() {
    Professor p("Dr. Rao");         // exists independently
    Department d(&p);                 // department just references it
}
```

---

## Solved Coding Questions

**Q1. Write a program to overload the `+`, `-`, and `==` operators for a `Complex` number class, and `<<` for display.**
```cpp
#include <iostream>
using namespace std;

class Complex {
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    Complex operator+(const Complex &c) { return Complex(real + c.real, imag + c.imag); }
    Complex operator-(const Complex &c) { return Complex(real - c.real, imag - c.imag); }
    bool operator==(const Complex &c) { return real == c.real && imag == c.imag; }
    friend ostream& operator<<(ostream &out, const Complex &c) {
        out << c.real << (c.imag >= 0 ? " + " : " - ") << abs(c.imag) << "i";
        return out;
    }
};

int main() {
    Complex c1(3, 4), c2(1, 2);
    cout << "Sum: " << (c1 + c2) << endl;
    cout << "Diff: " << (c1 - c2) << endl;
    cout << "Equal? " << (c1 == c2 ? "Yes" : "No") << endl;
    return 0;
}
```

**Q2. Write a program to demonstrate type conversion: basic-to-class and class-to-basic.**
```cpp
#include <iostream>
using namespace std;

class Fahrenheit {
    double temp;
public:
    Fahrenheit(double t) { temp = t; }   // basic type -> class type
    operator double() { return (temp - 32) * 5 / 9; }  // class type -> basic type (Celsius)
};

int main() {
    Fahrenheit f = 98.6;       // implicit basic-to-class conversion
    double celsius = f;         // implicit class-to-basic conversion
    cout << "Celsius: " << celsius << endl;
    return 0;
}
```

**Q3. Write a program to demonstrate all 4 basic types of inheritance in one file.**
```cpp
#include <iostream>
using namespace std;

// Single
class Animal { public: void eat() { cout << "Eating\n"; } };
class Dog : public Animal { public: void bark() { cout << "Barking\n"; } };

// Multilevel
class Puppy : public Dog { public: void weep() { cout << "Weeping\n"; } };

// Hierarchical
class Cat : public Animal { public: void meow() { cout << "Meowing\n"; } };

// Multiple
class Pet { public: void play() { cout << "Playing\n"; } };
class Trained { public: void obey() { cout << "Obeying\n"; } };
class TrainedPet : public Pet, public Trained {};

int main() {
    Puppy p; p.eat(); p.bark(); p.weep();     // multilevel
    Cat c; c.eat(); c.meow();                   // hierarchical
    TrainedPet tp; tp.play(); tp.obey();       // multiple
    return 0;
}
```

**Q4. Write a program to demonstrate ambiguity resolution in multiple inheritance, and the virtual base class fixing the diamond problem.**
```cpp
#include <iostream>
using namespace std;

class Person {
public:
    string name = "Unnamed";
};

class Student : virtual public Person {};
class Employee : virtual public Person {};

class TA : public Student, public Employee {};   // diamond, solved via virtual

int main() {
    TA t;
    t.name = "Meera";      // no ambiguity because Person is a single shared base
    cout << t.name << endl;
    return 0;
}
```

**Q5. Write a program demonstrating constructor/destructor execution order in inheritance, plus overriding a base function.**
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor\n"; }
    ~Base() { cout << "Base destructor\n"; }
    void greet() { cout << "Hello from Base\n"; }
};

class Derived : public Base {
public:
    Derived() { cout << "Derived constructor\n"; }
    ~Derived() { cout << "Derived destructor\n"; }
    void greet() { cout << "Hello from Derived\n"; Base::greet(); }   // override + explicit base call
};

int main() {
    Derived d;
    d.greet();
    return 0;
}
```

**Q6. Write a program to demonstrate composition (Car has-a Engine) vs aggregation (Library has-a Book that can exist independently).**
```cpp
#include <iostream>
using namespace std;

class Engine {
public:
    Engine() { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
};

class Car {                 // composition: Engine's life tied to Car
    Engine e;
public:
    Car() { cout << "Car created\n"; }
    ~Car() { cout << "Car destroyed\n"; }
};

class Book {
public:
    string title;
    Book(string t) : title(t) {}
};

class Library {              // aggregation: Book exists independently
    Book *b;
public:
    Library(Book *book) : b(book) {}
    void show() { cout << "Library has: " << b->title << endl; }
};

int main() {
    { Car c; }   // Engine created/destroyed with Car

    Book novel("The Hobbit");
    Library lib(&novel);
    lib.show();              // Book exists independent of Library
    return 0;
}
```

---

## Practice Coding Questions (Unsolved)

1. Overload the `[]` operator for a custom `Array` class to access elements like a normal array.
2. Overload `+=` and `-=` for a `Vector2D` class.
3. Write a class `Fraction` with a constructor for implicit `int → Fraction` conversion, and a conversion operator `Fraction → double`.
4. Design a class hierarchy: `Shape` (base) → `Shape2D` → `Circle`, `Rectangle` (multilevel + hierarchical), overriding an `area()` function in each.
5. Create classes `Father`, `Mother`, and `Child : public Father, public Mother` — demonstrate resolving ambiguity if both parents have a `skills()` function.
6. Simulate the diamond problem without `virtual`, observe the ambiguity error, then fix it using virtual inheritance.
7. Write a program modeling a `University` (aggregation with `Student` objects that can transfer to another university) vs a `House` (composition with `Room` objects that cease to exist when the house is demolished).
8. Overload the `<` operator for a `Student` class (compare by marks) and use it to find the topper in an array of students.

---

## Viva / Interview Questions

1. Which operators **cannot** be overloaded in C++?
2. Why must a binary operator overloaded as a friend function take two parameters, while as a member function it takes only one?
3. Why is `operator<<` typically overloaded as a friend function rather than a member function?
4. What is the difference between operator overloading and function overloading?
5. What is a converting constructor? How does the compiler use it implicitly?
6. What does the `explicit` keyword do, and why would you use it with a single-argument constructor?
7. Distinguish between pre-increment and post-increment operator overloading in terms of function signature.
8. What is the "is-a" vs "has-a" relationship, and which OOP concepts represent each?
9. In C++, what is the default mode of inheritance if none is specified for `class`? What about for `struct`?
10. What access level do `protected` base class members have in a derived class under `public`, `protected`, and `private` inheritance?
11. What is method overriding, and how is it different from method overloading?
12. Why are base class constructors called before derived class constructors?
13. Why are destructors called in reverse order of constructors in an inheritance hierarchy?
14. What is the "diamond problem" in multiple inheritance? Draw/describe the class hierarchy that causes it.
15. How does declaring a base class as `virtual` solve the diamond problem?
16. What's the difference between composition and aggregation — how does object lifetime differ?
17. Can you call a hidden base class function from a derived class object? How?
18. Why is multiple inheritance considered risky/complex in large codebases?
19. What happens if you don't provide any inheritance mode explicitly, like `class Derived : Base {}` — what's the default?
20. Explain how ambiguity in multiple inheritance is resolved using the scope resolution operator, with an example.