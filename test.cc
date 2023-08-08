#include "src/MACROS.h"
#include "src/map.h"

int main() {
    /*
    binary_tree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(0);
    tree.insert(3);
    tree.insert(2);

    std::cout << tree << "\n";*/

    map<int, int> t;

    t.insert(1, 1);
    t.insert(1, 2);
    t.insert(5, 3);
    t.insert(2, 4);
    t.insert(7, 5);
    t.insert(6, 6);
    t.insert(8, 7);
    t.insert(8, 8);

    std::cout << t << '\n';
}
