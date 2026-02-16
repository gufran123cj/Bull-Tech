#include <cstdlib>
#include <iostream>

void update(int& a, int& b) {//correct implementations better than pointer implementation
    a += b;
    b = std::abs(a - b);
}

int main() {
    int a, b;
    std::cout << "Enter two numbers (a b): ";
    std::cin >> a >> b;
    std::cout << "Initially - a address: " << static_cast<const void*>(&a)
              << "  b address: " << static_cast<const void*>(&b) << '\n';
    update(a, b);
    std::cout << "Result (a b): " << a << ' ' << b << '\n';
    std::cout << "Finally - a address: " << static_cast<const void*>(&a)
              << "  b address: " << static_cast<const void*>(&b) << '\n';
    return 0;
}
