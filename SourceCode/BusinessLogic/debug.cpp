#include "hashHeaderFiles.h"

#include <iostream>
#include <string>
#include <ctime>
#include <initializer_list>
#include <tuple>
#include <array>

#include "Convert/convert.h"

using namespace BusinessLogic::Hash;
using namespace Function::Pattern;
using namespace Table::Pattern;

using factory_ptr = std::shared_ptr<const Factory::Abstract>;

class Subscriber : public InterfaceSubscriber {
private:
    clock_t m_time;
    size_t  m_maxCollision;
    size_t  m_numberOfSuccesses;
    size_t  m_numberOfFailures;
    size_t  m_target;
    long double  m_lastCoefficients;

public:
    Subscriber(size_t target)
        : m_maxCollision(0)
        , m_numberOfSuccesses(0)
        , m_numberOfFailures(0)
        , m_target(target)
        , m_lastCoefficients(0)
    {
    }

    void startTime() {
        m_time = clock();
    }
    void endTime() {
        m_time = clock() - m_time;
    }
    double lastCoefficient() const {
        return m_lastCoefficients;
    }
    double workingTime() const {
        return m_time / static_cast<double>(CLOCKS_PER_SEC);
    }
    size_t maxCollision() const {
        return m_maxCollision;
    }
    auto numberOfSuccesses() const {
        return m_numberOfSuccesses;
    }
    auto numberOfFailures() const {
        return m_numberOfFailures;
    }

    virtual void successfulInsertion(const Table::Abstract *table, const std::array<char, 5> &, std::pair<size_t, size_t>, size_t numberOfCollisions) override {
        m_maxCollision = {
                numberOfCollisions > m_maxCollision
                ? numberOfCollisions
                : m_maxCollision
        };
        ++m_numberOfSuccesses;

        if(m_numberOfSuccesses + m_numberOfFailures >= m_target) {
            m_lastCoefficients = table->simpleUniformHashingCoefficient();
        }
    }
    virtual void unsuccessfulInsertion(const Table::Abstract *, const std::array<char, 5> &) override {
        ++m_numberOfFailures;
    }
    virtual void filledInPart(const Table::Abstract *) override {
        m_lastCoefficients = 0;
    }
};

void runTable(std::unique_ptr<Table::Abstract> table, size_t target) {
    /* 26 letters */
    constexpr char  firstChar = ' ';
    constexpr char  endChar = '~';
    size_t progress = 0;
    std::array<char, 5> currentString = { ' ', ' ', ' ', ' ', ' ' };

    bool continueFlag = true;
    while (continueFlag) {
	  if (++progress > target || not table->insert(currentString)) {
	    continueFlag = false;
	  }

         currentString[4] < endChar                                ? ++currentString[4]
      : (currentString[4] = firstChar, currentString[3] < endChar) ? ++currentString[3]
      : (currentString[3] = firstChar, currentString[2] < endChar) ? ++currentString[2]
      : (currentString[2] = firstChar, currentString[1] < endChar) ? ++currentString[1]
      : (currentString[1] = firstChar, currentString[0] < endChar) ? ++currentString[0]
      : (continueFlag = false);
    }
}

int main(int /*argc*/, char **/*argv*/)
{
    auto fnv1a       = std::make_shared<Function::FNV1a::Creator>();
    auto equivalent  = std::make_shared<Function::Equivalent::Creator>();
    auto standart    = std::make_shared<Function::Standart::Creator>();

    auto doubleHashing       = std::make_shared<Algorithm::DoubleHashing::Creator>(0, 1);
    auto pseudorandomProbing = std::make_shared<Algorithm::PseudorandomProbing::Creator>(0);
    auto linearProbing       = std::make_shared<Algorithm::LinearProbing::Creator>();
    auto quadraticProbing    = std::make_shared<Algorithm::QuadraticProbing::Creator>();

    /* First Hash Function has a number 0, second - 1 */
    const Factory::Abstract &fac1 { Factory::Family(fnv1a,   doubleHashing)       };
    const Factory::Abstract &fac2 { Factory::Family(fnv1a,   pseudorandomProbing) };
    const Factory::Abstract &fac3 { Factory::One(equivalent, linearProbing)       };
    const Factory::Abstract &fac4 { Factory::One(equivalent, quadraticProbing)    };
    const Factory::Abstract &fac5 { Factory::One(standart,   linearProbing)       };
    const Factory::Abstract &fac6 { Factory::One(standart,   quadraticProbing)    };

    auto simpleFNV1a = std::make_shared<FamilyToOne::Creator>(fnv1a, 0);
    const Factory::Abstract &fac7 { Factory::One(simpleFNV1a, linearProbing)    };
    const Factory::Abstract &fac8 { Factory::One(simpleFNV1a, quadraticProbing) };

    /* 0x5 == 0b0101 */
    auto complicatedFNV1a = std::make_shared<FamilyToOne::Creator>(fnv1a, 0x55555555);
    const Factory::Abstract &fac9  { Factory::One(complicatedFNV1a, linearProbing)    };
    const Factory::Abstract &fac10 { Factory::One(complicatedFNV1a, quadraticProbing) };

/*
 *  Constants
*/

    constexpr size_t numberOfInserts = (
            //11
            //101
            //5'003
            //50'021
            //230'003
            //456'959
            //1'000'003
            //5'000'011
            //10'000'019
            10'000'019
    ); // Must be simple - max is 10'371'957'246

    constexpr size_t quantityOfTables = 14;
    constexpr size_t numberOfBins = numberOfInserts / 10;
    constexpr size_t alphabetPower = '~' - ' ' + 1;
    constexpr double alpha = 0.9;

    std::array<std::shared_ptr<Subscriber>, quantityOfTables> results;
    for(std::shared_ptr<Subscriber> &current : results) {
        current = std::make_shared<Subscriber>(static_cast<size_t>(numberOfInserts * alpha));
    }

/*
 *  Constants
*/



    std::array<std::unique_ptr<Table::Abstract>, quantityOfTables> tables {
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac1,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac2,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac3,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac4,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac5,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac6,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac7,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac8,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac9,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::OpenAddressing(numberOfInserts, fac10,             alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains        (numberOfBins,    *equivalent,       alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains        (numberOfBins,    *standart,         alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains        (numberOfBins,    *simpleFNV1a,      alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains        (numberOfBins,    *complicatedFNV1a, alphabetPower) )
    };

    std::cout << std::fixed;
    std::cout.precision(10);
    std::cout << "START!" << std::endl;
    for(size_t i = 0; i < quantityOfTables; ++i) {
        tables[i]->signTheObject( &results[i].operator*() );
        results[i]->startTime();
        runTable(std::move(tables[i]), numberOfInserts * alpha);
        results[i]->endTime();

        std::cout
          << results[i]->maxCollision() << ' '
          << std::sqrt(results[i]->lastCoefficient()) << ' '
          << results[i]->numberOfSuccesses() << '/'
          << alpha << '/'
          << numberOfInserts << ' '
          << results[i]->workingTime() << std::endl;
    }
    std::cout << "END!" << std::endl;
}
