//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_MISSION_H
#define LD53_CLIENT_MISSION_H


#include "world/Tickable.h"
#include "world/World.h"

class Delivery;

class Mission : public Tickable {
    float spawnDelay;
    float spawnProgress;

    GraphNode* startPoint;
    int snailId;

    World& world;

    std::vector<Delivery*> deliveries;

    Snail* snail = nullptr;
public:
    Mission(World& world, LevelDeliveryMission& levelMission);

    ~Mission() override;

    void tick(float delta) override;

    [[nodiscard]]
    const std::vector<Delivery*>& getDeliveries() const;

    /**
     * @return True if the snail for this mission spawned (has been started)
     */
    [[nodiscard]]
    bool hasSpawnedSnail() const;

    /**
     * @return null if not spawned
     */
    [[nodiscard]]
    Snail* getSnail();
};


#endif //LD53_CLIENT_MISSION_H
