//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_SNAIL_H
#define LD53_CLIENT_SNAIL_H

#include "world/Entity.h"
#include "SFML/Graphics/Sprite.hpp"

class Snail : public Entity {
    mutable sf::Sprite sprite;
public:
    Snail(World& world);

    const sf::Vector2f &getLocation() override;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void tick(float delta);
};

#endif //LD53_CLIENT_SNAIL_H
