#ifndef DISPERSION_H
#define DISPERSION_H

#include "../businessLogic.h"

#include <vector>
#include <algorithm>
#include <functional>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Statistics)

class Dispersion {
public: // Types
    using value_type     = size_t;
    using container_type = std::vector<value_type>;

public:
    long double operator()(const container_type &container, size_t size) const;
};

END_NAMESPACE // Statistics
END_NAMESPACE // BusinessLogic

#endif // DISPERSION_H
