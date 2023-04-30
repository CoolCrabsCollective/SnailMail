//
// Created by william on 30/04/23.
//

#ifndef LD53_CLIENT_LEVELINDICATOR_H
#define LD53_CLIENT_LEVELINDICATOR_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class World;

class LevelIndicator : public sf::Drawable {
    mutable sf::Sprite backgroundSprite;
    mutable sf::Text label;

    mutable sf::Text level_num;

    sf::Vector2f mainOffset = {50.0f, 55.0f};
    sf::Vector2f numOffset = {30.f, -60.f};

    sf::Vector2f labelOffset = {-40.f, -60.f};

    std::string levelNum;

    World& world;

public:
    LevelIndicator(World &world);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    ~LevelIndicator() = default;
};

#endif //LD53_CLIENT_LEVELINDICATOR_H
