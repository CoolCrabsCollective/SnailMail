//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/level/Delivery.h"

Delivery::Delivery(float timeLimit,
                   Friend* destination)
        : timeLimit(timeLimit),
          timeLeft(timeLimit),
          destination(destination) {}

void Delivery::tick(float delta) {
    if(completed)
        return;

    if(timeLeft > 0.0f) {
        timeLeft -= 0.0f;
        if(timeLeft < 0.0f)
            timeLeft = 0.0f;
    }
}

bool Delivery::isCompleted() const {
    return completed;
}

bool Delivery::isExpired() const {
    return !completed && timeLeft == 0.0f;
}

Friend *Delivery::getDestination() const {
    return destination;
}
