
#include "set.hpp"

set::set(searchable_bag &bag) : b(bag) {}

set::set(const set &o) : b(o.b) {}

set &set::operator=(const set &o)
{
    (void)o;
    return *this;
}

set::~set() {}

void set::insert(int n)
{
    if (!b.has(n))
        b.insert(n);
}

void set::insert(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        insert(arr[i]);
}

bool set::has(int n) const
{
    return b.has(n);
}

void set::print() const
{
    b.print();
}

void set::clear()
{
    b.clear();
}

searchable_bag &set::get_bag()
{
    return b;
}

const searchable_bag &set::get_bag() const
{
    return b;
}
