//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_MOUSE_H
#define LD53_CLIENT_MOUSE_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"
#include "world/friends/Friend.h"
#include "world/World.h"

class Mouse : public Friend {
public:
    Mouse(World& world, GraphNode* node);
};

#endif //LD53_CLIENT_MOUSE_H
