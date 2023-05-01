//
// Created by adrien on 01/05/23.
//

#ifndef LD53_CLIENT_ANT_H
#define LD53_CLIENT_ANT_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"
#include "world/friends/Friend.h"
#include "world/World.h"

class Ant : public Friend {
public:
    Ant(World& world, GraphNode* node);

    const FriendType getFriendType() const override;
};

#endif //LD53_CLIENT_ANT_H
