//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_ENTITYSELECTION_H
#define LD53_CLIENT_ENTITYSELECTION_H

#include "world/World.h"

class EntitySelection {
private:
    World& world;

public:
    EntitySelection(World& world);

    void clickScan(sf::Vector2f clickPos);
};

#endif //LD53_CLIENT_ENTITYSELECTION_H
