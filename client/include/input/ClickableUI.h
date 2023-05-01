//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_CLICKABLEUI_H
#define LD53_CLIENT_CLICKABLEUI_H

#include "SFML/System/Vector2.hpp"

class ClickableUI {
protected:
    sf::Vector2f boundingBoxBL;
    sf::Vector2f boundingBoxTR;

    bool clickable = true;

public:
    ClickableUI(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR);

    virtual bool hit(const sf::Vector2f& hitPos);

    virtual bool hitScan(const sf::Vector2f& hitPos);

    virtual bool hoverScan(const sf::Vector2f& hitPos);

    virtual void hitAction(bool& hit) = 0;

    virtual void hoverAction(bool& hit) = 0;

    void setClickable(bool clickable);
};

#endif //LD53_CLIENT_CLICKABLEUI_H
