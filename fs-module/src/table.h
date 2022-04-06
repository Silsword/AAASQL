#ifndef TABLE_H
#define TABLE_H
#include "cell.h";
#include <vector>
#include<string>
#include"error.h"
using namespace std;

class table
{
public:
	string name_table;
	vector<unsigned short> num_type;
	vector <vector <cell>> rows;
	unsigned int index_max = 1;
	vector<string> tags;
	bool* prymary_key;
	table(string name_table, vector<string> rows_name, vector<unsigned short> rows_type, bool* rows_key, vector<string> tags);
	string get_name();
	unsigned short get_type(string name_column);
	string save();
	void insert(string name_collum, void* value);
	int found_index(string name_column);
	vector <int> select(string name_column, vector <long long> value);
	vector <int> select(string name_column, vector <long double> value);
	vector <int> select(string name_column, vector <string> value);
	vector <int> select(string name_column, vector <bool> value);
	void _return(string name_column, vector <int> num_rows);
};

#endif