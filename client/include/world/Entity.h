//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_ENTITY_H
#define LD53_CLIENT_ENTITY_H

#include "SFML/System/Vector2.hpp"
#include "Tickable.h"
#include "SFML/Graphics/Drawable.hpp"
#include "ZOrder.h"

class World;

class Entity : public sf::Drawable {
protected:
    World& world;
public:

    Entity(World& world)
            : world(world) {}

    virtual ~Entity() = default;

    [[nodiscard]]
    World& getWorld() const {
        return world;
    }

    [[nodiscard]]
    virtual const sf::Vector2f& getPosition() const = 0;

    [[nodiscard]]
    virtual sf::Vector2f getVisualSize() const {
        return sf::Vector2f { 1.0f, 1.0f };
    }

    virtual ZOrder getZOrder() const = 0;

    [[nodiscard]]
    virtual bool shouldBeRemoved() const {
        return false;
    }
};

#endif //LD53_CLIENT_ENTITY_H
