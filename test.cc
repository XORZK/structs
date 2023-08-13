#include "src/MACROS.hpp"
#include "src/map.hpp"

int main() {
    /*
    binary_tree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(0);
    tree.insert(3);
    tree.insert(2);

    std::cout << tree << "\n";*/

    rb_tree<int> t;

    t.insert(1);
    t.insert(1);
    t.insert(5);
    t.insert(2);
    t.insert(7);
    t.insert(6);
    t.insert(8);
    t.insert(8);

    std::cout << inorder_traversal(t) << '\n';
    std::cout << preorder_traversal(t) << '\n';
    std::cout << postorder_traversal(t) << '\n';
    std::cout << level_order_traversal(t) << '\n';
}
