//
// Created by william on 29/04/23.
//

#include "ui/PathSelArrow.h"
#include "SpriteUtil.h"
#include "GameAssets.h"
#include "world/World.h"

PathSelArrow::PathSelArrow(World& world) {
    sprite.setTexture(*world.getAssets().get(GameAssets::PATH_SEL_ARROW));
}

void PathSelArrow::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition({0.0f, 0.0f});
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});
    target.draw(sprite);
}

void PathSelArrow::tick(float delta) {
}