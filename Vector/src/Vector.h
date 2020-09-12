/*
    Vector: Dynamic array container with minimal interface.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

template<typename T>
class Vector
{
public:
    [[nodiscard]]
    bool Add(T item)
    {
        // reallocate to fit and add new element
        if (m_size == m_capacity)
            Reserve(m_capacity + 1);

        m_data[m_size] = item;
        m_size++;
    }

    void Remove(size_t index)
    {
        if (index >= m_size)
            return;

        m_size--;
        for (size_t i = index; i < m_size; ++i)
            m_data[i] = m_data[i + 1]; // overwrite free slot and move it at the end for O(1) addition
    }

    void Clear()
    {
        if (m_data)
        {
            delete [] m_data;
            m_data = nullptr;
        }

        m_size = 0;
        m_capacity = 0;
    }

    size_t Size() const { return m_size; }

    void Reserve(size_t capacity)
    {
        if (m_capacity >= capacity)
            return;

        if (m_data && m_size > 0) // existing elements
        {
            auto newData = new T[capacity]; // allocate for new capacity
            for (size_t i = 0; i < m_size; ++i)
                newData[i] = m_data[i]; // copy existing elements to new array

            delete [] m_data; // deallocate old array
            m_data = newData; // point to new array
        }
        else // empty
        {
            m_data = new T[capacity];
        }

        m_capacity = capacity;
    }

    const T* operator[](size_t index) const
    {
        if (index >= m_size)
            return nullptr;

        return &m_data[index];
    }

private:
    T* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
};