//
// Created by william on 30/04/23.
//

#ifndef LD53_CLIENT_LEVELINDICATOR_H
#define LD53_CLIENT_LEVELINDICATOR_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class World;

class LevelIndicator : public sf::Drawable {
    mutable sf::Sprite backgroundSprite;
    World& world;

public:
    LevelIndicator(World &world);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    ~LevelIndicator() = default;
};

#endif //LD53_CLIENT_LEVELINDICATOR_H
