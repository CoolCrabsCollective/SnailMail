//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_DELIVERY_H
#define LD53_CLIENT_DELIVERY_H


#include "world/friends/Friend.h"

class Delivery : public Tickable {
    float timeLimit;
    float timeLeft;

    Friend* destination;

    bool completed;
public:

    Delivery(float timeLimit, Friend *destination);

    void tick(float delta) override;

    bool isCompleted() const;

    bool isExpired() const;

    Friend *getDestination() const;
};


#endif //LD53_CLIENT_DELIVERY_H
