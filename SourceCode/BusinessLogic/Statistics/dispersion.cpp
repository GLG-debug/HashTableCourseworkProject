#include "dispersion.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Statistics)

long double Dispersion::operator()(const container_type &container, size_t size) const {
    long double average = 0;
    long double averageOfSquares = 0;

    for(size_t i = 0; i < size; ++i) {
        average          += ( container[i] )                    / static_cast<long double>(size);
        averageOfSquares += ( container[i] ) * ( container[i] ) / static_cast<long double>(size);
    }
    return averageOfSquares - average * average;
}

END_NAMESPACE // Statistics
END_NAMESPACE // BusinessLogic
