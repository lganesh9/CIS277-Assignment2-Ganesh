#include "MemoryPool.h"

    MemoryPool::MemoryPool(size_t blockSize, size_t blockCount){
        size = blockSize;
        count = blockCount;
        inUse.assign(count, false);
        mem = new unsigned char[size*count];
        for(size_t i = 0; i < count; i++){freeBlocks.push(mem + i * size);}
    }
    MemoryPool::~MemoryPool(){delete[] mem;}

    void* MemoryPool::allocate(){
        if (freeBlocks.empty())
        return nullptr;
        unsigned char* p = freeBlocks.pop();
        inUse[(p - mem) / size] = true;
        return p;
    }

    bool MemoryPool::deallocate(void* ptr){
        unsigned char* temp = static_cast<unsigned char*>(ptr);
        if (temp == nullptr) return false;
        if (temp < mem || temp >= mem + size * count) return false;
        if ((temp - mem) % size != 0) return false;

        size_t idx = (temp - mem) / size;
        if (!inUse[idx]) return false;
        inUse[idx] = false;
        freeBlocks.push(temp);
        return true;
    }

    size_t MemoryPool::availableBlocks() const{return freeBlocks.size();}
    size_t MemoryPool::allocatedBlocks() const{return count - freeBlocks.size();}
    size_t MemoryPool::blockSize() const{return size;}
    size_t MemoryPool::capacity() const{return size*count;}

