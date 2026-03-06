/**
 * @file util.h
 * @brief Template utility functions.
 *
 * Lesson 07 — Inheritance, Templates, Data Structures
 * Embedded Systems Course 2026
 *
 * Templates must be fully defined in the header — no .cpp file.
 */
#pragma once

/**
 * @brief Return the larger of two values.
 */
template<typename T>
T myMax(T a, T b)
{
    return (a > b) ? a : b;
}

/**
 * @brief Return the smaller of two values.
 */
template<typename T>
T myMin(T a, T b)
{
    return (a < b) ? a : b;
}

/**
 * @brief Clamp a value to [lo, hi] range.
 */
template<typename T>
T myClamp(T value, T lo, T hi)
{
    if (value < lo) return lo;
    if (value > hi) return hi;
    return value;
}
