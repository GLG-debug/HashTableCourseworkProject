#include "convert.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Convert)

size_t FromStdString::operator()(const std::array<char, 5> &value, size_t alphabetPower) const {
    if (value.empty()) {
        throw std::invalid_argument("undefined key");
    }

    size_t result = 0;
    size_t counter = 0;
    for (auto crbegin = value.crbegin(), crend = value.crend()
         ; crbegin != crend && *crbegin >= '!' && *crbegin <= '~'; ++crbegin, ++counter
    ) {
        result += (*crbegin) * std::pow(alphabetPower, counter);
    }
    return result;
}

END_NAMESPACE // Convert
END_NAMESPACE // BusinessLogic
