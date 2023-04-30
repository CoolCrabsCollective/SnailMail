//
// Created by Alexander Winter on 2023-04-29.
//

#include <iostream>
#include "world/level/Mission.h"
#include "world/PostOffice.h"
#include "world/level/Delivery.h"

Mission::Mission(World& world, LevelDeliveryMission& levelMission)
    : world(world),
        spawnDelay(levelMission.spawnDelay),
        spawnProgress(-0.01f),
        snailId(levelMission.snailId),
        startPoint(world.getPostOffice(levelMission.startPostOfficeId)->getLocation()) {

    for(LevelDelivery& levelDelivery : levelMission.deliveries) {
        deliveries.push_back(new Delivery(*this,
                                          levelDelivery.hasTimeLimit,
                                          levelDelivery.timeLimit,
                                          world.getFriend(levelDelivery.friendId)));
    }
}

Mission::~Mission() {
    for(Delivery* delivery : deliveries)
        delete delivery;
    deliveries.clear();
}

void Mission::tick(float delta) {
    if(isCompleted())
        return;

    if(!spawned_snail) {
        spawnProgress += delta;

        bool snail_already_exists = false;
        bool snail_already_at_post_office = false;

        for(Snail* s : world.getSnails())
        {
            if(s->getSnailColor() == World::snail_colors[snailId])
            {
                snail_already_exists = true;
            }

            if(s->getLocation() == startPoint)
            {
                snail_already_at_post_office = true;
            }
        }


        if(spawnProgress >= spawnDelay && !snail_already_at_post_office && !snail_already_exists) {
            snail = world.spawnSnail(startPoint, snailId, world
            .getCurrentLevel().snail_speed);
            spawnProgress = spawnDelay;
            spawned_snail = true;

            for (Delivery* delivery : deliveries) {
                delivery->getDestination()->getChatBubble().addLetter(delivery->getSender());
            }
        }
    } else {
        bool allComplete = true;

        for(Delivery* delivery : deliveries) {
            delivery->tick(delta);

            if(!delivery->isCompleted() && !delivery->isExpired())
                allComplete = false;
        }

        if(allComplete && snail->getLocation() == startPoint) {
            // mission completed
            snail->deleteYourself();
            snail = nullptr;
            completed = true;
        }
    }
}

const std::vector<Delivery*>& Mission::getDeliveries() const {
    return deliveries;
}

bool Mission::hasSpawnedSnail() const {
    return snail != nullptr;
}

Snail *Mission::getSnail() {
    return snail;
}

bool Mission::isCompleted() const {
    return completed;
}

