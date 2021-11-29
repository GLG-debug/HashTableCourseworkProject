#ifndef CONVERT_H
#define CONVERT_H

#include "../businessLogic.h"

#include <string>
#include <stdexcept>
#include <limits>
#include <array>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Convert)

size_t toInteger(const std::array<char, 5> &, size_t);

END_NAMESPACE // Convert
END_NAMESPACE // BusinessLogic

#endif // CONVERT_H
