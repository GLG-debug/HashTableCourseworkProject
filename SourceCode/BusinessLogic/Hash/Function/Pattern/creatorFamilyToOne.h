#ifndef CREATOR_ADAPTER_FAMILY_TO_ONE_H
#define CREATOR_ADAPTER_FAMILY_TO_ONE_H

#include "familyToOne.h"
#include "../One/creatorOne.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Pattern)
BEGIN_NAMESPACE(FamilyToOne)

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

#endif // !CREATOR_ADAPTER_FAMILY_TO_ONE_H
