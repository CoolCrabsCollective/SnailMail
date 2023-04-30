//
// Created by william on 30/04/23.
//

#ifndef LD53_CLIENT_LEVELSELMENU_H
#define LD53_CLIENT_LEVELSELMENU_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "input/ClickableUI.h"

class World;

class LevelSelMenu : public sf::Drawable, public ClickableUI {
    mutable sf::Sprite backgroundSprite;
    mutable sf::Text label;

    mutable sf::Sprite exitButtonSprite;

    sf::Vector2f mainOffset = {800.0f, 450.0f};
    sf::Vector2f labelOffset = {-40.f, -170.f};
    sf::Vector2f buttonOffset = {310.f, -140.f};

    sf::Vector2f mainSize = {800.f, 400.f};

    World& world;

    bool isOpen = false;

public:
    LevelSelMenu(World &world);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    bool getIsOpen() const;

    void setIsOpen(bool isOpen);

    void hitAction(bool& isHit) override;

    ~LevelSelMenu() = default;
};

#endif //LD53_CLIENT_LEVELSELMENU_H
