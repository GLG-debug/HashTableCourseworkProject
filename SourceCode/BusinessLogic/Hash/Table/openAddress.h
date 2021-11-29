#ifndef DIRECT_ADRESS_HASH_TABLE_H
#define DIRECT_ADRESS_HASH_TABLE_H

#include "../Factory/abstract.h"
#include "abstract.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Table)

class DirectAddress final : public Abstract
{
public: // Types
    using container_type = std::vector<value_type>;
    using factory_type   = Factory::Abstract;

private:
    using sample_type = BusinessLogic::Statistics::Dispersion::container_type;

private:
    friend factory_type::AAP_type;
    container_type m_container;
    std::vector<size_t> m_numberOfCollision;
    std::unique_ptr<Algorithm::Abstract::Product> m_algorithm;

public:
    DirectAddress(size_t size, const factory_type &factory, size_t alphabetPower = std::numeric_limits<char>::max())
        : Abstract(alphabetPower)
        , m_numberOfCollision(size, std::numeric_limits<size_t>::max())
        , m_algorithm(factory.getAlgorithm())
    {
        m_container.resize(size);
        m_algorithm->setTable(&m_container);
    }

private:
    sample_type sampleData(){
        sample_type result;
        result.reserve(m_numberOfBuckets);
        for(size_t i = 0; i < m_numberOfBuckets && m_numberOfCollision[i] != std::numeric_limits<size_t>::max(); ++i) {
            result.push_back( static_cast<double>( m_numberOfCollision[i] ) );
        }
        result.shrink_to_fit();
        return result;
    }

public:
    virtual bool isExist(const value_type &value) const override {
        size_t numberOfCollisions = 0;
        size_t index = (*m_algorithm).getIndex(value, numberOfCollisions, m_alphabetPower);
        return ( index != std::numeric_limits<size_t>::max() )
               || ( (m_container.begin() + index).operator*() == value );
    }
    virtual size_t size() const override {
        return m_container.size();
    }
    virtual bool insert(const value_type &value) override {
        using namespace BusinessLogic::Statistics;

        if ( m_numberOfBuckets == m_container.size() ) {
            sendUnseccessInsertion(value);
            return false;
        }

        size_t numberOfCollisions = 0;
        size_t index = (*m_algorithm).getIndex(value, numberOfCollisions, m_alphabetPower);
        if (index == std::numeric_limits<size_t>::max()
            || (m_container.begin() + index).operator*() == value
        ) {
            sendUnseccessInsertion(value);
            return false;
        }

        m_container[index] = value;
        m_numberOfCollision[m_numberOfBuckets] = numberOfCollisions;
        ++m_numberOfBuckets;

        Dispersion coefficient;
        m_simpleUniformHashingCoefficient = coefficient(sampleData());

        sendSuccessfulInsertion(value, std::make_pair(index, 0), numberOfCollisions, m_simpleUniformHashingCoefficient);
        return true;
    }
};

END_NAMESPACE // Table
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // DIRECT_ADRESS_HASH_TABLE_H
