//
// Created by william on 29/04/23.
//

#include <iostream>
#include "ui/PathSelectionArrowUI.h"
#include "SpriteUtil.h"
#include "GameAssets.h"
#include "world/World.h"

PathSelectionArrowUI::PathSelectionArrowUI(World &world, sf::Color color)
    : world(world),
        boundingBoxBL({-0.5f, -0.5f}),
        boundingBoxTR({0.5f, 0.5f}),
        currentArrowNode(nullptr) {
    sprite.setTexture(*world.getAssets().get(GameAssets::PATH_SEL_ARROW));
    sprite.setColor(color);
}

void PathSelectionArrowUI::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});

    for(auto& arrow : arrows) {
        SpriteUtil::setSpriteSize(sprite, arrow.second.scale * sf::Vector2f{1.0f, 1.0f});
        sprite.setPosition(arrow.second.position);
        sprite.setRotation(sf::radians(arrow.second.angle));
        SpriteUtil::setSpriteOpacity(sprite, arrow.second.alpha);
        target.draw(sprite);
    }
}

void PathSelectionArrowUI::tick(float delta, bool moving, GraphNode* currentNode, sf::Color snail_color) {
    if(currentArrowNode != currentNode) {
        arrows.clear();
        currentArrowNode = currentNode;
    }

    std::unordered_set<GraphNode*> found;

    if(!moving)
        for(GraphNode* neighbor : currentNode->getNeighbors()) {
            Path& path = world.getGraph()->getPath(currentNode, neighbor);
            if(path.isBlocked(currentNode, snail_color))
                continue;

            bool neighbor_blocking = false;
            for(Snail* snail : world.getSnails())
            {
                if(neighbor == snail->getLocation() && snail->isMoving() && snail->getDestination() == currentNode)
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

            sf::Vector2f position = {cosf(angle) * spawnRadius + currentNode->getPosition().x,
                                     sinf(angle) * spawnRadius + currentNode->getPosition().y};

            angle += M_PI / 2;

            if(arrows.contains(neighbor)) {
                arrows[neighbor].position = position;
                arrows[neighbor].angle = angle;

                if(arrows[neighbor].hovered) {

                    arrows[neighbor].alpha += delta * 10.0f;
                    if(arrows[neighbor].alpha > 1.0f)
                        arrows[neighbor].alpha = 1.0f;

                    arrows[neighbor].scale += delta * 2.0f;
                    if(arrows[neighbor].scale > 1.2f)
                        arrows[neighbor].scale = 1.2f;
                } else {

                    if(arrows[neighbor].alpha < 1.0f)
                        arrows[neighbor].alpha += delta * 10.0f;
                    else
                        arrows[neighbor].alpha -= delta * 2.0f;

                    if(arrows[neighbor].alpha > 1.0f)
                        arrows[neighbor].alpha = 1.0f;

                    arrows[neighbor].scale -= delta * 1.0f;
                    if(arrows[neighbor].scale < 1.0f)
                        arrows[neighbor].scale = 1.0f;
                }
            } else {
                arrows.emplace(neighbor, SelectionArrow { position, angle, 1.0f, false, 0.0f });
            }

            found.insert(neighbor);
        }

    for(auto it = arrows.begin(); it != arrows.end();)
    {
        if(!found.contains(it->first)) {
            it->second.alpha -= delta * 4.0f;
            it->second.scale += delta * 0.5f;
            if(it->second.alpha <= 0.0f)
                it = arrows.erase(it);
            else
                ++it;
        }
        else
            ++it;
    }
}

GraphNode* PathSelectionArrowUI::hitScanAll(const sf::Vector2f& hit) {
    for (auto& arrow : arrows) {
        if (hitScan(hit, arrow.second.position)) {
            return arrow.first;
        }
    }

    return nullptr;
}

bool PathSelectionArrowUI::hover(const sf::Vector2f &position) {
    for(auto& arrow : arrows)
        arrow.second.hovered = false;

    for (auto& arrow : arrows) {
        if (hitScan(position, arrow.second.position)) {
            arrow.second.hovered = true;
            return true;
        }
    }
    return false;
}

bool PathSelectionArrowUI::hitScan(const sf::Vector2f& hit, const sf::Vector2f& entityPos) {
    sf::Vector2f boundingBoxBottomLeft = entityPos + boundingBoxBL;
    sf::Vector2f boundingBoxTopRight = entityPos + boundingBoxTR;

    bool xBound = hit.x >= boundingBoxBottomLeft.x && hit.x <= boundingBoxTopRight.x;
    bool yBound = hit.y >= boundingBoxBottomLeft.y && hit.y <= boundingBoxTopRight.y;

    return xBound && yBound;
}
