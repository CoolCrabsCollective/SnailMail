//
// Created by william on 29/04/23.
//

#include "world/snail/SnailCum.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SFML/Graphics/RenderTarget.hpp"

SnailCum::SnailCum(World& world) : Entity(world) {
    sprite.setTexture(*world.getAssets().get(GameAssets::WHITE_PIXEL));
}

const sf::Vector2f &SnailCum::getLocation() {
    return { 0.0f, 0.0f };
}

sf::Vector2f SnailCum::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder SnailCum::getZOrder() const {
    return ZOrder::Goo_ZOrder;
}

void SnailCum::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition({ 0.0f, 0.0f });
    sprite.setScale({1.0f / 160.0f, 1.0f / 90.0f});
    target.draw(sprite);
}
