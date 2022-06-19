#include "table.h"

table::table(string name_table, vector<string> rows_name, vector<unsigned short> rows_type, bool* rows_key, vector<string> tags) {
    rows.push_back(vector <cell>());
    rows.push_back(vector <cell>(rows_name.size()));
    prymary_key = rows_key;
    this->name_table = name_table;
    this->tags = tags;
    num_type = rows_type;

    for (int i = 0; i <  rows_name.size(); i++) {
        rows[0].push_back(cell(&rows_name[i], 4));
    }
}
string table::get_name() {
    return (name_table);
}
string table::save() {
    string a = "";
    a += "\n { \"type\" : \"create\", \"table\" : \"" + name_table + "\",\"rows\" : [";

    for (int i = 0; i < rows[0].size(); i++) {
        a += "{ \"name\" : \"";
        string gh = *static_cast<string*>(rows[0][i].get_data());
        a += gh + "\", \"type\" : \"";

        switch (num_type[i]) {
        case 1:
            a += "int";
            break;

        case 2:
            a += "double";
            break;

        case 3:
            a += "bool";
            break;

        case 4:
            a += "str";
            break;
        }

        a += "\", \"prymary key\" :";

        if (prymary_key[i])
            a += "true";
        else
            a += "false";

        a += " } ";

        if (i != rows[0].size() - 1)
            a += ",";
    }

    a += "],\"tags\" : [";

    for (int i = 0; i < tags.size(); i++) {
        a += "\"" + tags[i] + "\"";

        if (i != tags.size() - 1)
            a += ",";
    }

    a += "]}\n" + to_string(rows[0].size());

    if (rows.size() > 1) {
        for (int j = 1; j < rows.size() - 1; j++) {
            a +=  "\n{\"type\": \"insert\", \"table\" : \"" + name_table + "\", \"values\" : [";

            for (int i = 0; i < rows[j].size(); i++) {
                a += "{\"name\": \"" + *static_cast<string*>(rows[0][i].get_data());
                a += "\",\"value\": \"";

                switch (num_type[i]) {
                case 1:
                    a += to_string(*static_cast<long long*>(rows[j][i].get_data()));
                    break;

                case 2:
                    a += to_string(*static_cast<long double*>(rows[j][i].get_data()));
                    break;

                case 3:
                    a += to_string(*static_cast<bool*>(rows[j][i].get_data()));
                    break;

                case 4:
                    a += *static_cast<string*>(rows[j][i].get_data());
                    break;
                }

                a += "\"}";

                if (i != rows[j].size() - 1)
                    a += ",";
            }

            a += "]}";
        }
    }

    return (a);
}
void table::insert(string name_column, void* value) {
    int j = found_index(name_column);

    for (int i = 1;; i++) {
        if (rows[i][j].empty) {
            rows[i][j] = cell(value, num_type[j]);

            if (i == index_max) {
                index_max++;
                rows.push_back(vector <cell>(rows[0].size()));
            }

            break;
        }
    }
}
int table::found_index(string name_column) {
    int j = -1;

    for (int i = 0; i < rows[0].size(); i++) {
        if (*static_cast<string*>(rows[0][i].get_data()) == name_column) {
            j = i;
            break;
        }
    }

    if (j == -1)
        error(5);
    else
        return (j);
}
unsigned short table::get_type(string name_column) {
    return (num_type[found_index(name_column)]);
}
vector <int> table::select(string name_column, vector<long long> value) {
    int j = found_index(name_column);
    vector <int> ans;

    for (int i = 1; i < rows.size(); i++) {
        for (int k = 0; k < value.size(); k++) {
            if (*static_cast<long long*>(rows[i][j].get_data()) == value[k]) {
                ans.push_back(i);
                break;
            }
        }
    }

    return (ans);
}
vector <int> table::select(string name_column, vector <long double> value) {
    int j = found_index(name_column);
    vector <int> ans;

    for (int i = 1; i < rows.size(); i++) {
        for (int k = 0; k < value.size(); k++) {
            if (*static_cast<long double*>(rows[i][j].get_data()) == value[k]) {
                ans.push_back(i);
                break;
            }
        }
    }

    return (ans);
}
vector <int> table::select(string name_column, vector <string> value) {
    int j = found_index(name_column);
    vector <int> ans;

    for (int i = 1; i < rows.size(); i++) {
        for (int k = 0; k < value.size(); k++) {
            if (*static_cast<string*>(rows[i][j].get_data()) == value[k]) {
                ans.push_back(i);
                break;
            }
        }
    }

    return (ans);
}
vector <int> table::select(string name_column, vector <bool> value) {
    int j = found_index(name_column);
    vector <int> ans;

    for (int i = 1; i < rows.size(); i++) {
        for (int k = 0; k < value.size(); k++) {
            if (*static_cast<bool*>(rows[i][j].get_data()) == value[k]) {
                ans.push_back(i);
                break;
            }
        }
    }

    return (ans);
}
void table::_return(string name_column, vector <int> num_rows) {
    int j = found_index(name_column);

    for (int i = 1; i < num_rows.size(); i++) {
        switch (num_type[j]) {
        case 1:
            cout << *static_cast<long long*>(rows[i][j].get_data());
            break;

        case 2:
            cout << *static_cast<long double*>(rows[i][j].get_data());
            break;

        case 3:
            cout << *static_cast<bool*>(rows[i][j].get_data());
            break;

        case 4:
            cout << *static_cast<string*>(rows[i][j].get_data());
            break;
        }

        if (i + 1 != num_rows.size())
            cout << ",";
    }
}
