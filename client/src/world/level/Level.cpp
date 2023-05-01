//
// Created by Alexander Winter on 2023-04-29.
//
#include "world/level/Level.h"

const std::vector<Level> Level::LEVELS = {
        // LEVEL 1
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
        },
        // LEVEL 2
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
        },
        // LEVEL 3
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
            .custom = true,
            .nodes = {{3.f, 10.f}, {6.f, 13.f}, {6.f, 6.f}, {9.f, 9.f}, {14.f, 9.f}, {17.f, 13.f}, {17.f, 6.f}, {20.f, 9.f},},
            .adjacency_list = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {6, 7},{5, 7}},
        },
        // LEVEL 4
        {
                .friends = {{ FROG, false, 6 },
                            { BEE, false, 4 }},
                .offices = { { false, 5 }, { false, 2 }},
                .snailCount = 2,
                .missions = { { 1.0f, 0, 0,
                                      { { 0, true, 9.0f },
                                              { 1, true, 14.0f },},},
                              { 1.0f, 1, 1,
                                      { { 0, true, 9.0f },
                                              { 1, true, 14.0f },},},},
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
                .custom = true,
                .nodes = {{6.f, 4.f}, {18.f, 4.f}, {21.f, 9.f}, {18.f, 14.f}, {6.f, 14.f}, {3.f, 9.f}, {12.f, 9.f}},
                .adjacency_list = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}, {0, 6}, {6, 3},{5, 6}, {6, 2}},
        },
        // LEVEL 5
        {
                .friends = {{ LADYBUG, false, 3 }, { BEE, false, 4 } },
                .offices = { { false, 0 }},
                .snailCount = 2,
                .missions = { { 1.0f, 0, 0,
                                      { { 0, true, 6.0f }, },},
                              { 1.0f, 0, 1,
                                      { { 0, true, 6.0f },
                                              { 1, true, 8.0f }, },},},
                .deliveriesForBronze = 0,
                .deliveriesForSilver = 1,
                .deliveriesForGold = 2,
                .custom = true,
                .nodes = { {5.f, 9.f}, {11.f, 9.f}, {15.f, 13.f}, {15.f, 6.f}, {18.f, 9.f},},
                .adjacency_list = { {0, 1}, {1, 2}, {1, 3}, {3, 4},{2, 4}},
        },
        // LEVEL 6
        {
                .name = "The Great Double Cock Block",
                .friends = {{ FROG, false, 1 },
                            { LADYBUG, false, 10 }},
                .offices = { { false, 0 }, {false, 3}, {false, 6}},
                .snailCount = 2,
                .missions = { { 1.0f, 2, 0,
                                      { { 1, true, 50.0f },},},
                              { 1.0f, 1, 1,
                                      { { 0, true, 50.0f },},},},
                .deliveriesForBronze = 0,
                .deliveriesForSilver = 1,
                .deliveriesForGold = 2,
                .custom = true,
                .nodes = {{2.f, 15.f}, {2.f, 10.f}, {5.f, 5.f}, {13.f, 5.f}, {9.f, 8.f},
                          {9.f, 12.f}, {5.f, 15.f}, {13.f, 15.f}, {18.f, 12.f}, {14.f, 9.f}, {22.f, 9.f}},
                .adjacency_list = {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {3, 4} , {4, 5}, {5, 6}, {5, 7}, {6, 7},
                                   {7, 8}, {8, 9}, {8, 10}, {9, 10}},
        },
        // LEVEL 7
        {
                .name = "Roadblock",
                .friends = { { LADYBUG, false, 1 },
                             { FROG, false, 3 },
                             { MOUSE, false, 2 } },
                .offices = { { false, 0 }, },
                .snailCount = 2,
                .missions = { { 1.0f, 0, 0,
                                      { { 2, true, 15.0f },
                                              { 1, true, 20.0f }} },
                              { 5.0f, 0, 1,
                                      {{ 1, true, 15.0f },
                                              { 0, true, 20.0f },} },
                              { 10.0f, 0, 1,
                                      {{ 0, true, 15.0f },
                                              { 2, true, 20.0f },} }},
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 4,
                .deliveriesForGold = 6,
                .custom = true,
                .nodes = {{2.5f, 2.f}, {9.5f, 10.7f}, {6.8f, 15.3f}, {18.f, 9.4f},
                          {21.f, 16.f}},
                .adjacency_list = {{0, 1}, {0,2}, {0,3}, {1,3}, {1,2}, {2,4}, {3,4}},
        },
        // Level 8
        {
                .name = "Desirable Detour",
                .friends = {{ FROG, false, 1 },
                            { LADYBUG, false, 3 },
                            { BEE, false, 6 },
                            { MOUSE, false, 7 }},
                .offices = { { false, 4 },
                             {false, 5},
                             {false, 8}},
                .snailCount = 2,
                .missions = { { 0.5f, 0, 0,
                                      { { 0, true, 10.0f },
                                              { 1, true, 10.0f },}},
                              { 0.5f, 1, 1,
                                      { { 2, true, 50.0f },
                                              { 3, true, 50.0f },},},
                              { 20.0f, 2, 0,
                                      { { 1, true, 10.0f },
                                              { 0, true, 10.0f },},},},
                .deliveriesForBronze = 4,
                .deliveriesForSilver = 5,
                .deliveriesForGold = 6,
                .custom = true,
                .nodes = {
                        {7.375, 1.575},
                        {7.475, 6.375},
                        {16.1, 1.275},
                        {15.975, 6.1},
                        {5.175, 2.6},
                        {5.25, 11.325},
                        {9.325, 15.7},
                        {15.45, 15.425},
                        {18.575, 11.425},
                        {21.7, 7.55},
                        {18.925, 3.4},
                },
                .adjacency_list = { {0, 4}, {1, 4}, {0, 2}, {2, 10}, {1, 3}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {3, 8}, {9, 10} },
        },
        // LEVEL 9 : Cock-Quille
        {
                .friends = { { LADYBUG, false, 1 },
                             { MOUSE, false, 14 },
                             { FROG, false, 26 },
                },
                .offices = { { false, 0}, {false, 28},
                             {false, 29}},
                .snailCount = 2,
                .missions = { { 0.5f, 1, 0,
                                      { { 1, true, 10.0f }, {2, true, 50.0f},{ 0, true, 100.0f }, }},

                              { 0.5f, 2, 1,
                                      { {2, true, 10.0f}, {1, true, 50.0f}}}},
                .deliveriesForBronze = 0,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
                .custom = true,
                .nodes = {

                        // spiral
                        {9.f, 8.f}, {11.f, 6.f}, {13.f, 8.f}, {9.f, 10.f}, {5.f, 8.f}, {7.f, 6.f},
                        {12.f, 4.f}, {16.f, 8.f}, {9.f, 12.f}, {2.f, 8.f}, {6.f, 4.f},
                        {13.f, 2.f}, {19.f, 8.f},
                        // rest of shell
                        {15.f, 11.f}, {19.f, 14.f}, {3.f, 14.f}, {-1.f, 10.f},
                        // snail
                        {1.f, 16.f}, {3.f, 17.f}, {5.f, 16.f}, {7.f, 17.f}, {9.f, 16.f}, {11.f, 17.f},
                        {13.f, 16.f}, {15.f, 17.f}, {17.f, 16.f}, {19.f, 17.f}, {21.f, 16.f},
                        // antenni
                        {19.7f, 4.925f}, {22.6f, 4.925}
                },
                .adjacency_list = {{0,1}, {1,2}, {2,3}, {3,4}, {4,5}, {5,6}, {6,7},
                                   {7,8}, {8,9}, {9,10}, {10,11}, {11, 12}, {12, 13}, {13, 14},
                                   {14, 15}, {15, 9},    {17,18}, {18,19},{19,20},{20,21},{21,22},{22,23},{23,24},
                                   {24,25},{25,26},{26,27},{27,28},{27,29}, {15,17},{14,27}}

        },
        // LEVEL 10
        {
                .name = "Traffic Jam",
                .seeded = true,
                .seed = 0xdef9,
                .nodeCount = 4,
                .friends = {
                        { BEE, false, 0 } },
                .offices = { { false, 1 }},
                .snailCount = 3,
                .missions = {
                        { 1.0f, 0, 0, {{ 0, true, 13.f}}},
                        { 5.0f, 0, 0, {{ 0, true, 13.f}}},
                        { 10.0f, 0, 1, {{ 0, true, 13.f}}},
                        { 15.0f, 0, 1, {{ 0, true, 13.f}}},
                        { 20.0f, 0, 2, {{ 0, true, 13.f}}},
                        { 25.0f, 0, 2, {{ 0, true, 13.f}}},
                },
                .deliveriesForBronze = 2,
                .deliveriesForSilver = 3,
                .deliveriesForGold = 4,
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
        },
};

Level Level::getLevel(int levelNumber) {
    if(levelNumber > LEVELS.size())
        return {};

    return LEVELS[levelNumber - 1];
}

