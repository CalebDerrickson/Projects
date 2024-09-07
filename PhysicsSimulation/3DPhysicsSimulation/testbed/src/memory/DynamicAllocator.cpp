#include "DynamicAllocator.hpp"
#include <memory>

DynamicAllocator::DynamicAllocator() 
    : _currentSize(2 << 10),
      _offset(0)
{
    _memory = std::malloc(_currentSize);
    std::cout<<"Dynamic Allocator: Allocating "<<_currentSize<<" bytes of memory."<<std::endl;
}

DynamicAllocator::DynamicAllocator(size_t size)
    : _currentSize(size),
      _offset(0)
{
    _memory = std::malloc(_currentSize);
    std::cout<<"Dynamic Allocator: Allocating "<<_currentSize<<" bytes of memory."<<std::endl;
}

DynamicAllocator::~DynamicAllocator()
{
    std::free(_memory);

}

void* DynamicAllocator::allocate(size_t size)
{
    if (_offset + size > _currentSize) {
        grow(size);
    }
    void* ptr = (char*)_memory + _offset;
    _offset += size;
    
    return ptr;
}

void DynamicAllocator::reset()
{
    _offset = 0;

}

void DynamicAllocator::grow(size_t size)
{
    size_t newSize = _currentSize * 2;
    if (_offset + size > newSize) {
        newSize += _offset;
    }

    void* newMemory = std::realloc(_memory, newSize);
    if (newMemory) {
        _memory = newMemory;
        _currentSize = newSize;
    } 
    else {
        std::cerr<<"Failed to reallocate dynamic allocator"<<std::endl;
        exit(1);
    }

}