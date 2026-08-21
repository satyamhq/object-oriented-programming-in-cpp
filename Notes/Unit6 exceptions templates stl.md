# CSE202 — Object Oriented Programming
## UNIT VI: Exception Handling, Templates and Standard Template Library (STL)

---

## Part A: Exception Handling

### 1. Basics of Exception Handling

An **exception** is a runtime anomaly (error) that disrupts the normal flow of a program (e.g., division by zero, invalid array access, file-not-found). C++ provides a structured way to detect and respond to such errors using `try`, `catch`, and `throw`, avoiding abrupt program termination.

### 2. Exception Handling Mechanism

Three keywords work together:
- **`try`** — block of code that might throw an exception
- **`throw`** — signals that an exceptional condition has occurred, and "throws" an exception object
- **`catch`** — block that handles a specific type of exception

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 0;
    try {
        if (b == 0) throw runtime_error("Division by zero!");
        cout << a / b;
    }
    catch (runtime_error &e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}
```

### 3. Throwing Mechanism

Any data type can be thrown — an int, a string, a custom object, or a standard exception class (`std::exception` and its derivatives from `<stdexcept>`, like `runtime_error`, `logic_error`, `out_of_range`, `invalid_argument`).

```cpp
void checkAge(int age) {
    if (age < 18)
        throw invalid_argument("Age must be 18 or older");
    cout << "Age accepted\n";
}
```

**Custom exception class:**
```cpp
class MyException : public exception {
public:
    const char* what() const throw() {
        return "Custom exception occurred";
    }
};

try {
    throw MyException();
} catch (MyException &e) {
    cout << e.what();
}
```

### 4. Catching Mechanism

- A `try` block can be followed by **multiple `catch` blocks**, each handling a different exception type — checked top to bottom, first match wins.
- `catch (...)` — a catch-all handler that catches **any** exception type (used as a last resort/fallback).

```cpp
try {
    throw 3.14;              // throwing a double
}
catch (int e) {
    cout << "Caught int\n";
}
catch (double e) {
    cout << "Caught double: " << e << endl;
}
catch (...) {
    cout << "Caught unknown exception\n";
}
```

### 5. Rethrowing an Exception

A `catch` block can partially handle an exception (e.g., log it) and then **rethrow** it using `throw;` (no argument) so an outer handler can also process it.

```cpp
void process() {
    try {
        throw runtime_error("Something failed");
    }
    catch (runtime_error &e) {
        cout << "Logged: " << e.what() << endl;
        throw;                  // rethrow the same exception
    }
}

int main() {
    try {
        process();
    }
    catch (runtime_error &e) {
        cout << "Handled again in main: " << e.what() << endl;
    }
}
```

---

## Part B: Templates

### 1. Function Template

A **generic blueprint** for a function that works with any data type — the compiler generates a specific version of the function for each type used, at compile time.

```cpp
template <typename T>
T maxVal(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << maxVal(5, 10) << endl;        // T = int
    cout << maxVal(3.5, 2.1) << endl;     // T = double
    cout << maxVal('a', 'z') << endl;      // T = char
}
```

### 2. Class Template

Similarly, an entire class can be made generic.

```cpp
template <class T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T getValue() { return value; }
};

int main() {
    Box<int> intBox(10);
    Box<string> strBox("Hello");
    cout << intBox.getValue() << " " << strBox.getValue();
}
```

### 3. Class Template with Inheritance

Templates and inheritance combine naturally — a derived class can inherit from a template base class (either keeping it generic or fixing the type).

```cpp
template <class T>
class Base {
protected:
    T value;
public:
    Base(T v) : value(v) {}
};

template <class T>
class Derived : public Base<T> {
public:
    Derived(T v) : Base<T>(v) {}
    void show() { cout << "Value: " << this->value << endl; }   // 'this->' needed for base template members
};

int main() {
    Derived<int> d(100);
    d.show();
}
```

### 4. Introduction to STL — Containers, Algorithms, and Iterators

The **Standard Template Library (STL)** is a set of generic, reusable, template-based classes and functions, built on three core components:

| Component | Description | Examples |
|---|---|---|
| **Containers** | Store collections of objects | `vector`, `list`, `map`, `set`, `stack`, `queue` |
| **Algorithms** | Operate on containers (via iterators) | `sort()`, `find()`, `reverse()`, `count()` |
| **Iterators** | "Generalized pointers" to traverse containers | `begin()`, `end()`, `iterator`, `const_iterator` |

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v = {5, 2, 8, 1};
sort(v.begin(), v.end());               // algorithm + iterators
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it << " ";
```

