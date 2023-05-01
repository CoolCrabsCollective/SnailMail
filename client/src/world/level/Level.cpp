//
// Created by Alexander Winter on 2023-04-29.
//
#include "world/level/Level.h"

const std::vector<Level> Level::LEVELS = {
        {
                .seeded = true,
                .seed = 123,
                .nodeCount = 3,
                .friends = { { LADYBUG, false, 2 }},
                .offices = { { false, 0 }},
                .snailCount = 1,
                .missions = {
                        { 1.0f, 0, 0, { { 0, false, 10.0f }, }}

                },
                .deliveriesForBronze = 0,
                .deliveriesForSilver = 0,
                .deliveriesForGold = 1,
                .snail_speed = 5.f,
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
                              {{0, true, 25.0f},
                               {1, true, 40.0f},
                              },}
                },
                .deliveriesForBronze = 0,
                .deliveriesForSilver = 1,
                .deliveriesForGold = 2,
                .snail_speed = 5.f,
        },
        {
            .friends = {{ MOUSE, false, 7 } },
            .offices = { { false, 0 }},
            .snailCount = 2,
            .missions = { { 1.0f, 0, 0,
                                  { { 0, true, 20.0f }, },},
                          { 7.0f, 0, 1,
                                  { { 0, true, 20.0f }, },},},
            .deliveriesForBronze = 0,
            .deliveriesForSilver = 1,
            .deliveriesForGold = 2,
            .snail_speed = 4.f,
            .custom = true,
            .nodes = {{3.f, 10.f}, {6.f, 13.f}, {6.f, 6.f}, {9.f, 9.f}, {14.f, 9.f}, {17.f, 13.f}, {17.f, 6.f}, {20.f, 9.f},},
            .adjacency_list = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {6, 7},{5, 7}},
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
                              { 5.0f, 0, 1,
                                      {{ 1, true, 28.0f },
                                              { 2, true, 37.0f },} }},
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
                .snail_speed = 3.f,
        },
        {
                .seeded = true,
                .seed = 0xdef9,
                .nodeCount = 4,
                .friends = {
                        { BEE, false, 0 } },
                .offices = { { false, 1 }},
                .snailCount = 3,
                .missions = {
                        { 1.0f, 0, 0, {{ 0, true, 15.f}}},
                        { 5.0f, 0, 1, {{ 0, true, 15.f}}},
                        { 10.0f, 0, 2, {{ 0, true, 15.f}}},
                        { 15.0f, 0, 0, {{ 0, true, 15.f}}},
                },
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
                .snail_speed = 2.f,
        },
        {
                .seeded = true,
                .seed = 0xceedbef,
                .nodeCount = 8,
                .friends = { { LADYBUG, false, 5 },
                             { FROG, false, 7 },
                             { MOUSE, false, 2 },
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
                                              { 1, true, 36.0f },
                                              { 0, true, 49.0f },
                                              { 2, true, 69.0f }} }},
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
                .snail_speed = 2.f,
        }


};

Level Level::getLevel(int levelNumber) {
    if(levelNumber > LEVELS.size())
        return {};

    return LEVELS[levelNumber - 1];
}

