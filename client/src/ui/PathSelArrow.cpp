//
// Created by william on 29/04/23.
//

#include "ui/PathSelArrow.h"
#include "SpriteUtil.h"
#include "GameAssets.h"
#include "world/World.h"

PathSelArrow::PathSelArrow(World &world) : Clickable({-1.0f, -1.0f}, {1.0f, 1.0f}) {
    sprite.setTexture(*world.getAssets().get(GameAssets::PATH_SEL_ARROW));
}

void PathSelArrow::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});

    for (int i = 0; i<arrowPositions.size(); i++) {
        sprite.setPosition(arrowPositions.at(i));
        sprite.setRotation(sf::radians(arrowAngles.at(i)));

        target.draw(sprite);
    }
}

void PathSelArrow::updatePositions(GraphNode* currentNode) {
    arrowPositions.clear();
    arrowAngles.clear();
    for (GraphNode* neighbor : currentNode->getNeighbors()) {
        sf::Vector2f dir = neighbor->getPosition() - currentNode->getPosition();
        float angle = atanf(dir.y / dir.x);

        if (dir.x < 0) {
            angle = angle + M_PI;
        }

        arrowPositions.push_back({cosf(angle) * spawnRadius + currentNode->getPosition().x,
                                  sinf(angle) * spawnRadius + currentNode->getPosition().y});
        arrowAngles.push_back(angle + M_PI / 2);
    }
}

bool PathSelArrow::hitScanAll(const sf::Vector2f &hit) {
    for (sf::Vector2f arrowPos : arrowPositions) {
        if (hitScan(hit, arrowPos)) {
            return true;
        }
    }

    return false;
}
