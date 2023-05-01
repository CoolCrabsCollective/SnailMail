//
// Created by william on 30/04/23.
//

#include "ui/LevelIndicator.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SpriteUtil.h"
#include "ui/LevelSelMenu.h"

LevelIndicator::LevelIndicator(World &world, LevelSelMenu& levelSelMenu) : ClickableUI({0.f, 0.f},
                                                                                       {0.f, 0.f}),
                                                           world(world), levelSelMenu(levelSelMenu) {
    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_INDICATOR));
    backgroundSprite.setPosition(mainOffset);

    level_num.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    level_num.setFillColor(sf::Color::White);
    level_num.setScale({1.2f, 1.2f});
    level_num.setOutlineColor(sf::Color::Black);
    level_num.setOutlineThickness(1.f);
    level_num.setStyle(sf::Text::Bold);
    level_num.setPosition(mainOffset + numOffset);

    label.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    label.setFillColor(sf::Color::White);
    label.setScale({1.2f, 1.2f});
    label.setOutlineColor(sf::Color::Black);
    label.setOutlineThickness(1.f);
    label.setStyle(sf::Text::Bold);
    label.setPosition(mainOffset + labelOffset);
    label.setString("LEVEL ");

    ClickableUI::boundingBoxBL = mainOffset - (sf::Vector2f{50.f, 50.f} / 2.f);
    ClickableUI::boundingBoxTR = mainOffset + (sf::Vector2f{50.f, 50.f} / 2.f);
}

void LevelIndicator::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    SpriteUtil::setSpriteSize(backgroundSprite, sf::Vector2f{50.f, 50.f});
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});
    target.draw(backgroundSprite);


    std::string levelNum = std::to_string(world.getCurrentLevelNumber());

    if (levelNum.length() < 2) {
        levelNum.insert(0, "0");
    }
    levelNum += ": " + world.getCurrentLevel().name;

    level_num.setString(levelNum);
    target.draw(level_num);


    target.draw(label);
}

void LevelIndicator::hitAction(bool& isHit) {
    if (isHit) {
        levelSelMenu.setIsOpen(true);
    }
}
