#include "error.h"

void error(unsigned short error_type) {
    switch (error_type) {
    case 1:
        cout << "{" << endl << "\"type\" : \"error\"," << "\"description\" : \"error type row\"," << endl << "}";
        break;

    case 2:
        cout << "{" << endl << "\"type\" : \"error\"," << "\"description\" : \"error type cell\"," << endl << "}";
        break;

    case 3:
        cout << "{" << endl << "\"type\" : \"error\"," << "\"description\" : \"table not found\"," << endl << "}";
        break;

    case 4:
        cout << "{" << endl << "\"type\" : \"error\"," << "\"description\" : \"file is not open\"," << endl << "}";
        break;

    case 5:
        cout << "{" << endl << "\"type\" : \"error\"," << "\"description\" : \"name column not found\"," << endl << "}";
        break;
    }
}
