//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_SIDEBAR_H
#define LD53_CLIENT_SIDEBAR_H

#include "SFML/Graphics.hpp"
#include "world/World.h"

class Sidebar : public sf::Drawable
{
protected:
    World& world;
    mutable sf::Sprite snail_sprite;
    mutable sf::Sprite snail_cap_sprite;
    mutable sf::Sprite friend_sprite;
    mutable sf::Text number_text;
    mutable sf::Text deliveryText;
public:
    Sidebar(World& world);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    constexpr static float DISTANCE_TO_SIDEBAR = 1200.f;
};

#endif //LD53_CLIENT_SIDEBAR_H
