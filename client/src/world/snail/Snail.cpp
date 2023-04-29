//
// Created by william on 29/04/23.
//

#include <iostream>
#include "world/snail/Snail.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"

Snail::Snail(World& world, GraphNode* node) : GraphEntity(world, node) {
    sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));

    actualPosition = node->getPosition();
    moveLocation(node->getNeighbors()[0]);
}

const sf::Vector2f &Snail::getLocation() {
    return actualPosition;
}

sf::Vector2f Snail::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Snail::getZOrder() const {
    return ZOrder::Snail_ZOrder;
}

void Snail::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition(actualPosition);
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
    float scaleX = sprite.getScale().x;
    float scaleY = sprite.getScale().y;
    if(locDiff.x >= 0)
        sprite.setScale(sf::Vector2f {std::abs(scaleX), std::abs(scaleY)});
    else
        sprite.setScale(sf::Vector2f {-std::abs(scaleX), std::abs(scaleY)});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 1.f});
    if(!isMoving)
    {
        sprite.setRotation(sf::radians(0));
    }

    target.draw(sprite);
}

void Snail::tick(float delta) {
    if (isMoving) {
        tickMovement(delta);
    }
}

void Snail::moveLocation(GraphNode* node) {
    isMoving = true;
    setTargetLocation(node);

    const sf::Vector2f& startLoc = getLocation();
    const sf::Vector2f& endLoc = getTargetLocation();
    locDiff = endLoc - startLoc;
    float angle = std::atan2(locDiff.y, locDiff.x);
    if(endLoc.x < startLoc.x)
    {
        angle += M_PI;
    }
    sprite.setRotation(sf::radians(angle));
}

void Snail::tickMovement(float delta) {
    currentProgressRate = progressRate / locDiff.length();
    movingProgress += delta * currentProgressRate;
    if (movingProgress < 1.0f) {
        actualPosition = this->getStartNode()->getPosition() + locDiff * movingProgress;
    } else {
        setLocation(getTargetNode());
        isMoving = false;
        actualPosition = getLocation();
        movingProgress = .0f;
    }
}
