#include "PacketQueue.h"

PacketQueue::PacketQueue(std::size_t blockSize, std::size_t blockCount)
    : size(blockSize),
      pool(blockSize, blockCount),
      q(blockCount){}

bool PacketQueue::receive(std::size_t id, const unsigned char *bytes, std::size_t length)
{
    if (length == 0 || length > size)
        return false;
    if (pool.availableBlocks() == 0 || q.full())
        return false;
    if(bytes == NULL)
    return false;
    PacketDescriptor temp;
    temp.block = pool.allocate();
    memcpy(temp.block, bytes, length);
    temp.id = id;
    temp.length = length;
    return q.enqueue(temp);
}
bool PacketQueue::processNext(std::size_t &id, std::vector<unsigned char> &bytes){
    if (q.empty())
    return false;
    PacketDescriptor temp;
    q.dequeue(temp);
    bytes.resize(temp.length);
    memcpy(bytes.data(), temp.block, temp.length);
    id = temp.id;
    pool.deallocate(temp.block);
    return true;
}

std::size_t PacketQueue::pending() const { return q.capacity(); }
std::size_t PacketQueue::availableBlocks() const { return pool.availableBlocks(); }
