//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_PATHSELARROW_H
#define LD53_CLIENT_PATHSELARROW_H

#include "world/Tickable.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "input/Clickable.h"
#include "world/GraphNode.h"

class World;

class PathSelArrow {
    mutable sf::Sprite sprite;

    World& world;

    std::vector<sf::Vector2f> arrowPositions;
    std::vector<float> arrowAngles;
    std::vector<GraphNode*> graphNodes;

    float spawnRadius = 2.0f;

    sf::Vector2f boundingBoxBL;
    sf::Vector2f boundingBoxTR;

public:
    PathSelArrow(World &world, sf::Color color);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;

    void updatePositions(GraphNode* currentNode, sf::Color snail_color);

    GraphNode* hitScanAll(const sf::Vector2f& hit);

    bool hitScan(const sf::Vector2f& hit, const sf::Vector2f& entityPos);

    ~PathSelArrow() = default;
};

#endif //LD53_CLIENT_PATHSELARROW_H
