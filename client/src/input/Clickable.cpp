//
// Created by william on 29/04/23.
//

#include "input/Clickable.h"

Clickable::Clickable(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR, sf::Vector2f entityPos,
                     bool* triggerFlag, bool* activeFlag): boundingBoxBL(boundingBoxBL),
                                                                                boundingBoxTR(boundingBoxTR),
                                                                                entityPos(entityPos),
                                                                                triggerFlag(triggerFlag),
                                                                                activeFlag(activeFlag) {}

bool Clickable::hitScan(const sf::Vector2f& hit) {
    hitScan(hit, entityPos);
}

bool Clickable::hitScan(const sf::Vector2f& hit, const sf::Vector2f& entityPos) {
    if (activeFlag && !*activeFlag)
        return false;

    sf::Vector2f boundingBoxBottomLeft = entityPos + boundingBoxBL;
    sf::Vector2f boundingBoxTopRight = entityPos + boundingBoxTR;

    bool xBound = hit.x >= boundingBoxBottomLeft.x && hit.x <= boundingBoxTopRight.x;
    bool yBound = hit.y >= boundingBoxBottomLeft.y && hit.y <= boundingBoxTopRight.y;

    if (triggerFlag)
        *triggerFlag = !(xBound && yBound);

    return xBound && yBound;
}