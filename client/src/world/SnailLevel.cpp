//
// Created by Alexander Winter on 2023-04-29.
//
#include "world/SnailLevel.h"

const SnailLevel SnailLevel::LEVELS[] = {
        {
            .seeded = true,
            .seed = 777,
            .nodeCount = 6,
            .friends = { { LADYBUG, false, 2 } },
            .offices = { { false, 0 }},
            .snailCount = 1,
            .missions = { { 0.0f, 0, 0, { { 0, 10.0f } } } }
        },

};

SnailLevel SnailLevel::getLevel(int levelNumber) {
    return LEVELS[levelNumber - 1];
}

