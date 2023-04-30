//
// Created by william on 29/04/23.
//

#include "ui/ChatBubble.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SpriteUtil.h"

ChatBubble::ChatBubble(World &world, sf::Color bubbleColor, sf::Sprite* letterSprite) {
    bubbleSprite.setTexture(*world.getAssets().get(GameAssets::CHAT_BUBBLE));
    bubbleSprite.setColor(bubbleColor);
}

void ChatBubble::draw(sf::RenderTarget &target, const sf::RenderStates &states, const sf::Vector2f& friendlyPos) const {
    SpriteUtil::setSpriteSize(bubbleSprite, sf::Vector2f{1.5f, 1.5f});
    SpriteUtil::setSpriteOrigin(bubbleSprite, sf::Vector2f{0.5f, 0.5f});

    bubbleSprite.setPosition(friendlyPos + bubbleRenderOffset);
    target.draw(bubbleSprite);
}
