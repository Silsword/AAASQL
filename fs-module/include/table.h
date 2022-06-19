#pragma once

#include "cell.h"
#include <vector>
#include <string>
#include "error.h"
using std::vector;
using std::to_string;

//! \brief The class is a database table

class table {
public:
    string name_table;///<The field contains the name of the table
    vector<unsigned short> num_type;///<The field contains the data type of each column
    vector <vector <cell>> rows;///<The field contains rows of data cells
    unsigned int index_max = 1;///<The parameter indicates the index of the row whose cell was filled
    vector<string> tags;///<A field containing tags for a more convenient table search
    bool* prymary_key;///<A field containing parameters of uniqueness of values for each column
    table(string name_table, vector<string> rows_name, vector<unsigned short> rows_type, bool* rows_key, vector<string> tags);///<Constructor that changes the values of class fields
    string get_name();///<The method returns the name of the table
    unsigned short get_type(string name_column);///<The method returns the data type number of the column by its name
    string save();///<The method generates JSON to save the table
    void insert(string name_collum, void* value);///<The method fills a table cell
    int found_index(string name_column);///<The method returns the index of the column by its name
    vector <int> select(string name_column, vector <long long> value);///<The method returns a set of indexes of rows in which a value was found in the column
    vector <int> select(string name_column, vector <long double> value);///<The method returns a set of indexes of rows in which a value was found in the column
    vector <int> select(string name_column, vector <string> value);///<The method returns a set of indexes of rows in which a value was found in the column
    vector <int> select(string name_column, vector <bool> value);///<The method returns a set of indexes of rows in which a value was found in the column
    void _return(string name_column, vector <int> num_rows);///<The method outputs the values of the column cells by row indexes
};

