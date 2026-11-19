
#pragma once
#include "searchable_bag.hpp"

class set
{
    searchable_bag &b;

public:
    set(searchable_bag &bag);
    set(const set &o);
    set &operator=(const set &o);
    ~set();

    void insert(int n);
    void insert(int *arr, int size);
    bool has(int n) const;
    void print() const;
    void clear();

    searchable_bag &get_bag();
    const searchable_bag &get_bag() const;
};
