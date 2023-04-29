//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_GRAPHENTITY_H
#define LD53_CLIENT_GRAPHENTITY_H

#include "Entity.h"
#include "GraphNode.h"

class GraphEntity : public Entity {
protected:
    GraphNode* startLocation = nullptr;
    GraphNode* targetLocation = nullptr;

public:
    GraphEntity(World& world, GraphNode* node) : Entity(world), startLocation(node) {}

    [[nodiscard]]
    virtual const sf::Vector2f& getLocation() const = 0;

    [[nodiscard]]
    const sf::Vector2f& getTargetLocation() { return targetLocation->getPosition(); }

    [[nodiscard]]
    GraphNode* getTargetNode() const { return targetLocation; }

    [[nodiscard]]
    GraphNode* getStartNode() const { return startLocation; }

    void setLocation(GraphNode *location) {
        GraphEntity::startLocation = location;
    }

    void setTargetLocation(GraphNode *targetLocation) {
        GraphEntity::targetLocation = targetLocation;
    }

    virtual ZOrder getZOrder() const = 0;

    [[nodiscard]]
    virtual bool shouldBeRemoved() const {
        return false;
    }

    virtual ~GraphEntity() = default;
};

#endif //LD53_CLIENT_GRAPHENTITY_H
