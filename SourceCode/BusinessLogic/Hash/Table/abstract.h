#ifndef ABSTRACT_HASH_TABLE_H
#define ABSTRACT_HASH_TABLE_H

#include "../../businessLogic.h"
#include "Pattern/subscriber.h"
#include "../../Statistics/dispersion.h"

#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <string>
#include <stdexcept>
#include <typeinfo>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Table)

class Abstract : public Pattern::Publisher
{
public:
    using value_type = std::array<char, 5>;

protected:  // Members
    size_t      m_numberOfBuckets;
    long double m_simpleUniformHashingCoefficient;
    size_t      m_alphabetPower;

protected:
    Abstract(size_t alphabetPower)
        : m_numberOfBuckets(0)
        , m_alphabetPower(alphabetPower)
    {
    }

    Abstract(Abstract &&)                 = default;
    Abstract &operator=(Abstract &&)      = default;
    Abstract(const Abstract &)            = delete;
    Abstract &operator=(const Abstract &) = delete;

public:
    virtual bool isExist(const value_type &) const = 0;
    virtual size_t size() const = 0;
    virtual bool insert(const value_type &value) = 0;
    size_t alphabetPower() const {
        return m_alphabetPower;
    }
    size_t numberOfBuckets() const {
        return m_numberOfBuckets;
    }
    long double simpleUniformHashingCoefficient() const {
        return m_simpleUniformHashingCoefficient;
    }
};

END_NAMESPACE // Table
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // ABSTRACT_HASH_TABLE_H
