//
// Created by cedric on 4/29/23.
//

#include "world/friends/LadyBug.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"

LadyBug::LadyBug(World& world, GraphNode* node) : Friend(world, node, *world.getAssets().get(GameAssets::LADY_BUG),
                                                         *world.getAssets().get(GameAssets::LADY_BUG_LETTER)) {

}