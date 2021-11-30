#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H

/* Opening bracket */
#define OPEN {

/* Closing bracket */
#define CLOSE }

/* Begin of namespace */
#define BEGIN_NAMESPACE(name)   \
    namespace name OPEN

/* Begin of namespace */
#define END_NAMESPACE           \
    CLOSE

/* Declaring classes of factory method */
#define DFM_TYPES               \
    class Product;              \
    class Creator;

/* Factory method namespace declaration */
#define DFM_NAMESPACE(name)     \
    BEGIN_NAMESPACE(name)       \
    DFM_TYPES                   \
    END_NAMESPACE

/* Factory method base cod declaration */
#define DFM_BASE                \
    DFM_NAMESPACE(Abstract)     \
    DFM_NAMESPACE(One)          \
    DFM_NAMESPACE(Family)

namespace BusinessLogic
{
    namespace Hash
    {
        namespace Function
        {
            DFM_BASE
            DFM_NAMESPACE(FNV1a)
            DFM_NAMESPACE(Standart)
            DFM_NAMESPACE(Equivalent)

            namespace Pattern
            {
                DFM_NAMESPACE(FamilyToOne)
            }
        }

        namespace Algorithm
        {
            DFM_BASE
            DFM_NAMESPACE(LinearProbing)
            DFM_NAMESPACE(QuadraticProbing)
            DFM_NAMESPACE(PseudorandomProbing)
            DFM_NAMESPACE(DoubleHashing)
        }

        namespace Factory
        {
            class Abstract;
            class One;
            class Family;
        }

        namespace Table /* Only string data */
        {
            class Abstract;

            class OpenAddressing; // Direct address hash function

            class Chains;        // Hash function implemented by the chain method

            namespace Pattern
            {
                class InterfaceSubscriber;

                class Publisher;
            }
        }
    }

    namespace Pattern // Can be used for different classes
    {
        template<typename T>
        class Singleton;
    }

    namespace Convert
    {
        class FromStdString;
    }

    namespace Statistics
    {
        class Dispersion;
    }
}

#endif // BUSINESS_LOGIC_H
