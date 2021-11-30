#ifndef FUNCTION_EQUIVALENT_H
#define FUNCTION_EQUIVALENT_H

#include "one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Equivalent)

using Singleton = BusinessLogic::Pattern::Singleton<Product>;

class Product final : public One::Product, public Singleton
{
private:
    friend const Product &Singleton::getInstance();
    Product() :
        One::Product(
            [](size_t value) -> size_t {
                return value;
            }
        )
    {
    }

public:
    using Singleton::getInstance;
};

END_NAMESPACE //  Equivalent
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !FUNCTION_EQUIVALENT_H
