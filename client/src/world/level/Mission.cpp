//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/level/Mission.h"
#include "world/PostOffice.h"
#include "world/level/Delivery.h"

Mission::Mission(World& world, LevelDeliveryMission& levelMission)
    : world(world),
        spawnDelay(levelMission.spawnDelay),
        spawnProgress(-0.01f),
        snailId(levelMission.snailId),
        startPoint(world.getPostOffice(levelMission.startPostOfficeId)->getStartNode()) {}

Mission::~Mission() {
    for(Delivery* delivery : deliveries)
        delete delivery;
    deliveries.clear();
}

void Mission::tick(float delta) {
    if(spawnProgress < spawnDelay) {
        spawnProgress += delta;

        if(spawnProgress >= spawnDelay) {
            snail = world.spawnSnail(startPoint, snailId);
            spawnProgress = spawnDelay;
        }
    } else {
        for(Delivery* delivery : deliveries) {
            delivery->tick(delta);
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

