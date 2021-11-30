#ifndef FUNCTION_ONE_H
#define FUNCTION_ONE_H

#include "../abstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(One)

using function_type = std::function<size_t(size_t)>;

class Product : public Abstract::Product
{
protected:
    const function_type m_function;

protected:
    Product(const function_type& function) : m_function(function)
    {
    }

public:
    const function_type& to_std() const {
        return m_function;
    }
    size_t getHash(size_t value) const {
        return m_function(value);
    }
};

END_NAMESPACE //  One
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !FUNCTION_ONE_H
