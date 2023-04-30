//
// Created by william on 30/04/23.
//

#include "ui/LevelSelMenu.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "world/World.h"

LevelSelMenu::LevelSelMenu(World &world) : Clickable(buttonOffset, buttonOffset + sf::Vector2f{50.f, 50.f},
                                                     mainOffset, &isOpen, &isOpen), world(world) {
    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_SEL_MENU_BACKDROP));
    backgroundSprite.setPosition(mainOffset);
    SpriteUtil::setSpriteSize(backgroundSprite, mainSize);
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});

    label.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    label.setFillColor(sf::Color::Black);
    label.setPosition(mainOffset + labelOffset);
    label.setString("LEVELS");

    exitButtonSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_SEL_MENU_EXIT));
    exitButtonSprite.setPosition(mainOffset + buttonOffset);
    SpriteUtil::setSpriteSize(exitButtonSprite, sf::Vector2f{50.f, 50.f});
    SpriteUtil::setSpriteOrigin(exitButtonSprite, sf::Vector2f{0.5f, 0.5f});
}

void LevelSelMenu::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if (!isOpen)
        return;

    target.draw(backgroundSprite);
    target.draw(label);
    target.draw(exitButtonSprite);
}

bool LevelSelMenu::getIsOpen() const {
    return isOpen;
}

void LevelSelMenu::setIsOpen(bool isOpen) {
    LevelSelMenu::isOpen = isOpen;
}
