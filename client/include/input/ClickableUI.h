//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_CLICKABLEUI_H
#define LD53_CLIENT_CLICKABLEUI_H

#include "SFML/System/Vector2.hpp"

class ClickableUI {
private:
    sf::Vector2f boundingBoxBL;
    sf::Vector2f boundingBoxTR;

protected:
    bool clickable = true;

public:
    ClickableUI(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR);

    bool hitScan(const sf::Vector2f& hit);

    virtual void hitAction(bool& hit) = 0;
};

#endif //LD53_CLIENT_CLICKABLEUI_H