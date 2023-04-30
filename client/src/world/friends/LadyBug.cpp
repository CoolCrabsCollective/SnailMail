//
// Created by cedric on 4/29/23.
//

#include "world/friends/LadyBug.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"

LadyBug::LadyBug(World& world, GraphNode* node) : Friend(world, node, *world.getAssets().get(GameAssets::LADY_BUG_SPRITE_SHEET), 0.3f, 2.0f) {

}

const FriendType LadyBug::getFriendType() const {
    return LADYBUG;
}