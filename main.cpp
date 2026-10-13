#include <iostream>
#include <vector>
#include <cstddef>
#include "PacketQueue.h"

using namespace std;

int main()
{
    PacketQueue packQue(512, 5);
    size_t idOne = 1, idTwo = 2, idThree = 3, idFour = 4, idFive = 5;
    static const unsigned char payload1[] = {'P', 'K', 'T', '-', 'A', '0', '0', '1'};
    static_assert(sizeof(payload1) == 8);
    static const unsigned char payload2[] = {
        'P', 'A', 'Y', 'L', 'O', 'A', 'D', '-', 'B', '-', '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'};
    static_assert(sizeof(payload2) == 32);
    static unsigned char payload3[64];
    for (std::size_t i = 0; i < sizeof(payload3); ++i)
        payload3[i] = static_cast<unsigned char>(i);
    static const unsigned char payloadShort[] = { 0x00 };
    static_assert(sizeof(payloadShort) == 1);
    static unsigned char payloadMax[512];
    for (std::size_t i = 0; i < sizeof(payloadMax); ++i)
        payloadMax[i] = static_cast<unsigned char>((i * 31 + 7) % 256);
    size_t length1 = sizeof(payload1), length2 = sizeof(payload2), length3 = sizeof(payload3);
    size_t length4 = sizeof(payloadShort), length5 = sizeof(payloadMax);

    vector <unsigned char> output;
    size_t idOutput = 0;

    cout << "Attempting to receive the first payload... \n";
    if (!packQue.receive(idOne, payload1, length1))
    cout << "Rejected - the queue cannot recieve the input\n";

    cout << "Attempting to receive the second payload... \n";
    if (!packQue.receive(idTwo, payload2, length2))
    cout << "Rejected - the queue cannot recieve the input\n";

    cout << "There are " << packQue.pending() << " packets that are in queue\n";
    //should output 2

    cout << "Attempting to process the first payload... \n";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    cout << "The ID of the payload is " << idOutput << " the contents are: \n";
    for (unsigned char i : output)
    cout << i << " ";

    cout << "\nAfter processing one packet, there are now " << packQue.availableBlocks() << " available blocks in the queue\n";
    //Should output 4

    cout << "Attempting to receive the third payload... \n";
    if (!packQue.receive(idThree, payload3, length3))
    cout << "Rejected - the queue cannot recieve the input\n";

    cout << "Attempting to process the second payload... \n";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    cout << "The ID of the payload is " << idOutput << " the contents are: \n";
    for (unsigned char i : output)
    cout << i << " ";

    cout << "\nAttempting to process the third payload... \n";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    cout << "The ID of the payload is " << idOutput << " the contents are: \n";
    for (unsigned char i : output)
    cout << hex << static_cast<int>(i) << " ";

    cout << "\nFilling the queue...\n";
    if (!packQue.receive(idOne, payload1, length1))
    cout << "Rejected - the queue cannot recieve the input\n";
    if (!packQue.receive(idTwo, payload2, length2))
    cout << "Rejected - the queue cannot recieve the input\n";
    if (!packQue.receive(idThree, payload3, length3))
    cout << "Rejected - the queue cannot recieve the input\n";
    if (!packQue.receive(idFive, payloadMax, length5))
    cout << "Rejected - the queue cannot recieve the input\n";
    if (!packQue.receive(idFour, payloadShort, length4))
    cout << "Rejected - the queue cannot recieve the input\n";

    cout << "Attempting to overflow...\n";
    if (!packQue.receive(idOne, payload1, length1))
    cout << "Rejected - the queue cannot recieve the input\n";

    cout << "Draining queue with outputting a payload of size 512 and size 1";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";

    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    cout << "\nThe ID of the payload is " << idOutput << " the contents are: \n";
    for (unsigned char i : output)
    cout << hex << static_cast<int>(i) << " ";

    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";
    cout << "\nThe ID of the payload is " << idOutput << " the contents are: \n";
    for (unsigned char i : output)
    cout << hex << static_cast<int>(i) << " ";

    cout << "\nAttempting to process with no packets waiting...\n";
    if (!packQue.processNext(idOutput, output))
    cout << "Could not process because there is no waiting packet\n";

    cout << "Outputting vector...\n";
    for (unsigned char i : output)
    cout << hex << static_cast<int>(i) << " ";
}