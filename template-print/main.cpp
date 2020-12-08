#include <stdlib.h>
#include <iostream>
#include <vector>

template<class... Args>
void print(Args... args) {
    std::vector<int> numbers = {args...};
   for (unsigned i = 0; i < numbers.size(); ++i) {
       std::cout << numbers[i] << " ";
   }
    std::cout << std::endl;
}

int main(void) {
    print(1, 2, 3);
    print(1, 2);
    print(1);
    print();
}
