#include "../../include/runtime/MethodPool.h"
#include <iostream>

int main()
{
    std::cout << "Successful enter!" << std::endl;
    UBytePtr ptrB = new UChar[6];
    ptrB[0] = '\x22';
    ptrB[0] = '\x13';
    ptrB[0] = '\x09';
    ptrB[0] = '\x1b';
    ptrB[0] = '\x3c';
    auto res_pos = GenCodePool.Reserve(5, ptrB);
    std::cout << res_pos << std::endl;
    return 0;
}