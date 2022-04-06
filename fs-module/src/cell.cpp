#include <cell.h>

cell::cell(void* input, unsigned short num_type) {
    this->num_type = num_type;
    empty = 0;

    switch (num_type) {
    case 1:
        data = *static_cast<long long*>(input);
        break;

    case 2:
        data = *static_cast<long double*>(input);
        break;

    case 3:
        data = *static_cast<bool*>(input);
        break;

    case 4:
        data = *static_cast<string*>(input);
        break;
    }
};
cell::cell() {}
void* cell::get_data() {
    return (&data);
};

