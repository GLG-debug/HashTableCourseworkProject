#ifndef FACTORY_FAMILY_H
#define FACTORY_FAMILY_H

#include "../Factory/abstract.h"

#include "../Function/Family/family.h"
#include "../Function/Family/creatorFamily.h"

#include "../Algorithm/Family/family.h"
#include "../Algorithm/Family/creatorFamily.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Factory)

class Family final : public Abstract
{
public:
    using FFC_type = std::shared_ptr<Function::Family::Creator>;
    using FAC_type = std::shared_ptr<Algorithm::Family::Creator>;

    using FFP_type = Function::Family::Product;
    using FAP_type = Algorithm::Family::Product;

public:
    Family(const FFC_type functionCreator, const FAC_type algorithmCreator)
        : Abstract(functionCreator, algorithmCreator)
    {
    }

public:
    virtual const FFP_type &getFunction() const override {
        return dynamic_cast<const FFP_type &>(m_functionCreator->create());
    }
    virtual std::unique_ptr<AAP_type> getAlgorithm() const override {
        std::unique_ptr<AAP_type> algorithm = m_algorithmCreator->create();
        dynamic_cast<FAP_type *>(algorithm.get())->setHashFunction(getFunction());
        return algorithm;
    }
};

END_NAMESPACE // Factory
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !FACTORY_FAMILY_H
