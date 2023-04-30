//
// Created by Alexander Winter on 2023-04-29.
//
#include "world/level/Level.h"

const Level Level::LEVELS[] = {
        {
            .seeded = true,
            .seed = 777,
            .nodeCount = 6,
            .friends = { { LADYBUG, false, 2 },
                         { FROG, false, 3 }},
            .offices = { { false, 0 }},
            .snailCount = 1,
            .missions = { { 1.0f, 0, 0, { { 0, 10.0f }, { 1, 15.0f } } } }
        },
        {
            .seeded = true,
            .seed = 666,
            .nodeCount = 10,
            .friends = { { LADYBUG, false, 2 },
                         { FROG, false, 3 },
                         { MOUSE, false, 5 },
                         { BEE, false, 9 } },
            .offices = { { false, 0 }},
            .snailCount = 1,
            .missions = { { 1.0f, 0, 0,
                            { { 0, 10.0f },
                              { 1, 20.0f },
                              { 2, 30.0f },
                              { 3, 50.0f }} } }
        },
        {
                .seeded = true,
                .seed = 666,
                .nodeCount = 25,
                .friends = { { LADYBUG, false, 2 },
                             { FROG, false, 3 },
                             { MOUSE, false, 5 },
                             { BEE, false, 9 } },
                .offices = { { false, 0 }},
                .snailCount = 1,
                .missions = { { 1.0f, 0, 0,
                                { { 0, 10.0f },
                                  { 1, 20.0f },
                                  { 2, 30.0f },
                                  { 3, 50.0f }} } }
        }

};

Level Level::getLevel(int levelNumber) {
    if(levelNumber > 2)
        return Level();

    return LEVELS[levelNumber - 1];
}

