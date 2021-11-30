#ifndef CREATOR_ALGHORITHM_FAMILY_H
#define CREATOR_ALGHORITHM_FAMILY_H

#include "../creatorAbstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(Family)

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

#endif // !CREATOR_ALGHORITHM_FAMILY_H
