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
            .missions = { { 1.0f, 0, 0, { { 0, false, 10.0f }, }}},
            .deliveriesForBronze = 0,
            .deliveriesForSilver = 0,
            .deliveriesForGold = 1,
        },
        {
            .seeded = true,
            .seed = 0xbeefced,
            .nodeCount = 5,
            .friends = { { LADYBUG, false, 4 },
                         { FROG, false, 2 }},
            .offices = { { false, 0 }},
            .snailCount = 1,
            .missions = {{1.0f, 0, 0,
                          {{0, true, 35.0f},
                           {1, true, 50.0f},
                          },}
            },
            .deliveriesForBronze = 0,
            .deliveriesForSilver = 1,
            .deliveriesForGold = 2,
        },
        {
                .seeded = true,
                .seed = 0x71,
                .nodeCount = 6,
                .friends = { { LADYBUG, false, 2 },
                             { FROG, false, 3 },
                             { MOUSE, false, 4 } },
                .offices = { { false, 0 }},
                .snailCount = 2,
                .missions = { { 1.0f, 0, 0,
                                { { 0, true, 15.0f },
                                  { 1, true, 20.0f }} },
                              { 8.0f, 0, 1,
                                      {{ 1, true, 28.0f },
                                              { 2, true, 37.0f },} }},
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
        },
        {
                .seeded = true,
                .seed = 0xcedbeef,
                .nodeCount = 8,
                .friends = { { LADYBUG, false, 2 },
                             { FROG, false, 7 },
                             { MOUSE, false, 5 },
                             { BEE, false, 6 } },
                .offices = { { false, 0 }, { false, 4 }},
                .snailCount = 2,
                .missions = { { 1.0f, 0, 0,
                                { { 0, true, 10.0f },
                                  { 1, true, 20.0f },
                                  { 2, true, 30.0f },
                                  { 3, true, 50.0f }} },
                              { 7.0f, 1, 1,
                                { { 3, true, 23.0f },
                                  { 1, true, 30.0f },
                                  { 0, true, 43.0f },
                                  { 2, true, 60.0f }} } },
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
        }


};

Level Level::getLevel(int levelNumber) {
    if(levelNumber > 4)
        return Level();

    return LEVELS[levelNumber - 1];
}

