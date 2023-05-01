//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_POSTOFFICE_H
#define LD53_CLIENT_POSTOFFICE_H


#include "GraphEntity.h"
#include "SFML/Graphics/Sprite.hpp"

class PostOffice : public GraphEntity {
    mutable sf::Sprite sprite;
public:
    PostOffice(World &world, GraphNode *node);

    const sf::Vector2f& getPosition() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
};


#endif //LD53_CLIENT_POSTOFFICE_H
