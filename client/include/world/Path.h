//
// Created by adrien on 29/04/23.
//

#ifndef LD53_CLIENT_PATH_H
#define LD53_CLIENT_PATH_H

#include "SFML/Graphics.hpp"

#define PATH_TO_NODE_RATIO 1

class Path : public sf::Drawable, public sf::Transformable {
public:
    std::vector<sf::Sprite> sprites;
    sf::Vector2f& p1;
    sf::Vector2f& p2;
    sf::Texture pathTexture;
    sf::Texture cumTexture;

    Path(const sf::Texture& pathTexture, const sf::Texture& cumTexture, sf::Vector2f p1, sf::Vector2f p2, sf::View view);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void setCumminess(float cum_level);
};


#endif //LD53_CLIENT_PATH_H