### 5. Container: Vector

`vector` is a **dynamic array** — resizes automatically, supports random access via `[]`, and provides efficient insertion/removal at the end.

| Function | Purpose |
|---|---|
| `push_back(x)` | add element at end |
| `pop_back()` | remove last element |
| `size()` | number of elements |
| `at(i)` / `[i]` | access element (bounds-checked / unchecked) |
| `begin()` / `end()` | iterators to start/past-end |
| `clear()` | remove all elements |
| `empty()` | check if container is empty |
| `insert(pos, x)` | insert at iterator position |
| `erase(pos)` | remove element at iterator position |

```cpp
vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);
cout << v.size() << endl;         // 3
cout << v[1] << endl;                // 20
v.pop_back();
for (int x : v) cout << x << " ";  // range-based for loop with iterators internally
```

### 6. Container: List

`list` is a **doubly linked list** — efficient insertion/deletion anywhere (O(1)), but no random access (`[]` not supported; must use iterators).

| Function | Purpose |
|---|---|
| `push_back(x)` / `push_front(x)` | add at end/front |
| `pop_back()` / `pop_front()` | remove from end/front |
| `insert(pos, x)` | insert before iterator position |
| `erase(pos)` | remove element |
| `sort()` | sort the list (member function, not `<algorithm>`) |
| `reverse()` | reverse the list |

```cpp
#include <list>
list<int> l = {3, 1, 4, 1, 5};
l.push_front(0);
l.sort();
for (int x : l) cout << x << " ";   // 0 1 1 3 4 5
```

---

## Solved Coding Questions

**Q1. Write a program to demonstrate exception handling for division by zero using multiple catch blocks.**
```cpp
#include <iostream>
using namespace std;

double divide(int a, int b) {
    if (b == 0) throw runtime_error("Division by zero");
    return (double)a / b;
}

int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    try {
        cout << "Result: " << divide(a, b) << endl;
    }
    catch (runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred\n";
    }
    return 0;
}
```

**Q2. Write a program with a custom exception class for an invalid bank withdrawal.**
```cpp
#include <iostream>
using namespace std;

class InsufficientFundsException : public exception {
    string msg;
public:
    InsufficientFundsException(string m) : msg(m) {}
    const char* what() const throw() { return msg.c_str(); }
};

class Account {
    double balance;
public:
    Account(double b) : balance(b) {}
    void withdraw(double amt) {
        if (amt > balance)
            throw InsufficientFundsException("Insufficient balance for this withdrawal");
        balance -= amt;
        cout << "Withdrawal successful. New balance: " << balance << endl;
    }
};

int main() {
    Account acc(1000);
    try {
        acc.withdraw(1500);
    } catch (InsufficientFundsException &e) {
        cout << "Transaction failed: " << e.what() << endl;
    }
    return 0;
}
```

**Q3. Write a program demonstrating rethrowing an exception across two functions.**
```cpp
#include <iostream>
using namespace std;

void innerFunc() {
    throw out_of_range("Index out of bounds");
}

void outerFunc() {
    try {
        innerFunc();
    }
    catch (out_of_range &e) {
        cout << "outerFunc logging: " << e.what() << endl;
        throw;   // rethrow to caller
    }
}

int main() {
    try {
        outerFunc();
    }
    catch (out_of_range &e) {
        cout << "main handling: " << e.what() << endl;
    }
    return 0;
}
```

**Q4. Write a function template to find the maximum of 3 values of any comparable type, and a class template for a generic Pair.**
```cpp
#include <iostream>
using namespace std;

template <typename T>
T maxOfThree(T a, T b, T c) {
    T m = (a > b) ? a : b;
    return (m > c) ? m : c;
}

template <class T1, class T2>
class Pair {
    T1 first;
    T2 second;
public:
    Pair(T1 a, T2 b) : first(a), second(b) {}
    void show() { cout << "(" << first << ", " << second << ")" << endl; }
};

int main() {
    cout << maxOfThree(3, 7, 5) << endl;
    cout << maxOfThree(2.5, 1.2, 9.9) << endl;

    Pair<int, string> p(1, "Apple");
    p.show();
    return 0;
}
```

