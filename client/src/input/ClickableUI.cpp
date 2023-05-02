//
// Created by william on 29/04/23.
//

#include "input/ClickableUI.h"

ClickableUI::ClickableUI(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR): boundingBoxBL(boundingBoxBL),
                                                                                  boundingBoxTR(boundingBoxTR),
                                                                                  clickSound() {
}

bool ClickableUI::hit(const sf::Vector2f& hitPos) {
    if (!clickable)
        return false;

    bool xBound = hitPos.x >= boundingBoxBL.x && hitPos.x <= boundingBoxTR.x;
    bool yBound = hitPos.y >= boundingBoxBL.y && hitPos.y <= boundingBoxTR.y;

    return xBound && yBound;
}

bool ClickableUI::hitScan(const sf::Vector2f& hitPos) {
    bool isHit = hit(hitPos);

    if (isHit)
        clickSound.play();

    hitAction(isHit);
    return isHit;
}

bool ClickableUI::hoverScan(const sf::Vector2f& hitPos) {
    bool isHit = hit(hitPos);
    hoverAction(isHit);
    return isHit;
}

void ClickableUI::setClickable(bool clickable) {
    ClickableUI::clickable = clickable;
}
