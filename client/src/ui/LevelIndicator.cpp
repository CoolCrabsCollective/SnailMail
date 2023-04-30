//
// Created by william on 30/04/23.
//

#include "ui/LevelIndicator.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SpriteUtil.h"

LevelIndicator::LevelIndicator(World &world) : world(world) {
    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_INDICATOR));
    backgroundSprite.setPosition({50.0f, 50.0f});
}

void LevelIndicator::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    SpriteUtil::setSpriteSize(backgroundSprite, sf::Vector2f{50.f, 50.f});
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});

    target.draw(backgroundSprite);
}
