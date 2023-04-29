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

class PathSelArrow: public Clickable {
    mutable sf::Sprite sprite;

    std::vector<sf::Vector2f> arrowPositions;
    std::vector<float> arrowAngles;

    float spawnRadius = 2.0f;

public:
    PathSelArrow(World &world);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;

    void updatePositions(GraphNode* currentNode);

    bool hitScanAll(const sf::Vector2f& hit);

    ~PathSelArrow() = default;
};

#endif //LD53_CLIENT_PATHSELARROW_H
