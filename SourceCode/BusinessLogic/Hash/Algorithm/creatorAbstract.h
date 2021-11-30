#ifndef CREATOR_ALGHORITHM_ABSTRACT_H
#define CREATOR_ALGHORITHM_ABSTRACT_H

#include "../../../BusinessLogic/businessLogic.h"

#include <memory>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(Abstract)

class Creator
{
protected:
    Creator()
    {
    }

public:
    virtual std::unique_ptr<Product> create() const = 0;
};

END_NAMESPACE // Abstract
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !CREATOR_ALGHORITHM_ABSTRACT_H
