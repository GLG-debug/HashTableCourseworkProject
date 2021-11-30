#ifndef ALGHORITHM_ABSTRACT_H
#define ALGHORITHM_ABSTRACT_H

#include "../../Convert/convert.h"

#include <vector>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <array>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(Abstract)

class Product
{
public:
    using value_type = std::array<char, 5>;

private:
    const std::vector<value_type> *m_table;
    BusinessLogic::Convert::FromStdString m_toInteger;

protected:
    Product() : m_table(nullptr)
    {
    }

protected:
    size_t  gcd(size_t first, size_t second) const {
        while (first > 0 && second > 0) {
            first > second
                ? first %= second
                : second %= first;
        }
        return first + second;
    }
    bool    isPrimeNumber(size_t value) const {
        size_t size = static_cast<size_t>(sqrt(value));
        for (size_t i = 2; i <= size; i++) {
            if (value % i == 0) {
                return false;
            }
        }
        return true;
    }
    size_t size() const {
        return m_table->size();
    }

protected:
    virtual bool isValidInput() const {
        return true;
    }
    virtual size_t  getFirstCoefficient(size_t)  const = 0;
    virtual size_t  getMultiplier(size_t)        const = 0;

public:
    void setTable(decltype(m_table) table) {
        m_table = table;
    }

    size_t getIndex(const value_type &value, size_t& numberOfCollisions, size_t alphabetPower) const {
        if (not isValidInput()) {
            throw std::invalid_argument("the condition for using the algorithm is not met");
        }

        size_t size = m_table->size();
        size_t convertValue     = m_toInteger(value, alphabetPower);
        // It is necessary to use some coefficient
        size_t beginIndex       = getFirstCoefficient(convertValue) % size;
        size_t multiplier       = getMultiplier(convertValue);
        if (multiplier % size == 0) {
            ++multiplier;
        }

        numberOfCollisions = 0;
        decltype (m_table->cbegin()) currentIterator;
        while (numberOfCollisions <= size) {
            currentIterator = {
                m_table->cbegin()
                + ( beginIndex + (numberOfCollisions % size) * (multiplier % size) ) % size
            };

            if ( currentIterator->front() == 0x0000 || *currentIterator == value ) { // Free cell or value match
                return ( currentIterator - m_table->cbegin() );
            }
            ++numberOfCollisions;
        }
        return std::numeric_limits<size_t>::max();
    }
};

END_NAMESPACE // Abstract
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_ABSTRACT_H
