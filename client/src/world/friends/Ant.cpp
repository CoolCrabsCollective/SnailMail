//
// Created by adrien on 01/05/23.
//

#include "world/friends/Ant.h"
#include "world/World.h"
#include "GameAssets.h"

Ant::Ant(World& world, GraphNode* node) : Friend(world, node, *world.getAssets().get(GameAssets::ANT_SPRITE_SHEET), 0.3f, 2.0f) {

}

const FriendType Ant::getFriendType() const {
    return ANT;
}
