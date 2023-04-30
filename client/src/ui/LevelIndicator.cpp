//
// Created by william on 30/04/23.
//

#include "ui/LevelIndicator.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SpriteUtil.h"

LevelIndicator::LevelIndicator(World &world) : world(world) {
    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_INDICATOR));
    backgroundSprite.setPosition(mainOffset);

    level_num.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    level_num.setFillColor(sf::Color::Black);
    level_num.setPosition(mainOffset + numOffset);

    label.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    label.setFillColor(sf::Color::Black);
    label.setPosition(mainOffset + labelOffset);
    label.setString("LEVEL:");
}

void LevelIndicator::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    SpriteUtil::setSpriteSize(backgroundSprite, sf::Vector2f{50.f, 50.f});
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});
    target.draw(backgroundSprite);


    std::string levelNum = std::to_string(world.getCurrentLevelNumber());

    if (levelNum.length() < 2) {
        levelNum.insert(0, "0");
    }
    level_num.setString(levelNum);
    target.draw(level_num);


    target.draw(label);
}
