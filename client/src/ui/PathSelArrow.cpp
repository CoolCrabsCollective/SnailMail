//
// Created by william on 29/04/23.
//

#include "ui/PathSelArrow.h"
#include "SpriteUtil.h"
#include "GameAssets.h"
#include "world/World.h"

PathSelArrow::PathSelArrow(World &world, sf::Color color) : Clickable({-.5f, -.5f}, {.5f, .5f}),
                                                                            world(world) {
    sprite.setTexture(*world.getAssets().get(GameAssets::PATH_SEL_ARROW));
    sprite.setColor(color);
}

void PathSelArrow::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{1., 1.});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});

    for (int i = 0; i<arrowPositions.size(); i++) {
        sprite.setPosition(arrowPositions.at(i));
        sprite.setRotation(sf::radians(arrowAngles.at(i)));

        target.draw(sprite);
    }
}

void PathSelArrow::updatePositions(GraphNode* currentNode, sf::Color snail_color) {
    arrowPositions.clear();
    arrowAngles.clear();
    graphNodes.clear();
    for (GraphNode* neighbor : currentNode->getNeighbors()) {
        Path& path = world.getGraph()->getPath(currentNode, neighbor);
        if (path.isBlocked(currentNode, snail_color))
            continue;

        bool neighbor_blocking = false;
        for(Snail* snail : world.getSnails())
        {
            if(neighbor == snail->getLocation())
            {
                neighbor_blocking = true;
                break;
            }
        }

        if(neighbor_blocking)
            continue;

        sf::Vector2f dir = neighbor->getPosition() - currentNode->getPosition();
        float angle = atanf(dir.y / dir.x);

        if (dir.x < 0) {
            angle = angle + M_PI;
        }

        arrowPositions.push_back({cosf(angle) * spawnRadius + currentNode->getPosition().x,
                                  sinf(angle) * spawnRadius + currentNode->getPosition().y});
        arrowAngles.push_back(angle + M_PI / 2);
        graphNodes.push_back(neighbor);
    }
}

GraphNode* PathSelArrow::hitScanAll(const sf::Vector2f &hit) {
    for (int i = 0; i<arrowPositions.size(); i++) {
        if (hitScan(hit, arrowPositions.at(i))) {
            return graphNodes.at(i);
        }
    }

    return nullptr;
}
