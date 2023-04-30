//
// Created by cedric on 4/29/23.
//
#include "world/friends/Friend.h"
#include "world/World.h"
#include "SFML/Graphics.hpp"
#include "SpriteUtil.h"

Friend::Friend(World &world, GraphNode *node, const sf::Texture &texture, float frameDelay, float animationDelay) : GraphEntity(world, node),
                    chatBubble(world, sf::Color(255, 255, 255)), frameDelay(frameDelay), animationDelay(animationDelay) {
    sprite.setTexture(texture);
    spriteRect = sf::IntRect({0, 0}, {FRIEND_TEXTURE_SIZE, FRIEND_TEXTURE_SIZE});
    sprite.setTextureRect(spriteRect);
    GRand queue;
    timeTillNextAnim += queue.d();
}

const sf::Vector2f& Friend::getPosition() const {
    return getLocation()->getPosition();
}

sf::Vector2f Friend::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Friend::getZOrder() const {
    return ZOrder::LadyBug_ZOrder;
}

void Friend::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    chatBubble.draw(target, states, getPosition());

    sprite.setPosition(getPosition());
    SpriteUtil::setSpriteSizeUsingTextureRect(sprite, sf::Vector2f{1.95f, 2.});
    SpriteUtil::setSpriteOriginUsingTextureRect(sprite, sf::Vector2f{0.5, 1.});
    target.draw(sprite);
}

void Friend::tick(float delta) {
    if (timeTillNextAnim <= 0) {
        if (spriteRect.left == sprite.getTexture()->getSize().x - FRIEND_TEXTURE_SIZE) {
            spriteRect.left = 0;
            timeTillNextAnim += animationDelay;
        } else {
            spriteRect.left += FRIEND_TEXTURE_SIZE;
        }
        sprite.setTextureRect(spriteRect);
        timeTillNextAnim += frameDelay;
    } else {
        timeTillNextAnim -= delta;
    }
}

ChatBubble& Friend::getChatBubble() {
    return chatBubble;
}

