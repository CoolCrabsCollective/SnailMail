//
// Created by adrien on 29/04/23.
//

#ifndef LD53_CLIENT_PATH_H
#define LD53_CLIENT_PATH_H

#include "SFML/Graphics.hpp"
#include "GraphNode.h"
#include "WIZ/asset/AssetLoader.h"

struct Slime {
    sf::Color color;
    float start, end;
    bool forward;
};

enum PathType {
    DIRT,
    ROCK
};

class Path : public sf::Drawable, public sf::Transformable {
    mutable sf::Sprite sprite;
    mutable sf::Sprite slimeSprite;
    GraphNode* node1, *node2;

    std::vector<Slime> slimes;
public:
    Path(wiz::AssetLoader& assets,
         GraphNode* node1,
         GraphNode* node2,
         PathType pathType);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void addSlime(GraphNode* enterNode,
                  float position,
                  float previous,
                  sf::Color color);

    bool isBlocked(GraphNode* enterNode, sf::Color color) const;
};


#endif //LD53_CLIENT_PATH_H
