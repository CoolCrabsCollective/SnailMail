//
// Created by cedric on 4/29/23.
//
#include "world/friends/Friend.h"
#include "world/World.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"

Friend::Friend(World &world, GraphNode *node, const sf::Texture &texture) : GraphEntity(world, node) {
    sprite.setTexture(texture);
}

const sf::Vector2f& Friend::getLocation() const {
    return getStartNode()->getPosition();
}

sf::Vector2f Friend::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Friend::getZOrder() const {
    return ZOrder::LadyBug_ZOrder;
}

void Friend::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition(getLocation());
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{1.95f, 2.});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5, 1.});
    target.draw(sprite);
}

