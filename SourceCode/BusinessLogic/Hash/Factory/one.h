#ifndef FACTORY_ONE_H
#define FACTORY_ONE_H

#include "../Factory/abstract.h"
#include "../Function/One/one.h"
#include "../Algorithm/One/one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Factory)

class One final : public Abstract
{
public:
    using OFC_type = std::shared_ptr<Function::One::Creator>;
    using OAC_type = std::shared_ptr<Algorithm::One::Creator>;

    using OFP_type = Function::One::Product;
    using OAP_type = Algorithm::One::Product;

public:
    One(OFC_type functionCreator, OAC_type algorithmCreator)
        : Abstract(functionCreator, algorithmCreator)
    {
    }

public:
    virtual const OFP_type &getFunction() const override {
        return dynamic_cast<const OFP_type &>(m_functionCreator->create());
    }
    virtual std::unique_ptr<AAP_type> getAlgorithm() const override {
        std::unique_ptr<AAP_type> algorithm = m_algorithmCreator->create();
        dynamic_cast<OAP_type *>(algorithm.get())->setHashFunction(getFunction());
        return algorithm;
    }
};

END_NAMESPACE // Factory
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !FACTORY_ONE_H