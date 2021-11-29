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
    size_t  m_maxCollision;
    clock_t m_time;
    size_t  m_numberOfSuccesses;
    size_t  m_numberOfFailures;
    double  m_lastCoefficients;
public:
    Subscriber()
        : m_maxCollision(0)
        , m_numberOfSuccesses(0)
        , m_numberOfFailures(0)
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

    virtual void successfulInsertion(const std::array<char, 5> &, std::pair<size_t, size_t>, size_t numberOfCollisions, double simpleUniformHashingCoefficients) override {
        m_maxCollision = {
                numberOfCollisions > m_maxCollision
                ? numberOfCollisions
                : m_maxCollision
        };
        ++m_numberOfSuccesses;
        m_lastCoefficients = simpleUniformHashingCoefficients;
    }
    virtual void unsuccessfulInsertion(const std::array<char, 5> &) override {
        ++m_numberOfFailures;
    }
};

void runTable(std::unique_ptr<Table::Abstract> table, size_t target) {
    /* 26 letters */
    constexpr char  firstChar = ' ';
    constexpr char  endChar = '~';
    size_t progress = 0;
    std::array<char, 5> currentString = { ' ' };

    bool continueFlag = true;
    while (continueFlag) {
	  if (++progress > target || not table->insert(currentString)) {
	    continueFlag = false;
	  }
//      if(table->simpleUniformHashingCoefficient() > 1) {
//        continueFlag = false;
//      }

         currentString[0] < endChar                                ? ++currentString[0]
      : (currentString[0] = firstChar, currentString[1] < endChar) ? ++currentString[1]
      : (currentString[1] = firstChar, currentString[2] < endChar) ? ++currentString[2]
      : (currentString[2] = firstChar, currentString[3] < endChar) ? ++currentString[3]
      : (currentString[3] = firstChar, currentString[4] < endChar) ? ++currentString[4]
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

    constexpr size_t quantityOfTables = 14;
    std::array<Subscriber, quantityOfTables>  results{ Subscriber() };

    constexpr size_t sizeOpen = /*11*//*101*/5'003/*50'021*//*230'003*//*456'959*/; // Must be simple
    constexpr size_t targetC = sizeOpen / 10;
    constexpr size_t alphabetPower = 26;
    std::array<std::unique_ptr<Table::Abstract>, quantityOfTables> tables {
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac1,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac2,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac3,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac4,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac5,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac6,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac7,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac8,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac9,              alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::DirectAddress(sizeOpen, fac10,             alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains       (targetC,  *equivalent,       alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains       (targetC,  *standart,         alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains       (targetC,  *simpleFNV1a,      alphabetPower) ),
        std::unique_ptr<Table::Abstract>( new Table::Chains       (targetC,  *complicatedFNV1a, alphabetPower) )
    };

    std::cout << "START!" << std::endl;

    double alpha = 0.8;
    for(size_t i = 0; i < quantityOfTables; ++i) {
        tables[i]->signTheObject(&results[i]);
        results[i].startTime();
        runTable(std::move(tables[i]), sizeOpen * alpha);
        results[i].endTime();

        std::cout
          << results[i].maxCollision() << '\t'
          << std::sqrt(results[i].lastCoefficient()) << '\t'
          << results[i].numberOfSuccesses() << '/'
          << alpha << '/'
          << sizeOpen << '\t'
          << results[i].workingTime() << std::endl;
    }

    std::cin.get();
    std::cin.get();
}
