//
// Created by william on 29/04/23.
//

#include "world/snail/Snail.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"
#include "ui/PathSelArrow.h"

Snail::Snail(World& world, GraphNode* node, sf::Color snail_color) : GraphEntity(world, node), snail_color(snail_color) {
    snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
    snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));

    snail_cap_sprite.setColor(snail_color);
    actualPosition = node->getPosition();
    if(!node->getNeighbors().empty())
        moveLocation(node->getNeighbors()[0]);

    pathSelArrow = new PathSelArrow(world, snail_color);
}

const sf::Vector2f &Snail::getPosition() const {
    return actualPosition;
}

sf::Vector2f Snail::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Snail::getZOrder() const {
    return ZOrder::Snail_ZOrder;
}

void Snail::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (!isMoving)
        pathSelArrow->draw(target, states);

    snail_sprite.setPosition(actualPosition);
    snail_cap_sprite.setPosition(actualPosition);
    SpriteUtil::setSpriteSize(snail_sprite, sf::Vector2f{2., 2.});
    SpriteUtil::setSpriteSize(snail_cap_sprite, sf::Vector2f{2., 2.});
    float scaleX = snail_sprite.getScale().x;
    float scaleY = snail_sprite.getScale().y;
    if(locDiff.x >= 0)
    {
        snail_sprite.setScale(sf::Vector2f {std::abs(scaleX), std::abs(scaleY)});
        snail_cap_sprite.setScale(sf::Vector2f {std::abs(scaleX), std::abs(scaleY)});
    }
    else
    {
        snail_sprite.setScale(sf::Vector2f {-std::abs(scaleX), std::abs(scaleY)});
        snail_cap_sprite.setScale(sf::Vector2f {-std::abs(scaleX), std::abs(scaleY)});
    }

    SpriteUtil::setSpriteOrigin(snail_sprite, sf::Vector2f{0.5f, 1.f});
    SpriteUtil::setSpriteOrigin(snail_cap_sprite, sf::Vector2f{0.5f, 1.f});
    if(!isMoving)
    {
        snail_sprite.setRotation(sf::radians(0));
        snail_cap_sprite.setRotation(sf::radians(0));
    }

    target.draw(snail_sprite);
    target.draw(snail_cap_sprite);
}

void Snail::tick(float delta) {
    if (isMoving) {
        tickMovement(delta);
        arrowPosUpdated = false;
    } else {
        if (!arrowPosUpdated) {
            pathSelArrow->updatePositions(getStartNode());
            arrowPosUpdated = true;
        }
    }
}

void Snail::moveLocation(GraphNode* node) {
    if (isMoving || !world.getGraph()->areAdjacent(getStartNode(), node) || !node)
        return;

    if(!world.getGraph()->areAdjacent(getStartNode(), node)
    || world.getGraph()->getPath(getStartNode(), node).cummed)
        return;

    isMoving = true;
    setTargetLocation(node);

    const sf::Vector2f& startLoc = getPosition();
    const sf::Vector2f& endLoc = getTargetPosition();
    locDiff = endLoc - startLoc;
    float angle = std::atan2(locDiff.y, locDiff.x);
    if(endLoc.x < startLoc.x)
    {
        angle += M_PI;
    }
    snail_sprite.setRotation(sf::radians(angle));
    snail_cap_sprite.setRotation(sf::radians(angle));
}

void Snail::tickMovement(float delta) {
    currentProgressRate = progressRate / locDiff.length();
    movingProgress += delta * currentProgressRate;
    if (movingProgress < 1.0f) {
        actualPosition = this->getStartNode()->getPosition() + locDiff * movingProgress;
        world.getGraph()->getPath(getStartNode(), getTargetNode()).setCumminess(movingProgress, getStartNode() >= getTargetNode());
    } else {

        world.getGraph()->getPath(getStartNode(), getTargetNode()).setCummed(true);
        setLocation(getTargetNode());
        isMoving = false;
        actualPosition = getPosition();
        movingProgress = .0f;
    }
}

GraphNode* Snail::hitScan(const sf::Vector2f& hit) {
    if (isMoving)
        return nullptr;

    GraphNode* target = pathSelArrow->hitScanAll(hit);
    if (target)
        moveLocation(target);
    return target;
}
