//
// Created by Alexander Winter on 2023-04-29.
//
#include "world/level/Level.h"

const Level Level::LEVELS[] = {
        {
            .seeded = true,
            .seed = 123,
            .nodeCount = 3,
            .friends = { { LADYBUG, false, 2 }},
            .offices = { { false, 0 }},
            .snailCount = 1,
            .missions = { { 1.0f, 0, 0, { { 0, false, 10.0f }, }}}
        },
        {
            .seeded = true,
            .seed = 2,
            .nodeCount = 5,
            .friends = { { LADYBUG, false, 2 },
                         { FROG, false, 3 }},
            .offices = { { false, 0 }},
            .snailCount = 1,
            .missions = {{1.0f, 0, 0,
                          {{0, true, 15.0f},
                           {1, true, 20.0f},
                          },}
            }
        },
        {
                .seeded = true,
                .seed = 666,
                .nodeCount = 15,
                .friends = { { LADYBUG, false, 2 },
                             { FROG, false, 3 },
                             { MOUSE, false, 5 },
                             { BEE, false, 9 } },
                .offices = { { false, 0 }},
                .snailCount = 1,
                .missions = { { 1.0f, 0, 0,
                                { { 0, true, 10.0f },
                                  { 1, true, 20.0f },
                                  { 2, true, 30.0f },
                                  { 3, true, 50.0f }} } }
        },
        {
                .seeded = true,
                .seed = 0xcedbeef,
                .nodeCount = 16,
                .friends = { { LADYBUG, false, 2 },
                             { FROG, false, 3 },
                             { MOUSE, false, 5 },
                             { BEE, false, 9 } },
                .offices = { { false, 0 }, { false, 4 }},
                .snailCount = 2,
                .missions = { { 1.0f, 0, 0,
                                { { 0, true, 10.0f },
                                  { 1, true, 20.0f },
                                  { 2, true, 30.0f },
                                  { 3, true, 50.0f }} },
                              { 7.0f, 1, 1,
                                { { 3, true, 16.0f },
                                  { 1, true, 27.0f },
                                  { 0, true, 38.0f },
                                  { 2, true, 60.0f }} } }
        }


};

Level Level::getLevel(int levelNumber) {
    if(levelNumber > 4)
        return Level();

    return LEVELS[levelNumber - 1];
}

