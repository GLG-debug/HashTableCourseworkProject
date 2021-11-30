#ifndef CREATOR_FUNCTION_FAMILY_H
#define CREATOR_FUNCTION_FAMILY_H

#include "../creatorAbstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Family)

class Creator : public Abstract::Creator
{
protected:
    Creator()
    {
    }

public:
    virtual const Product &create() const = 0;
};

END_NAMESPACE //  Family
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // CREATOR_FUNCTION_FAMILY_H
