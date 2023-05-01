//
// Created by Alexander Winter on 2023-04-30.
//

#ifndef LD53_CLIENT_GRASSPATCH_H
#define LD53_CLIENT_GRASSPATCH_H

#include <vector>
#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "grand.h"

enum GrassType {
    GRASS,
    RED_FLOWER,
    YELLOW_FLOWER,
    BLUE_FLOWER
};

class GrassPatch : public Entity, public Tickable {
    float time, timeRate;
    
    mutable sf::Sprite sprite;
    std::vector<sf::Texture*> textures;
public:
    GrassPatch(World& world, sf::Vector2f position, GrassType type);

    virtual void tick(float delta);

    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
    
    virtual const sf::Vector2f& getPosition() const;

    virtual ZOrder getZOrder() const;
};


#endif //LD53_CLIENT_GRASSPATCH_H
