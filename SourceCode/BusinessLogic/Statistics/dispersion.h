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
    using value_type     = double;
    using container_type = std::vector<double>;

public:
    double operator()(const container_type &container) {
        double average = 0;
        double averageOfSquares = 0;
        size_t size = container.size();

        if( std::all_of(
                container.begin() + 1,
                container.end(),
                std::bind(std::equal_to<value_type>(), std::placeholders::_1, container.front())
            )
        ) {
            return 0;
        }

        for(const auto &value : container) {
            average          += value         / size;
            averageOfSquares += value * value / size;
        }
        return averageOfSquares - average * average;
    }
};

END_NAMESPACE // Statistics
END_NAMESPACE // BusinessLogic

#endif // DISPERSION_H
