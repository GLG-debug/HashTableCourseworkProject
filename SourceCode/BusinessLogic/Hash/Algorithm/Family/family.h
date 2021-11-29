#ifndef ALGHORITHM_FAMILY_H
#define ALGHORITHM_FAMILY_H

#include "../../Function/Family/family.h"
#include "../abstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(Family)

class Product : public Abstract::Product
{
public:
    using function_type = Function::Family::Product;

protected:
    const function_type *m_hashFunction;

protected:
    Product() : m_hashFunction(nullptr)
    {
    }

public:
    void setHashFunction(const function_type &hashFunction) {
        m_hashFunction = &hashFunction;
    }
};

class Creator : public Abstract::Creator
{
protected:
    Creator()
    {
    }
};

END_NAMESPACE // Family
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_FAMILY_H