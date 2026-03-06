/**
 * @file circle.h
 * @brief Circle class — inherits from point.
 *
 * Lesson 07 — Inheritance, Templates, Data Structures
 * Embedded Systems Course 2026
 */
#pragma once

#include "point.h"

class circle : public point {
private:
    uint8_t radius_;

public:
    circle(uint8_t x, uint8_t y, uint8_t radius);
    ~circle() override;

    void print() const override;

    uint8_t radius() const;
    float   area() const;
    float   circumference() const;
};
