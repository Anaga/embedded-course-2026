# Lesson 07 — Inheritance, Templates, Data Structures

Embedded Systems Course 2026 | ESP32-C3 Super Mini

---

## Overview

This lesson builds on the `point` class from Lesson 6. We introduce:
- Inheritance (`circle` and `rectangle` derived from `point`)
- Virtual functions and polymorphism
- Template functions (`myMax`, `myMin`, `myClamp`)
- Template class: `RingBuffer` — the essential embedded data structure

---

## Project Structure

```
lesson7-inheritance/
  include/
    point.h         Base class (protected x, y, virtual print)
    circle.h        Derived: adds radius, area(), circumference()
    rectangle.h     Derived: adds width, height, area(), perimeter()
    RingBuffer.h    Template ring buffer (fully in header)
    util.h          Template utility functions (fully in header)
  src/
    point.cpp       Base class implementation
    circle.cpp      Circle implementation
    rectangle.cpp   Rectangle implementation
    main.cpp        Template with exercises
  platformio.ini
```

---

## Wiring

### Button — GPIO 0

| Pin | Connect to          |
|-----|---------------------|
| IO0 | One leg of button   |
| GND | Other leg of button |

Internal pull-up enabled.

---

## Key Concepts

### Inheritance

```cpp
class circle : public point {   // circle IS-A point
private:
    uint8_t radius_;
public:
    circle(uint8_t x, uint8_t y, uint8_t r)
        : point(x, y)           // call base constructor first
        , radius_(r) {}
};
```

`circle` inherits `x`, `y`, `print()`, `moveX()`, `moveY()` from `point`.
It only adds what is new: `radius_`, `area()`, `circumference()`.

### protected vs private

- `private`: only this class can access
- `protected`: this class AND its children can access
- `public`: everyone can access

We changed `x, y` from `private` to `protected` so `circle` and
`rectangle` can use them directly.

### Virtual functions

```cpp
class point {
public:
    virtual void print() const;    // can be overridden
    virtual ~point();              // always virtual if class has virtual methods
};

class circle : public point {
public:
    void print() const override;   // override = compiler checks for you
};
```

### Templates

```cpp
template<typename T>
T myMax(T a, T b) { return (a > b) ? a : b; }
```

Template code must live in the header file. The compiler generates
a separate function for each type used — zero runtime cost.

### RingBuffer

Fixed-size circular buffer. No heap allocation, O(1) push/peek.
When full, new items overwrite the oldest.

---

## Exercises

1. Uncomment `circle` and `rectangle` — call `print()`, `area()`.
2. Uncomment the `point*` array — observe virtual dispatch.
3. Uncomment `myMax()` tests — test with different types.
4. Uncomment `RingBuffer` — push random points on button press.
5. BONUS: find the shape with the largest area.
