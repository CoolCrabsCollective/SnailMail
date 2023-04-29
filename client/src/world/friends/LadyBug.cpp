//
// Created by cedric on 4/29/23.
//

#include "world/friends/LadyBug.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"

LadyBug::LadyBug(World& world, GraphNode* node) : GraphEntity(world, node) {
    sprite.setTexture(*world.getAssets().get(GameAssets::LADY_BUG));
}

const sf::Vector2f& LadyBug::getLocation() const {
    return getStartNode()->getPosition();
}

sf::Vector2f LadyBug::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder LadyBug::getZOrder() const {
    return ZOrder::LadyBug_ZOrder;
}

void LadyBug::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition(getLocation());
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5, 1.});
    target.draw(sprite);
}
