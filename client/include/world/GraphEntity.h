//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_GRAPHENTITY_H
#define LD53_CLIENT_GRAPHENTITY_H

#include "Entity.h"
#include "GraphNode.h"

class GraphEntity : public Entity {
protected:
    GraphNode* location = nullptr;
    GraphNode* destination = nullptr;

public:
    GraphEntity(World& world, GraphNode* node) : Entity(world), location(node) {}

    [[nodiscard]]
    virtual const sf::Vector2f& getPosition() const = 0;

    [[nodiscard]]
    const sf::Vector2f& getTargetPosition() { return destination->getPosition(); }

    [[nodiscard]]
    GraphNode* getDestination() const { return destination; }

    [[nodiscard]]
    GraphNode* getLocation() const { return location; }

    void setLocation(GraphNode* location) {
        GraphEntity::location = location;
    }

    void setDestination(GraphNode* destination) {
        GraphEntity::destination = destination;
    }

    virtual ZOrder getZOrder() const = 0;

    [[nodiscard]]
    virtual bool shouldBeRemoved() const {
        return false;
    }

    virtual ~GraphEntity() = default;
};

#endif //LD53_CLIENT_GRAPHENTITY_H
