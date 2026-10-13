#include "MyStack.h"
#include <vector>

class MemoryPool
{
public:
    MemoryPool(size_t blockSize, size_t blockCount);
    ~MemoryPool();

    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;

    void* allocate();
    bool deallocate(void* ptr);

    size_t availableBlocks() const;
    size_t allocatedBlocks() const;
    size_t blockSize() const;
    size_t capacity() const;

    private:
    size_t size, count;
    unsigned char* mem;
    MyStack <unsigned char*> freeBlocks;
    std::vector<bool> inUse;
};