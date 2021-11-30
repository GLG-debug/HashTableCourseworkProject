#ifndef CHAINS_HASH_TABLE_H
#define CHAINS_HASH_TABLE_H

#include "abstract.h"
#include "../../Convert/convert.h"
#include "../Function/One/one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Table)

class Chains final : public Abstract
{
public: // Types
    using container_type = std::vector<std::list<value_type>>;
    using OFP_type       = Function::One::Product;
    using OFC_type       = Function::One::Creator;

private:
    BusinessLogic::Convert::FromStdString m_toInteger;

public:
    container_type m_container;
    const OFP_type &m_function;

    Chains(size_t size, const OFC_type &function, size_t alphabetPower = std::numeric_limits<char>::max())
        : Abstract(alphabetPower)
        , m_function(function.create())
    {
        if (size == 0) {
            size = 1;
        }
        /* The use of 'this' is mandatory */
        this->m_container.resize(size);
    }

private:
    bool isExist(const value_type &value, size_t index) const {
        const std::list<value_type> &currentList = m_container[index];
        return std::find(currentList.cbegin(), currentList.cend(), value) not_eq currentList.cend();
    }

public:
    virtual bool isExist(const value_type &value) const override {
        size_t size = this->size();
        size_t index = m_function.getHash(m_toInteger(value, m_alphabetPower)) % size;
        return isExist(value, index);
    }
    auto row(size_t index) const {
        return m_container[index];
    }
    virtual size_t size() const override {
        return m_container.size();
    }
    virtual bool insert(const value_type &value) override {
        using namespace BusinessLogic::Statistics;

        size_t index = m_function.getHash(m_toInteger(value, m_alphabetPower)) % this->size();
        if( isExist(value, index) ) {
            sendUnseccessInsertion(this, value);
            return false;
        }

        try {
            // List does not need a reserve
            m_container[index].push_back(value);
        }
        catch (const std::bad_alloc &) {
            sendUnseccessInsertion(this, value);
            return false;
        }
        ++m_numberOfBuckets;

        size_t listLength = m_container[index].size();
        sendSuccessfulInsertion(this, value, std::make_pair(index, listLength - 1), listLength - 1);

        return true;
    }
    virtual double simpleUniformHashingCoefficient() const override {
        size_t size = this->size();
        collision_container container(size);
        for(size_t i = 0; i < size; ++i) {
            container[i] = m_container[i].size();
        }
        return m_dispersion(container, size);
    }
};

END_NAMESPACE // Table
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // CHAINS_HASH_TABLE_H
