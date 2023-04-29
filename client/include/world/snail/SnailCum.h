//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_SNAILCUM_H
#define LD53_CLIENT_SNAILCUM_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/World.h"

class SnailCum : public Entity {
    mutable sf::Sprite sprite;
public:
    SnailCum(World& world);

    const sf::Vector2f &getLocation() override;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif //LD53_CLIENT_SNAILCUM_H
