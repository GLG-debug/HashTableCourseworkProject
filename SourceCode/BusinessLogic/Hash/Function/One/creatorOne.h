#ifndef CREATOR_FUNCTION_ONE_H
#define CREATOR_FUNCTION_ONE_H

#include "../creatorAbstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(One)

class Creator : public Abstract::Creator
{
protected:
    Creator()
    {
    }

public:
    virtual const Product &create() const = 0;
};

END_NAMESPACE //  One
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !CREATOR_FUNCTION_ONE_H
