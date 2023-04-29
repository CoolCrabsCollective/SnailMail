//
// Created by william on 29/04/23.
//

#include "input/Clickable.h"

Clickable::Clickable(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR): boundingBoxBL(boundingBoxBL),
                                                                                boundingBoxTR(boundingBoxTR) {}

bool Clickable::hitScan(const sf::Vector2f& hit, const sf::Vector2f& entityPos) {
    sf::Vector2f boundingBoxBottomLeft = entityPos + boundingBoxBL;
    sf::Vector2f boundingBoxTopRight = entityPos + boundingBoxTR;

    bool xBound = hit.x >= boundingBoxBottomLeft.x && hit.x <= boundingBoxTopRight.x;
    bool yBound = hit.y >= boundingBoxBottomLeft.y && hit.y <= boundingBoxTopRight.y;

    return xBound && yBound;
}