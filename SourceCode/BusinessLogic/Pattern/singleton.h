#ifndef SINGLETON_H
#define SINGLETON_H

#include "../businessLogic.h"

#include <memory>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Pattern)

template <typename T>
class Singleton {
private:
    static std::unique_ptr<T> m_singleton;

public:
    static const T &getInstance() {
        if (m_singleton == nullptr) {
            m_singleton = std::unique_ptr<T>(new T);
        }
        return m_singleton.operator*();
    }

    Singleton()                             = default;
    Singleton(const Singleton &)            = delete;
    Singleton(Singleton &&)                 = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&)      = delete;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::m_singleton = nullptr;

END_NAMESPACE // Pattern
END_NAMESPACE // BusinessLogic

#endif // SINGLETON_H
