//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_PATHSELARROW_H
#define LD53_CLIENT_PATHSELARROW_H

#include "world/Tickable.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"

class World;

class PathSelArrow: public Tickable {
    mutable sf::Sprite sprite;

public:
    PathSelArrow(World& world);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;

    void tick(float delta);

};

#endif //LD53_CLIENT_PATHSELARROW_H
