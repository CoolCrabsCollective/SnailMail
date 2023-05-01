//
// Created by william on 30/04/23.
//

#ifndef LD53_CLIENT_LEVELITEM_H
#define LD53_CLIENT_LEVELITEM_H

#include "SFML/Graphics/Drawable.hpp"
#include "input/ClickableUI.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ui/LevelIndicator.h"

class World;
class LevelSelMenu;

class LevelItem : public sf::Drawable, public ClickableUI {
    mutable sf::Sprite backgroundSprite;

    mutable sf::Text level_num;

    sf::Vector2f parentMenuOffset;
    sf::Vector2f mainOffset;
    sf::Vector2f numOffset;

    sf::Vector2f size = {70.f, 70.f};

    std::string levelNumString;

    World& world;

    int levelNum = 0;

public:
    LevelItem(World &world, sf::Vector2f parentMenuOffset, int levelNum);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void hitAction(bool& isHit) override;

    void calculateOffsets();

    ~LevelItem() = default;
};

#endif //LD53_CLIENT_LEVELITEM_H
