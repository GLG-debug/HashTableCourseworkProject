#ifndef FUNCTION_STANDART_H
#define FUNCTION_STANDART_H

#include "one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Standart)

using Singleton = BusinessLogic::Pattern::Singleton<Product>;

class Product final : public One::Product, public Singleton
{
private:
    std::hash<size_t> m_standartHashFunction;

private:
    friend const Product &Singleton::getInstance();
    Product() 
        : One::Product(
            std::bind(&std::hash<size_t>::operator(), &m_standartHashFunction, std::placeholders::_1)
        )
        , m_standartHashFunction()
    {
    }

public:
    using Singleton::getInstance;
};

class Creator : public One::Creator
{
public:
    virtual const Product &create() const override {
        return Product::getInstance();
    }
};

END_NAMESPACE //  Standart
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !FUNCTION_FNV1a_H
