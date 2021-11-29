#ifndef ALGHORITHM_PSEUDORANDOM_PROBING_H
#define ALGHORITHM_PSEUDORANDOM_PROBING_H

#include "family.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(PseudorandomProbing)

class Product final : public Family::Product
{
private:
    size_t m_hashFunctionNumber;

private:
    friend Creator;
    Product(size_t number) : m_hashFunctionNumber(number)
    {
    }

protected:
//    virtual bool isValidInput() const override {
//        return isPrimeNumber(size());
//    }
    virtual size_t getFirstCoefficient(size_t convertValue) const override {
        return m_hashFunction->getHash(convertValue, m_hashFunctionNumber);
    }
    virtual size_t getMultiplier(size_t convertValue) const override {
        size_t firstCoefficient = getFirstCoefficient(convertValue);
        size_t size = this->size();
        size_t result;
        do { // Pseudo-random function
            result = m_hashFunction->getHash(convertValue, firstCoefficient++);
        } while (result % size == 0);
        return result;
    }
};

class Creator : public Family::Creator
{
private:
    size_t m_hashFunctionNumber;

public:
    Creator(size_t number) : m_hashFunctionNumber(number)
    {
    }

public:
    virtual std::unique_ptr<Abstract::Product> create() const override {
        return std::unique_ptr<Abstract::Product>(new Product(m_hashFunctionNumber));
    }

};

END_NAMESPACE // PseudorandomProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_PSEUDORANDOM_PROBING_H
