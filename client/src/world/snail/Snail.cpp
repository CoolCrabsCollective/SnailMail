//
// Created by william on 29/04/23.
//

#include "world/snail/Snail.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SFML/Graphics/RenderTarget.hpp"

Snail::Snail(World& world) : Entity(world) {
    sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
}

const sf::Vector2f &Snail::getLocation() {
    return { 0.0f, 0.0f };
}

sf::Vector2f Snail::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Snail::getZOrder() const {
    return ZOrder::Snail;
}

void Snail::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition({ 0.0f, 0.0f });
    sprite.setScale({1.0f / 160.0f, 1.0f / 90.0f});
    target.draw(sprite);
}

void Snail::tick(float delta) {

}
