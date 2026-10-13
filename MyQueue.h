#include <cstddef>

template <typename T>

class Queue
{
public:
    explicit Queue(std::size_t capacity){
        arr = new T[capacity];
        count = 0;
        frontIndex = capacity / 2;
        rear = frontIndex;
        arrSize = capacity;
    }
    ~Queue(){ delete[] arr;}
    bool enqueue(const T& value){
        if (full())
        return false;
        arr[rear] = value;
        count++;
        rear = (frontIndex + count) % arrSize;
        return true;
    }
    bool dequeue(T& value){
        if (empty())
        return false;
        value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % arrSize;
        count--;
        return true;

    }
    bool front(T& value) const{
        if (empty())
        return false;
        value = arr[frontIndex];
        return true;
    }
    bool empty() const{
        return count == 0;
    }
    bool full() const{
        return count == arrSize; 
    }
    std::size_t size() const{
        return arrSize;
    }
    std::size_t capacity() const{
        return count;
    }
private:
    T* arr;
    std::size_t frontIndex, rear, count, arrSize;
};