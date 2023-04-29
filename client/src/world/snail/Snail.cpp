//
// Created by william on 29/04/23.
//

#include <iostream>
#include "world/snail/Snail.h"
#include "GameAssets.h"
#include "world/World.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"

Snail::Snail(World& world, GraphNode* node, sf::Color snail_color) : GraphEntity(world, node), pathSelArrow(world) {
    snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
    snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));

    snail_cap_sprite.setColor(snail_color);
    actualPosition = node->getPosition();
    if(!node->getNeighbors().empty())
        moveLocation(node->getNeighbors()[0]);
}

const sf::Vector2f& Snail::getLocation() const {
    return actualPosition;
}

sf::Vector2f Snail::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Snail::getZOrder() const {
    return ZOrder::Snail_ZOrder;
}

void Snail::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
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
    pathSelArrow.draw(target, states);
}

void Snail::tick(float delta) {
    if (isMoving) {
        tickMovement(delta);
    }
}

void Snail::moveLocation(GraphNode* node) {
    if (isMoving || !world.getGraph()->areAdjacent(getStartNode(), node))
        return;

    std::pair<GraphNode*, GraphNode*> key;
    if (getStartNode() < node) {
        key = {getStartNode(), node};
    } else {
        key = {node, getStartNode()};
    }

    auto found = world.getGraph()->adjacencyMap.find(key);
    if (found == world.getGraph()->adjacencyMap.end() || world.getGraph()->adjacencyMap.find(key)->second.cummed)
        return;

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
    snail_sprite.setRotation(sf::radians(angle));
    snail_cap_sprite.setRotation(sf::radians(angle));
}

void Snail::tickMovement(float delta) {
    currentProgressRate = progressRate / locDiff.length();
    movingProgress += delta * currentProgressRate;
    if (movingProgress < 1.0f) {
        actualPosition = this->getStartNode()->getPosition() + locDiff * movingProgress;

        std::pair<GraphNode*, GraphNode*> key;
        bool backdoor = false;
        if (getStartNode() < getTargetNode()) {
            key = {getStartNode(), getTargetNode()};
        } else {
            backdoor = true;
            key = {getTargetNode(), getStartNode()};
        }

        world.getGraph()->adjacencyMap.find(key)->second.setCumminess(movingProgress, backdoor);
    } else {
        std::pair<GraphNode*, GraphNode*> key;
        if (getStartNode() < getTargetNode()) {
            key = {getStartNode(), getTargetNode()};
        } else {
            key = {getTargetNode(), getStartNode()};
        }

        world.getGraph()->adjacencyMap.find(key)->second.setCummed(true);

        setLocation(getTargetNode());
        isMoving = false;
        actualPosition = getLocation();
        movingProgress = .0f;
    }
}
