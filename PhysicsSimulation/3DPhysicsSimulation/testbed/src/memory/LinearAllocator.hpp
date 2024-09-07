#pragma once 
#include "utils.hpp"
#include <iostream>

class LinearAllocator {
public:

    // Default constructor will allocate 1 kB of space
    LinearAllocator();
    LinearAllocator(size_t size);
    ~LinearAllocator();

    void* allocate(size_t size);

    void reset();


private:

    void* _memory;
    size_t _totalSize;
    size_t _offset;
};