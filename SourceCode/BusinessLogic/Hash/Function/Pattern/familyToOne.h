#ifndef ADAPTER_FAMILY_TO_ONE_H
#define ADAPTER_FAMILY_TO_ONE_H

#include "../Family/family.h"
#include "../One/one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Pattern)
BEGIN_NAMESPACE(FamilyToOne)

class Product final : public One::Product
{
public:
    Product(const Family::Product &adaptee, size_t coefficient)
        : One::Product(
            std::bind(adaptee.to_std(), std::placeholders::_1, coefficient)
        )
    {
    }
};

class Creator final : public One::Creator
{
private:
    Product m_product; // To support the interface

public:
    Creator(std::shared_ptr<Family::Creator> adaptee, size_t coefficient)
        : m_product(adaptee->create(), coefficient)
    {
    }

public:
    virtual const Product &create() const override {
        return m_product;
    }
};

END_NAMESPACE //  FamilyToOne
END_NAMESPACE //  Pattern
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !ADAPTER_FAMILY_TO_ONE_H
