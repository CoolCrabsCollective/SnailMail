//
// Created by adrien on 29/04/23.
//

#ifndef LD53_CLIENT_PATH_H
#define LD53_CLIENT_PATH_H

#include "SFML/Graphics.hpp"

class Path : public sf::Drawable, public sf::Transformable {
public:
    sf::Sprite pathSprite;

    Path(const sf::Texture& pathTexture);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD53_CLIENT_PATH_H
