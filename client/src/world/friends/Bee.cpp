//
// Created by cedric on 4/29/23.
//
//
// Created by cedric on 4/29/23.
//

#include "world/friends/Bee.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"

Bee::Bee(World& world, GraphNode* node) : Friend(world, node, *world.getAssets().get(GameAssets::BEE),
                                                 *world.getAssets().get(GameAssets::BEE_LETTER)) {

}

