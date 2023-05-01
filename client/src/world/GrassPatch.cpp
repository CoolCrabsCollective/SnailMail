//
// Created by Alexander Winter on 2023-04-30.
//

#include "world/GrassPatch.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SpriteUtil.h"

GrassPatch::GrassPatch(World& world, 
                       sf::Vector2f position,
                       GrassType type)
        : Entity(world), 
            time(world.getRandom().d(5.0f)),
            timeRate(world.getRandom().d()),
            sprite(), 
            textures() {

    if(type == RED_FLOWER) {
        textures.push_back(world.getAssets().get(GameAssets::FLOWER_0));
        textures.push_back(world.getAssets().get(GameAssets::FLOWER_1));
    } else if(type == YELLOW_FLOWER) {
        textures.push_back(world.getAssets().get(GameAssets::YELLOW_FLOWER_0));
        textures.push_back(world.getAssets().get(GameAssets::YELLOW_FLOWER_1));
    } else if(type == BLUE_FLOWER) {
        textures.push_back(world.getAssets().get(GameAssets::BLUE_FLOWER_0));
        textures.push_back(world.getAssets().get(GameAssets::BLUE_FLOWER_1));
    } else {
        textures.push_back(world.getAssets().get(GameAssets::GRASS_0));
        textures.push_back(world.getAssets().get(GameAssets::GRASS_1));
        textures.push_back(world.getAssets().get(GameAssets::GRASS_2));
    }
    sprite.setPosition(position);
}

void GrassPatch::tick(float delta) {
    time += delta * timeRate;
}

void GrassPatch::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setTexture(*textures[(int)round(time / 5.0f) % textures.size()]);
    SpriteUtil::setSpriteSize(sprite, textures.size() > 2 ? sf::Vector2f { 1.0f, 1.0f } : sf::Vector2f { 0.85f, 0.85f });
    SpriteUtil::setSpriteOrigin(sprite, { 0.5f, 0.5f });
    target.draw(sprite);
}

const sf::Vector2f& GrassPatch::getPosition() const {
    return sprite.getPosition();
}

ZOrder GrassPatch::getZOrder() const {
    return Grass_ZOrder;
}
