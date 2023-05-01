//
// Created by cedric on 4/29/23.
//
//
// Created by cedric on 4/29/23.
//

#include "world/friends/Bee.h"
#include "world/World.h"
#include "GameAssets.h"

Bee::Bee(World& world, GraphNode* node) : Friend(world, node, *world.getAssets().get(GameAssets::BEE_SPRITE_SHEET), 0.3f, 2.0f) {

}

const FriendType Bee::getFriendType() const {
    return BEE;
}

