/*
    Array: Static array container with minimal interface.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

template<typename T, size_t N>
class Array
{
public:
    Array() : m_capacity(N){}
    ~Array() = default;

    [[nodiscard]]
    bool Add(T item)
    {
        if (m_count == m_capacity)
            return false;

        m_data[m_count] = item;
        m_count++;

        return true;
    }

    void Remove(size_t index)
    {
        if (index >= m_count)
            return;

        m_count--;
        for (size_t i = index; i < m_count; ++i)
            m_data[i] = m_data[i + 1]; // overwrite free slot and move it at the end for O(1) addition
    }

    void Clear()
    {
        m_count = 0;
    }

    size_t Count() const
    {
        return m_count;
    }

    const T* operator[](size_t index) const
    {
        if (index >= m_count)
            return nullptr;

        return &m_data[index];
    }

private:
    T m_data[N] = {};
    size_t m_count = 0;
    const size_t m_capacity = 0;
};