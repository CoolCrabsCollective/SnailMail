//
// Created by william on 30/04/23.
//

#include "ui/LevelItem.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/World.h"

LevelItem::LevelItem(World &world, LevelSelMenu& levelSelMenu, sf::Vector2f parentMenuOffset, int levelNum) : ClickableUI({0.f, 0.f},
                                                                                                                    {0.f, 0.f}),
                                                                           world(world), levelSelMenu(levelSelMenu), parentMenuOffset(parentMenuOffset), levelNum(levelNum) {
    calculateOffsets();

    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_SEL_MENU_ITEM));
    backgroundSprite.setPosition(mainOffset);

    level_num.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    level_num.setFillColor(sf::Color::Black);
    level_num.setPosition(numOffset);
    std::string levelNumString = std::to_string(levelNum + 1);

    if (levelNumString.length() < 2) {
        levelNumString.insert(0, "0");
    }
    level_num.setString(levelNumString);
}

void LevelItem::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    SpriteUtil::setSpriteSize(backgroundSprite, size);
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});
    target.draw(backgroundSprite);



    target.draw(level_num);
}

void LevelItem::hitAction(bool& isHit) {
//    if (isHit) {
//        levelSelMenu.setIsOpen(true);
//    }
}

void LevelItem::calculateOffsets() {
    int rowNum = 0;
    if (levelNum > 5) {
        rowNum = (levelNum + 1) % 6;
    }

    float yPos = -95.f + (size.y + 25.f) * (float) rowNum;

    float xPos = -270.f + (25.f + size.x) * (float) levelNum;

    mainOffset = parentMenuOffset + sf::Vector2f{xPos, yPos};
    numOffset = mainOffset + sf::Vector2f{-10.f, -20.f};
}
