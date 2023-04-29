//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_ENTITYSELECTION_H
#define LD53_CLIENT_ENTITYSELECTION_H

#include "SFML/System/Vector2.hpp"
#include "world/GraphNode.h"

class World;

class EntitySelection {
private:
    World& world;
    GraphNode* selected = nullptr;

public:
    EntitySelection(World& world);

    GraphNode* clickScan(sf::Vector2f clickPos);

    GraphNode *getSelected() const;

    void setSelected(GraphNode *selected);
};

#endif //LD53_CLIENT_ENTITYSELECTION_H
