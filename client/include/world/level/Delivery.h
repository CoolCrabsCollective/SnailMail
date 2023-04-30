//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_DELIVERY_H
#define LD53_CLIENT_DELIVERY_H


#include "world/friends/Friend.h"

class Delivery : public Tickable {

    Mission& mission;
    bool hasTimeLimit;
    float timeLimit;
    float timeLeft;

    Friend* destination;
    FriendType sender;

    bool completed;
public:

    Delivery(Mission& mission, bool hasTimeLimit, float timeLimit, Friend *destination);

    void tick(float delta) override;

    bool isCompleted() const;

    bool isExpired() const;

    float getTimeLeft() const;

    Friend *getDestination() const;

    FriendType getSender() const;
};


#endif //LD53_CLIENT_DELIVERY_H
