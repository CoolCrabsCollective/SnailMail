//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/level/Delivery.h"
#include "world/level/Mission.h"

Delivery::Delivery(Mission& mission,
                   bool hasTimeLimit,
                   float timeLimit,
                   Friend* destination)
        : mission(mission),
          hasTimeLimit(hasTimeLimit),
          timeLimit(!hasTimeLimit ? INFINITY : timeLimit),
          timeLeft(!hasTimeLimit ? INFINITY : timeLimit),
          destination(destination),
          completed(false) {
    GRand r;

    sender = static_cast<FriendType>(r.i(FRIEND_TYPE_LENGTH));
    if (sender == destination->getFriendType()) {
        int senderNum = static_cast<int>(sender);
        senderNum++;
        if (senderNum == static_cast<int>(FRIEND_TYPE_LENGTH)) {
            senderNum = 0;
            sender = static_cast<FriendType>(senderNum);
        }
    }
}

void Delivery::tick(float delta) {
    if(completed || !mission.hasSpawnedSnail())
        return;

    if(isExpired())
        return;

    if(mission.getSnail()->getLocation() == destination->getLocation() && !mission.getSnail()->isMoving()) {
        destination->getChatBubble().popLetter(sender);
        completed = true;
        mission.getSnail()->deliverySound.play();
    } else {
        timeLeft -= delta;
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

float Delivery::getTimeLeft() const {
    return timeLeft;
}

FriendType Delivery::getSender() const {
    return sender;
}
