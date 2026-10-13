# CIS-277 Assignment 2: Network Packet Arrival Queue
## Student
Logan Ganesh
## Design
The front index is the size of the queue divided by two. The reason why I did it this way was because I felt that it would be much easier to check my code logically. The expected outputs would have been easy to know as well. Rear was decided by the formula discussed in class, which is (front+count)%size. This made it much easier for rear to change indices. The front index is also made to change after a dequeue. The math that was used is front+1%size. This made it so that the front could be used to keep track of the oldest item in the queue. The queue was made to store the actual data that was being processed and used, while the memory pool was used to make and reuse memory blocks. Memory pool did absolutely nothing with the data, it neither processed nor returned any data, only blocks of a specified size of memory.
## How to Compile
Requires a C++ compiler such as g++. Open a terminal in the project folder and run:

g++ -std=c++17 -Wall -o packet_queue main.cpp PacketQueue.cpp MemoryPool.cpp

This produces an executable called packets.
## How to Run

./packet_queue

## Tests and Results
I tested the circular queue to make sure that it works as intended. To do that I just made a small queue, filled it with int variables, and output them to test to make sure that it worked. The expected output matched the actual output. The test of queue.h happened much earlier so it will not appear in the main.cpp. 

## Analysis Questions
Why must packet service be FIFO even though free-block reuse is LIFO?
Packet service must be FIFO because it matters which one came first and which one came last. Free-block reuse can be LIFO because it doesn't matter which or when blocks are taken or put back, just that they are there when they are needed. In other words, in packet service order matters, while in free-use block order doesn't matter.
How does your circular array wrap without shifting all waiting packets?
I move the front index whenever a dequeue happens. An alternative way would be to have a selector variable that keeps the index of the oldest index. I decided arbitrarily that I would just move front instead of having another variable.
What happens at queue overflow and underflow, and why must those attempts leave state unchanged?
At queue overflow false is returned ano nothing is changed, and at queue underflow false is returned and nothing changes. When a circular queue overflows, it can overwrite the first/oldest item in it before it was processed. It is possible the count can be below zero which would permanantly shorten the queue. These attempts much leave the state unchanged as it can lead to problems. 
What are the time complexities of queue operations and of receive/processNext when the packet has length bytes?
Queue operations should all be O(1) when the front and rear index is being tracked. receive/processNext would be O(length) since they have to copy the bytes from the parameter to the queue.
Why must processNext copy bytes out before returning the block to the pool?
The block becomes usable immediatly after it gets returned. If it returned a pointer to the block instead of copying the data, the data within the block would get corrupted since it would be the next block to be used.
## AI Use
I did use AI. I used it as a google search. I asked about things like errors and "how to declare an array as a private member and use it in the constructor of a class." I never copy and pasted code from the AI and I always double checked the code it did give me via other sources. I used AI to help fill out the How to Compile and How to Run sections of the README.