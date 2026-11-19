
#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int n) const
{
    node *cur = tree;

    while (cur && cur->value != n)
        cur = n < cur->value ? cur->l : cur->r;

    return cur != 0;
}
