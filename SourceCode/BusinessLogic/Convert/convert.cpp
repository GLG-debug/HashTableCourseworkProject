#include "convert.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Convert)

size_t toInteger(const std::array<char, 5> &value, size_t alphabetPower) {
    if (value.empty()) {
        throw std::invalid_argument("undefined key");
    }
    size_t result = value[0];
    for (auto current = value.begin() + 1, end = value.end(); current != end; ++current) {
        result = result * alphabetPower + (*current);
    }
    return result;
}

END_NAMESPACE // Convert
END_NAMESPACE // BusinessLogic
