//
// Created by cedric on 4/29/23.
//
#include "world/friends/Friend.h"
#include "world/World.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"
#include "GameAssets.h"

Friend::Friend(World &world, GraphNode *node, const sf::Texture &texture) : GraphEntity(world, node),
                                        chatBubble(world, sf::Color(255, 255, 255)) {
    sprite.setTexture(texture);
}

const sf::Vector2f& Friend::getPosition() const {
    return getLocation()->getPosition();
}

sf::Vector2f Friend::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Friend::getZOrder() const {
    return ZOrder::LadyBug_ZOrder;
}

void Friend::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    chatBubble.draw(target, states, getPosition());

    sprite.setPosition(getPosition());
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{1.95f, 2.});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5, 1.});
    target.draw(sprite);
}

