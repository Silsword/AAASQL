#include <json/json.h>
#include <iostream>
#include <table.h>
#include <error.h>
#include <fstream>
#include <vector>

using namespace std;

vector<int> _and(vector <int> a1, vector<int> a2) {
    vector<int> ans;

    for (int i = 0; i < a1.size(); i++) {
        bool exist = 0;

        for (int j = 0; j < a2.size(); j++) {
            if (a1[i] == a2[j]) {
                exist = 1;
                break;
            }
        }

        if (exist) {
            ans.push_back(a1[i]);
        }
    }

    return (ans);
}

int main() {
    ofstream file;
    vector<table> t;
    Json::Reader r;
    Json::Value test;

    while (1) {
        string json_call;
        getline(cin, json_call);
        r.parse(json_call, test);

        if (test["type"].asString() == "create") {
            vector <string> rows_name;
            bool* rows_key = new bool[test["rows"].size()];
            vector<string> tags;

            for (int i = 0; i < test["tags"].size(); i++)
                tags.push_back(test["tags"][i].asString());

            vector<unsigned short> rows_type;

            for (int i = 0; i < test["rows"].size(); i++) {
                rows_name.push_back(test["rows"][i]["name"].asString());
                string te = test["rows"][i]["type"].asString();

                if ((te == "int") || (te == "long long"))
                    rows_type.push_back(1);
                else if ((te == "float") || (te == "long double") || (te == "double"))
                    rows_type.push_back(2);
                else if ((te == "bool") || (te == "boolean"))
                    rows_type.push_back(3);
                else if ((te == "str") || (te == "string") || (te == "text"))
                    rows_type.push_back(4);
                else {
                    error(2);
                    break;
                }

                if (("false" == test["rows"][i]["prymary key"].asString()) || ("0" == test["rows"][i]["prymary key"].asString()))
                    rows_key[i] = 0;
                else if (("true" == test["rows"][i]["prymary key"].asString()) || ("1" == test["rows"][i]["prymary key"].asString()))
                    rows_key[i] = 1;
            }

            t.push_back(table(test["table"].asString(), rows_name, rows_type, rows_key, tags));
        } else if (test["type"].asString() == "insert") {
            short j = -1;

            for (int i = 0; i < t.size(); i++)
                if (test["table"].asString() == t[i].get_name())
                    j = i;

            if (j == -1) {
                error(3);
                break;
            } else {
                for (int i = 0; i < test["values"].size(); i++) {
                    if (t[j].get_type(test["values"][i]["name"].asString()) == 1) {
                        long long ad = test["values"][i]["value"].asLargestInt();
                        t[j].insert(test["values"][i]["name"].asString(), &ad);
                    } else if (t[j].get_type(test["values"][i]["name"].asString()) == 2) {
                        long double ad = test["values"][i]["value"].asDouble();
                        t[j].insert(test["values"][i]["name"].asString(), &ad);
                    } else if (t[j].get_type(test["values"][i]["name"].asString()) == 3) {
                        bool ad = test["values"][i]["value"].asBool();
                        t[j].insert(test["values"][i]["name"].asString(), &ad);
                    } else if (t[j].get_type(test["values"][i]["name"].asString()) == 4) {
                        string ad = test["values"][i]["value"].asString();
                        t[j].insert(test["values"][i]["name"].asString(), &ad);
                    }
                }
            }
        } else if (test["type"].asString() == "new") {
            file.open(test["file"].asString() + ".aaasql");
        } else if (test["type"].asString() == "save") {
            if (file.is_open()) {
                file.write("", 0);
                file << t.size();

                for (int i = 0; i < t.size(); i++) {
                    file << t[i].save();
                }
            } else {
                error(4);
                break;
            }
        } else if (test["type"].asString() == "select") {
            short j = -1;

            for (int i = 0; i < t.size(); i++)
                if (test["table"].asString() == t[i].get_name())
                    j = i;

            if (j == -1) {
                error(3);
                break;
            } else {
                vector <int> ans;

                for (int i = 0; i < test["conditions"].size(); i++) {
                    if (t[j].get_type(test["conditions"][i]["name"].asString()) == 1) {
                        vector <long long> mas;

                        for (int k = 0; k < test["conditions"][i]["values"].size(); k++)
                            mas.push_back(test["conditions"][i]["values"][k].asLargestInt());

                        if (i == 0) {
                            ans = t[j].select(test["conditions"][i]["name"].asString(), mas);
                        } else
                            ans = _and(ans, t[j].select(test["conditions"][i]["name"].asString(), mas));
                    } else if (t[j].get_type(test["conditions"][i]["name"].asString()) == 2) {
                        vector <long double> mas;

                        for (int k = 0; k < test["conditions"][i]["values"].size(); k++)
                            mas.push_back(test["conditions"][i]["values"][k].asDouble());

                        if (i == 0) {
                            ans = t[j].select(test["conditions"][i]["name"].asString(), mas);
                        } else
                            ans = _and(ans, t[j].select(test["conditions"][i]["name"].asString(), mas));
                    } else if (t[j].get_type(test["conditions"][i]["name"].asString()) == 4) {
                        vector <string> mas;

                        for (int k = 0; k < test["conditions"][i]["values"].size(); k++)
                            mas.push_back(test["conditions"][i]["values"][k].asString());

                        if (i == 0) {
                            ans = t[j].select(test["conditions"][i]["name"].asString(), mas);
                        } else
                            ans = _and(ans, t[j].select(test["conditions"][i]["name"].asString(), mas));
                    } else if (t[j].get_type(test["conditions"][i]["name"].asString()) == 3) {
                        vector<bool> mas;

                        for (int k = 0; k < test["conditions"][i]["values"].size(); k++)
                            mas.push_back(test["conditions"][i]["values"][k].asBool());

                        if (i == 0) {
                            ans = t[j].select(test["conditions"][i]["name"].asString(), mas);
                        } else
                            ans = _and(ans, t[j].select(test["conditions"][i]["name"].asString(), mas));
                    }
                }

                cout << "{\n\"type\" : \"result\",\n";

                for (int i = 0; i < test["rows"].size(); i++) {
                    cout << "\"" << test["rows"][i].asString() << "\" : [";
                    t[j]._return(test["rows"][i].asString(), ans);
                    cout << "]";

                    if (i + 1 != test["rows"].size())
                        cout << ",";

                    cout << "\n";
                }

                cout << "}\n";
            }
        } else if (test["type"].asString() == "exit") {
            file.close();
            break;
        } else {
            error(1);
            break;
        }
    }
}

