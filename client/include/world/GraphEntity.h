//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_GRAPHENTITY_H
#define LD53_CLIENT_GRAPHENTITY_H

#include "Entity.h"
#include "GraphNode.h"

class GraphEntity : public Entity {
private:
    GraphNode* location = nullptr;

public:
    GraphEntity(World& world, GraphNode* node) : Entity(world), location(node) {}

    [[nodiscard]]
    const sf::Vector2f& getLocation() { return location->getPosition(); }

    virtual ZOrder getZOrder() const = 0;

    [[nodiscard]]
    virtual bool shouldBeRemoved() const {
        return false;
    }

    virtual ~GraphEntity() = default;
};

#endif //LD53_CLIENT_GRAPHENTITY_H
