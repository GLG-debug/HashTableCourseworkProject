#ifndef FUNCTION_FAMILY_H
#define FUNCTION_FAMILY_H

#include "../abstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Family)

using function_type = std::function<size_t(size_t, size_t)>;

class Product : public Abstract::Product
{
protected:
    const function_type m_function;

protected:
    Product(const function_type& function) : m_function(function)
    {
    }

public:
    const function_type &to_std() const {
        return m_function;
    }
    size_t getHash(size_t first, size_t second) const {
        // First - the value that is hashed
        // Second - coefficient
        return m_function(first, second);
    }
};

END_NAMESPACE //  Family
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // FUNCTION_FAMILY_H
