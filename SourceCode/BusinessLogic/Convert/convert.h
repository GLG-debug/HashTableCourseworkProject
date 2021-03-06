#ifndef CONVERT_H
#define CONVERT_H

#include "../businessLogic.h"

#include <string>
#include <stdexcept>
#include <limits>
#include <array>
#include <cmath>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Convert)

class FromStdString
{
public:
    size_t operator()(const std::array<char, 5> &, size_t) const;
};

END_NAMESPACE // Convert
END_NAMESPACE // BusinessLogic

#endif // CONVERT_H
