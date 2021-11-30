#ifndef FUNCTION_FNV1a_H
#define FUNCTION_FNV1a_H

#include "family.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(FNV1a)

using Singleton = BusinessLogic::Pattern::Singleton<Product>;

class Product final : public Family::Product, public Singleton
{
private:
    const int32_t m_p;

private:
    friend const Product &Singleton::getInstance();
    Product() 
        : Family::Product(
            [this](size_t value, size_t i) -> size_t {
                size_t result = (0x811C9DC5 xor i) xor static_cast<int32_t>(value);
                return static_cast<int32_t>(result * m_p);
            }
          )
        , m_p(0x01000193)
    {
    }

public:
    using Singleton::getInstance;
};

END_NAMESPACE //  FNV1a
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !FUNCTION_FNV1a_H
