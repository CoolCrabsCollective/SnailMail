//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_CLICKABLE_H
#define LD53_CLIENT_CLICKABLE_H

#include "SFML/System/Vector2.hpp"

class Clickable {
private:
    sf::Vector2f boundingBoxBL;
    sf::Vector2f boundingBoxTR;

public:
    Clickable(sf::Vector2f boundingBoxBL, sf::Vector2f boundingBoxTR);

    bool hitScan(const sf::Vector2f& hit, const sf::Vector2f& entityPos);
};

#endif //LD53_CLIENT_CLICKABLE_H
