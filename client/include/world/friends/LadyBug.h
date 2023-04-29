//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_LADYBUG_H
#define LD53_CLIENT_LADYBUG_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"
#include "world/World.h"

class LadyBug : public GraphEntity {
    mutable sf::Sprite sprite;


public:
    LadyBug(World& world, GraphNode* node);

    const sf::Vector2f& getPosition() const override;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif //LD53_CLIENT_LADYBUG_H
