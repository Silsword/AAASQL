#pragma once

#include <iostream>
#include <variant>

using namespace std;

class cell {
public:
    bool empty = 1;
    unsigned short num_type;
    variant <string, long long, long double, bool> data;
    cell();
    cell(void* input, unsigned short num_type);
    void* get_data();
};

