//
// Created by william on 29/04/23.
//

#include "world/snail/Snail.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SFML/Graphics/RenderTarget.hpp"

Snail::Snail(World& world, GraphNode* node) : GraphEntity(world, node) {
    sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));

    actualPosition = node->getPosition();
}

const sf::Vector2f &Snail::getLocation() {
    return getLocation();
}

sf::Vector2f Snail::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Snail::getZOrder() const {
    return ZOrder::Snail;
}

void Snail::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition(actualPosition);
    sprite.setScale({1.0f / 160.0f, 1.0f / 90.0f});
    target.draw(sprite);
}

void Snail::tick(float delta) {
    if (isMoving) {
        tickMovement(isMoving);
    }
}

void Snail::moveLocation(GraphNode* node) {
    isMoving = true;
    setTargetLocation(node);

    const sf::Vector2f& startLoc = getLocation();
    const sf::Vector2f& endLoc = getTargetLocation();

    locDiff = endLoc - startLoc;
}

void Snail::tickMovement(float delta) {
    movingProgress += delta*progressRate;

    if (movingProgress < 1.0f) {
        actualPosition = getLocation() + locDiff * movingProgress;
    } else {
        setLocation(getTargetNode());
        isMoving = false;
        actualPosition = getLocation();
        movingProgress = .0f;
    }
}
