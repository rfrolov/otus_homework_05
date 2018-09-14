#include "../primitives/IPrimitive.h"
#include "utils.h"

std::ostream &operator<<(std::ostream &os, IPrimitive::serialised_t &v) {
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        os << *it;
        if (it + 1 != v.cend()) {
            os << " ";
        }
    }
    os << std::endl;
    return os;
}