//
// Created by adrien on 01/05/23.
//

#include "world/friends/Duck.h"
#include "world/World.h"
#include "GameAssets.h"

Duck::Duck(World& world, GraphNode* node) : Friend(world, node, *world.getAssets().get(GameAssets::DUCK_SPRITE_SHEET), 0.3f, 2.0f) {

}

const FriendType Duck::getFriendType() const {
    return DUCK;
}
