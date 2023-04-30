//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/level/Delivery.h"
#include "world/level/Mission.h"

Delivery::Delivery(Mission& mission,
                   float timeLimit,
                   Friend* destination)
        : mission(mission),
          timeLimit(timeLimit),
          timeLeft(timeLimit),
          destination(destination),
          completed(false) {}

void Delivery::tick(float delta) {
    if(completed || !mission.hasSpawnedSnail())
        return;

    if(isExpired())
        return;

    if(mission.getSnail()->getLocation() == destination->getLocation() && !mission.getSnail()->isMoving()) {
        completed = true;
    } else {
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
