//
// Created by Alexander Winter on 2023-04-30.
//

#include "world/GrassPatch.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SpriteUtil.h"

GrassPatch::GrassPatch(World& world, 
                       sf::Vector2f position)
        : Entity(world), 
            time(world.getRandom().d(5.0f)),
            timeRate(world.getRandom().d()),
            sprite(), 
            textures() {
    textures.push_back(world.getAssets().get(GameAssets::GRASS_0));
    textures.push_back(world.getAssets().get(GameAssets::GRASS_1));
    textures.push_back(world.getAssets().get(GameAssets::GRASS_2));
    sprite.setPosition(position);
}

void GrassPatch::tick(float delta) {
    time += delta * timeRate;
}

void GrassPatch::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setTexture(*textures[(int)round(time / 5.0f) % textures.size()]);
    SpriteUtil::setSpriteSize(sprite, { 1.0f, 1.0f });
    SpriteUtil::setSpriteOrigin(sprite, { 0.5f, 0.5f });
    target.draw(sprite);
}

const sf::Vector2f& GrassPatch::getPosition() const {
    return sprite.getPosition();
}

ZOrder GrassPatch::getZOrder() const {
    return Grass_ZOrder;
}
