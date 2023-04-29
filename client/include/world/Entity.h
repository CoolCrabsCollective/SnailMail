//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_ENTITY_H
#define LD53_CLIENT_ENTITY_H

//
// Created by Alexander Winter on 2023-01-06.
//

#ifndef LD52_CLIENT_ENTITY_H
#define LD52_CLIENT_ENTITY_H

#include "SFML/System/Vector2.hpp"
#include "Tickable.h"
#include "SFML/Graphics/Drawable.hpp"

class World;

class Entity : public Tickable, public sf::Drawable {
protected:
    World& world;
    sf::Vector2f location;
public:

    Entity(World& world,
           sf::Vector2f location)
            : world(world), location(location) {}

    virtual ~Entity() = default;

    [[nodiscard]]
    World& getWorld() const {
        return world;
    }

    [[nodiscard]]
    const sf::Vector2f& getLocation() const {
        return location;
    }

    [[nodiscard]]
    virtual sf::Vector2f getVisualSize() const {
        return sf::Vector2f { 1.0f, 1.0f };
    }

    virtual float getZOrder() const {
        return 0.;
    };

    [[nodiscard]]
    virtual bool shouldBeRemoved() const {
        return false;
    }
};

#endif //LD52_CLIENT_ENTITY_H

#endif //LD53_CLIENT_ENTITY_H
