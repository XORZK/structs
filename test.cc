#include "src/MACROS.hpp"
#include "src/set.hpp"

int main() {
    set<int> t;

    t.insert(1);
    t.insert(2);
    t.insert(3);

    set<int> u = t;
    u.remove(3);

    std::cout << t << "\n";
    std::cout << u << "\n";
    std::cout << u * t << "\n";
}
