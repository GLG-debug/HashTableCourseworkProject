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
    size_t m_convertValue;

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
    virtual size_t getFirstCoefficient() = 0;
    virtual size_t getSecondCoefficient(size_t counter) = 0;

public:
    void setTable(decltype(m_table) table) {
        m_table = table;
    }

    size_t getIndex(const value_type &value, size_t& numberOfCollisions, size_t alphabetPower) {
        if (not isValidInput()) {
            throw std::invalid_argument("the condition for using the algorithm is not met");
        }

        size_t size = m_table->size();
        m_convertValue = m_toInteger(value, alphabetPower);
        // It is necessary to use some coefficient

        numberOfCollisions = 0;
        decltype (m_table->cbegin()) currentIterator;

        constexpr std::array<char, 5> nullValue = {'\0', '\0', '\0', '\0', '\0'};
        while (numberOfCollisions <= size) {
            currentIterator = {
                m_table->cbegin()
                + ( getFirstCoefficient() + getSecondCoefficient(numberOfCollisions) ) % size
            };

            if ( *currentIterator == nullValue || *currentIterator == value ) { // Free cell or value match
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
