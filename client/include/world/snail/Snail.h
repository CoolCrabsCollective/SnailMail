//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_SNAIL_H
#define LD53_CLIENT_SNAIL_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"

class Snail : public GraphEntity {
    mutable sf::Sprite sprite;
    bool isMoving = false;
    float movingProgress = 0.f;
    float progressRate = .1f;

    sf::Vector2f locDiff;

    sf::Vector2f actualPosition;

public:
    Snail(World& world, GraphNode* node);

    const sf::Vector2f &getLocation() override;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void tick(float delta);

    void moveLocation(GraphNode* targetLocation);

    void tickMovement(float delta);
};

#endif //LD53_CLIENT_SNAIL_H
