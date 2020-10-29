#include <iostream>
#include "ping.h"

void pong(int depth) {
    if (depth > 0) {
        std::cout << "pong" << std::endl;
        ping(depth - 1);
    }
}
