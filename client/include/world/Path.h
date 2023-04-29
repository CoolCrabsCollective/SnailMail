//
// Created by adrien on 29/04/23.
//

#ifndef LD53_CLIENT_PATH_H
#define LD53_CLIENT_PATH_H

#include "SFML/Graphics.hpp"

#define PATH_TEXTURE_SIZE 32

class Path : public sf::Drawable, public sf::Transformable {
public:
    std::vector<sf::Sprite> sprites;
    sf::Vector2f& p1;
    sf::Vector2f& p2;

    Path(const sf::Texture& pathTexture, sf::Vector2f p1, sf::Vector2f p2);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD53_CLIENT_PATH_H
