#include "smallest.hpp"
#include <iostream>
#include <string>

struct Point {
    int x;
    bool operator<(const Point& o) const { return x < o.x; }
};
std::ostream& operator<<(std::ostream& o, const Point& p) { return o << p.x; }

template <typename T>
static void print_array_with_addresses(const T* arr, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << "  [" << i << "] value=" << arr[i]
                  << "  addr=" << static_cast<const void*>(&arr[i]) << '\n';
}

int main() {
    int arr[] = {30, 10, 50, 20, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "--- Array (int) ---\n";
    std::cout << "Input: ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << (i + 1 < n ? ", " : "\n");
    std::cout << "start = " << static_cast<const void*>(arr) << "  length = " << n << '\n';
    std::cout << "Array (with addresses):\n";
    print_array_with_addresses(arr, n);

    int idx = smallest(arr, n);
    std::cout << "\n--- Result ---\n";
    std::cout << "Index of smallest: " << idx;
    if (idx >= 0) {
        std::cout << "  value = " << arr[idx]
                  << "  addr = " << static_cast<const void*>(&arr[idx]);
    }
    std::cout << '\n';

    double darr[] = {3.3, 1.1, 2.2};
    const int dn = 3;

    std::cout << "\n--- Array (double) ---\n";
    std::cout << "Input: ";
    for (int i = 0; i < dn; ++i) std::cout << darr[i] << (i + 1 < dn ? ", " : "\n");
    std::cout << "start = " << static_cast<const void*>(darr) << "  length = " << dn << '\n';
    std::cout << "Array (with addresses):\n";
    print_array_with_addresses(darr, dn);

    int didx = smallest(darr, dn);
    std::cout << "\n--- Result ---\n";
    std::cout << "Index of smallest: " << didx;
    if (didx >= 0) {
        std::cout << "  value = " << darr[didx]
                  << "  addr = " << static_cast<const void*>(&darr[didx]);
    }
    std::cout << '\n';

    std::string sarr[] = {"zz", "aa", "mm", "bb"};
    const int sn = 4;

    std::cout << "\n--- Array (std::string) ---\n";
    std::cout << "Input: ";
    for (int i = 0; i < sn; ++i) std::cout << '"' << sarr[i] << '"' << (i + 1 < sn ? ", " : "\n");
    std::cout << "start = " << static_cast<const void*>(sarr) << "  length = " << sn << '\n';
    std::cout << "Array (with addresses):\n";
    print_array_with_addresses(sarr, sn);

    int sidx = smallest(sarr, sn);
    std::cout << "\n--- Result ---\n";
    std::cout << "Index of smallest: " << sidx;
    if (sidx >= 0) {
        std::cout << "  value = \"" << sarr[sidx] << "\""
                  << "  addr = " << static_cast<const void*>(&sarr[sidx]);
    }
    std::cout << '\n';

    Point pts[] = {{30}, {10}, {20}, {5}, {40}};
    const int pn = 5;

    std::cout << "\n--- Array (Point custom struct) ---\n";
    std::cout << "Input: ";
    for (int i = 0; i < pn; ++i) std::cout << pts[i] << (i + 1 < pn ? ", " : "\n");
    std::cout << "start = " << static_cast<const void*>(pts) << "  length = " << pn << '\n';
    std::cout << "Array (with addresses):\n";
    print_array_with_addresses(pts, pn);

    int pidx = smallest(pts, pn);
    std::cout << "\n--- Result ---\n";
    std::cout << "Index of smallest: " << pidx;
    if (pidx >= 0) {
        std::cout << "  value = " << pts[pidx]
                  << "  addr = " << static_cast<const void*>(&pts[pidx]);
    }
    std::cout << '\n';

    return 0;
}
