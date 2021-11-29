#ifndef FACTORY_ABSTRACT_H
#define FACTORY_ABSTRACT_H

#include "../Function/abstract.h"
#include "../Algorithm/abstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Factory)

class Abstract
{
public:
    /* 
    *  I used to use a constant link. This led to UB.
    * 
    *  https://eel.is/c++draft/class.temporary#6 (27.10.2021)
    * 
    *  The exceptions to this lifetime rule are:
    *  (6.9) A temporary object bound to a reference parameter in a function call ([expr.call]) persists until the completion of the full-expression containing the call.
    */
    using AFC_type = std::shared_ptr<Function::Abstract::Creator>;
    using AAC_type = std::shared_ptr<Algorithm::Abstract::Creator>;

protected:
    AFC_type m_functionCreator;
    AAC_type m_algorithmCreator;

protected:
    Abstract(AFC_type functionCreator, AAC_type algorithmCreator)
        : m_functionCreator(functionCreator), m_algorithmCreator(algorithmCreator)
    {
    }

public:
    using AFP_type = Function::Abstract::Product;
    using AAP_type = Algorithm::Abstract::Product;

public:
    virtual const AFP_type            &getFunction()  const = 0;
    virtual std::unique_ptr<AAP_type>  getAlgorithm() const = 0;
};

END_NAMESPACE // Factory
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !FACTORY_ABSTRACT_H