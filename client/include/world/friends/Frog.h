//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_FROG_H
#define LD53_CLIENT_FROG_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"
#include "world/friends/Friend.h"
#include "world/World.h"

class Frog : public Friend {
public:
    Frog(World& world, GraphNode* node);
};

#endif //LD53_CLIENT_FROG_H
