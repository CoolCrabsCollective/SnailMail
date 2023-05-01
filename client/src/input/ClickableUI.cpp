//
// Created by william on 29/04/23.
//

#include "input/ClickableUI.h"

ClickableUI::ClickableUI(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR): boundingBoxBL(boundingBoxBL),
                                                                                  boundingBoxTR(boundingBoxTR) {}

bool ClickableUI::hitScan(const sf::Vector2f& hit) {
    if (!clickable)
        return false;

    bool xBound = hit.x >= boundingBoxBL.x && hit.x <= boundingBoxTR.x;
    bool yBound = hit.y >= boundingBoxBL.y && hit.y <= boundingBoxTR.y;

    bool isHit = xBound && yBound;
    hitAction(isHit);
    return isHit;
}

void ClickableUI::setClickable(bool clickable) {
    ClickableUI::clickable = clickable;
}
