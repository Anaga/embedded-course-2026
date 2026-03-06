/**
 * @file RingBuffer.h
 * @brief Template ring buffer — fixed-size, no allocation.
 *
 * Lesson 07 — Inheritance, Templates, Data Structures
 * Embedded Systems Course 2026
 *
 * NOTE: Template classes must be fully implemented in the header.
 *       There is no RingBuffer.cpp — this is by design.
 */
#pragma once

#include <stdint.h>

template<typename T, uint8_t SIZE>
class RingBuffer {
private:
    T       buf_[SIZE];
    uint8_t head_;      // next write position
    uint8_t count_;     // number of items currently stored

public:
    RingBuffer()
        : head_(0)
        , count_(0)
    {
    }

    /**
     * @brief Push an item into the buffer.
     *
     * If the buffer is full, the oldest item is overwritten.
     */
    void push(const T& item)
    {
        buf_[head_] = item;
        head_ = (head_ + 1) % SIZE;
        if (count_ < SIZE) {
            count_++;
        }
    }

    /**
     * @brief Peek at an item by age.
     *
     * @param age 0 = newest, 1 = second newest, etc.
     * @return Copy of the item.
     */
    T peek(uint8_t age = 0) const
    {
        uint8_t idx = (head_ - 1 - age + SIZE) % SIZE;
        return buf_[idx];
    }

    /**
     * @brief Access item by age (non-const).
     */
    T& at(uint8_t age)
    {
        uint8_t idx = (head_ - 1 - age + SIZE) % SIZE;
        return buf_[idx];
    }

    /** @brief Number of items currently stored. */
    uint8_t count() const { return count_; }

    /** @brief True if the buffer contains SIZE items. */
    bool full() const { return count_ == SIZE; }

    /** @brief True if the buffer is empty. */
    bool empty() const { return count_ == 0; }

    /** @brief Maximum capacity. */
    uint8_t capacity() const { return SIZE; }

    /** @brief Remove all items. */
    void clear()
    {
        head_  = 0;
        count_ = 0;
    }
};
