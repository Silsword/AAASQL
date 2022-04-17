#pragma once

#include <iostream>
#include <variant>

using namespace std;

 //! \brief A class representing a cell of a database table

class cell {
public:
    bool empty = 1;///< The parameter shows whether the cell is full
    unsigned short num_type;///< The field in which the data type number of this cell is stored
    variant <string, long long, long double, bool> data;///< Container with cell information
    cell();///< Default Constructor
    cell(void* input, unsigned short num_type);///< Constructor that changes the values of class fields
    void* get_data();///< Method that returns the cell value
};

