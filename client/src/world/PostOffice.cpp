//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/PostOffice.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"

PostOffice::PostOffice(World &world, GraphNode *node)
    : GraphEntity(world, node) {

    sprite.setTexture(*world.getAssets().get(GameAssets::POST_OFFICE));
}

const sf::Vector2f &PostOffice::getPosition() const {
    return location->getPosition();
}

ZOrder PostOffice::getZOrder() const {
    return ZOrder::PostOffice_ZOrder;
}

void PostOffice::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    SpriteUtil::setSpriteSize(sprite, {2.0f, 2.0f});
    SpriteUtil::setSpriteOrigin(sprite, {0.5f, 1.0f});
    sprite.setPosition(getPosition());
    target.draw(sprite);
}
