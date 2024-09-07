#include "LinearAllocator.hpp"
#include <memory>

LinearAllocator::LinearAllocator()
    : _totalSize(2 << 10),
      _offset(0)
{
    _memory = std::malloc(_totalSize);

    std::cout<<"Linear Allocator: Allocating "<<_totalSize<<" bytes of memory."<<std::endl;
}

LinearAllocator::LinearAllocator(size_t size)
    : _totalSize(size),
      _offset(0)
{
    _memory = std::malloc(_totalSize);

    std::cout<<"Allocating "<<_totalSize<<" bytes of memory."<<std::endl;
}

LinearAllocator::~LinearAllocator()
{
    std::free(_memory);

}

void* LinearAllocator::allocate(size_t size)
{
    if (_offset + size > _totalSize) {
        return nullptr;
    }

    void* ptr = (char*)_memory + _offset;
    _offset += size;

    return ptr; 
}

void LinearAllocator::reset()
{
    _offset = 0;

}


