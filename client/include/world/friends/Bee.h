//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_BEE_H
#define LD53_CLIENT_BEE_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"
#include "world/friends/Friend.h"
#include "world/World.h"

class Bee : public Friend {
public:
    Bee(World& world, GraphNode* node);

    const FriendType getFriendType() const override;
};

#endif //LD53_CLIENT_BEE_H
