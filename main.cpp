#include <iostream>
#include "Array.h"

int main() {
    Array<int> a1, a2, a3, a4;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    a2 = a1;
    std::cout << a2 << std::endl;
    std::cin >> a3 >> a4;
    std::cout << a3 << "\n" << a4 << std::endl;

    Array<double> b;
    b.push_back(1.1);
    b.push_back(2.2);

    std::cout << b << std::endl;

    a1.pop_back();
    std::cout << a1 << std::endl;

    std::cout << a1.size() << std::endl;

    a1.swap(a3);
    std::cout << a1 << std::endl;
    a3.clear();
    std::cout << "a3 empty ?: " << a3.empty() << std::endl;

    return 0;
}
