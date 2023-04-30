//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_LEVEL_H
#define LD53_CLIENT_LEVEL_H

#include <cstdlib>
#include "grand.h"

enum FriendType {
    LADYBUG = 0,
    BEE = 1,
    MOUSE,
    FROG,
    FRIEND_TYPE_LENGTH
};

struct LevelFriend {
    FriendType type = LADYBUG;
    bool randomPosition = true;
    int hardcodedVertex = 0;
};

struct LevelPostOffice {
    bool randomPosition = true;
    int hardcodedVertex = 0;
};

struct LevelDelivery {
    int friendId = 0;
    bool hasTimeLimit = false;
    float timeLimit = 10.0f;
};

struct LevelDeliveryMission {
    float spawnDelay = 0.0f;
    int startPostOfficeId = 0;
    int snailId = 0;
    std::vector<LevelDelivery> deliveries;
};

struct Level {
    bool seeded = false;
    int seed = 0;
    int nodeCount = 10;
    std::vector<LevelFriend> friends = { { LADYBUG, true, 0 } };
    std::vector<LevelPostOffice> offices = { { true, 0 } };
    int snailCount = 1;

    std::vector<LevelDeliveryMission> missions = { { 0.0f, 0, 0, { { 0, true, 10.0f } } } };

    int deliveriesForBronze = 1;
    int deliveriesForSilver = 1;
    int deliveriesForGold = 1;
    float snail_speed = 2.f;
    static Level getLevel(int levelNumber);
    const static std::vector<Level> LEVELS;
};


#endif //LD53_CLIENT_LEVEL_H
