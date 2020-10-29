#include <iostream>
#include "pong.h"

void ping(int depth) {
    if (depth > 0) {
        std::cout << "ping" << std::endl;
        pong(depth - 1);
    }
}