**Q5. Write a program demonstrating a class template with inheritance (generic Stack with a bounded/safe variant).**
```cpp
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack {
protected:
    vector<T> data;
public:
    void push(T val) { data.push_back(val); }
    T pop() {
        T top = data.back();
        data.pop_back();
        return top;
    }
    bool isEmpty() { return data.empty(); }
};

template <class T>
class BoundedStack : public Stack<T> {
    int maxSize;
public:
    BoundedStack(int m) : maxSize(m) {}
    void push(T val) {
        if ((int)this->data.size() >= maxSize) {
            cout << "Stack overflow!\n";
            return;
        }
        Stack<T>::push(val);
    }
};

int main() {
    BoundedStack<int> s(3);
    s.push(1); s.push(2); s.push(3); s.push(4);   // 4th triggers overflow message
    while (!s.isEmpty()) cout << s.pop() << " ";
    return 0;
}
```

**Q6. Write a program using STL `vector` and algorithms (`sort`, `find`, `reverse`) and iterators.**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {40, 10, 30, 20, 50};

    sort(v.begin(), v.end());
    cout << "Sorted: ";
    for (auto it = v.begin(); it != v.end(); ++it) cout << *it << " ";
    cout << endl;

    auto pos = find(v.begin(), v.end(), 30);
    if (pos != v.end()) cout << "Found 30 at index: " << (pos - v.begin()) << endl;

    reverse(v.begin(), v.end());
    cout << "Reversed: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    return 0;
}
```

**Q7. Write a program using STL `list` to maintain a sorted list of tasks (insertion + sort + display).**
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> tasks;
    tasks.push_back("Write report");
    tasks.push_front("Fix bug");
    tasks.push_back("Attend meeting");

    tasks.sort();      // alphabetical sort

    cout << "Tasks (sorted):\n";
    for (auto it = tasks.begin(); it != tasks.end(); ++it)
        cout << "- " << *it << endl;

    tasks.reverse();
    cout << "Reversed order:\n";
    for (const string &t : tasks) cout << "- " << t << endl;
    return 0;
}
```

---

## Practice Coding Questions (Unsolved)

1. Write a program that validates user input for an integer between 1–100 using exception handling, re-prompting on invalid input.
2. Create a custom exception hierarchy: `AppException` (base) → `FileException`, `NetworkException` (derived), and demonstrate catching the base type to handle either.
3. Write a function template `swapValues(T &a, T &b)` that works for int, double, and string; test all three.
4. Write a class template `Queue<T>` (using STL `vector` internally) with `enqueue()`, `dequeue()`, and `isEmpty()`.
5. Write a program using STL `map` to count the frequency of each word in a sentence (research `map` briefly — it's a key STL container beyond what's covered above).
6. Write a program combining exception handling and templates: a generic `safeDivide<T>(T a, T b)` function template that throws if `b == 0`.
7. Write a program using `vector` and the `<algorithm>` functions `count()`, `min_element()`, and `max_element()` on a list of exam scores.
8. Implement a simple `Stack<T>` template class from scratch (not using STL `vector` internally) using a dynamic array, with overflow/underflow exception handling.

---

## Viva / Interview Questions

1. What are the three keywords involved in C++ exception handling, and what role does each play?
2. What is the difference between `throw` (with an argument) and `throw;` (rethrow, no argument)?
3. Can you have multiple `catch` blocks for a single `try` block? How does the compiler decide which one executes?
4. What does `catch (...)` do, and when should it be used?
5. Why should `catch` blocks typically catch exceptions **by reference** (`catch (MyException &e)`) rather than by value?
6. What is `std::exception`, and why is it good practice to derive custom exceptions from it?
7. What happens if an exception is thrown but never caught anywhere in the program?
8. What is the purpose of the `what()` method in exception classes?
9. What is a function template, and how does the compiler generate code from it (template instantiation)?
10. What is the difference between `template <class T>` and `template <typename T>`? (Hint: functionally identical.)
11. Why do we sometimes need `this->` when accessing a base class template member inside a derived template class?
12. What is the STL, and what are its three main components?
13. What is the difference between an iterator and a pointer, conceptually?
14. When would you choose `list` over `vector`, and vice versa? Compare their time complexities for insertion and random access.
15. What does `v.begin()` and `v.end()` return, and why is `end()` described as "one past the last element"?
16. What's the difference between `v.at(i)` and `v[i]` in a `vector`? Which one throws an exception on an invalid index?
17. Can class templates be combined with inheritance? Give a short example use case.
18. What is exception "stack unwinding," and how does it relate to destructors being called as the stack unwinds?
19. What is the time complexity of `push_back()` on a `vector` in the amortized sense, and why can it occasionally be more expensive?
20. Why can't `list` elements be accessed using the `[]` operator like `vector`?