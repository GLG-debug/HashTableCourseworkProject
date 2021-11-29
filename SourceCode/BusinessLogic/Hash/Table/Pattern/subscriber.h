#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "../../../businessLogic.h"

#include <vector>
#include <string>
#include <algorithm>
#include <array>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Table)
BEGIN_NAMESPACE(Pattern)

class InterfaceSubscriber
{
public:
    virtual void successfulInsertion(const std::array<char, 5> &, std::pair<size_t, size_t>, size_t, double) = 0;
    virtual void unsuccessfulInsertion(const std::array<char, 5> &) = 0;
};

class Publisher
{
private:
    std::vector<InterfaceSubscriber *> m_subscribers;

public:
    virtual void signTheObject(InterfaceSubscriber *subscriber) {
        if (subscriber not_eq nullptr) {
            m_subscribers.push_back(subscriber);
        }
    }
    virtual void unsubscribe(InterfaceSubscriber *subscriber) {
        if (subscriber not_eq nullptr) {
            m_subscribers.erase(std::find(m_subscribers.begin(), m_subscribers.end(), subscriber));
        }
    }

protected:
    virtual void sendSuccessfulInsertion(const std::array<char, 5> &value, std::pair<size_t, size_t> index, size_t numberOfCollisions, double simpleUniformHashingCoefficient) const {
        for (decltype(auto) currentSubscriber : m_subscribers) {
            currentSubscriber->successfulInsertion(value, index, numberOfCollisions, simpleUniformHashingCoefficient);
        }
    }
    virtual void sendUnseccessInsertion(const std::array<char, 5> &value) const {
        for (decltype(auto) currentSubscriber : m_subscribers) {
            currentSubscriber->unsuccessfulInsertion(value);
        }
    }
};

END_NAMESPACE // Pattern
END_NAMESPACE // Table
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // SUBSCRIBER_H
