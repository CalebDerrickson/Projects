#pragma once
#include <iostream>

class DynamicAllocator{
public:
    DynamicAllocator();
    DynamicAllocator(size_t size);
    ~DynamicAllocator();

    void* allocate(size_t size);
    void reset();

private:
    void grow(size_t size);

    void* _memory;
    size_t _currentSize;
    size_t _offset;
};