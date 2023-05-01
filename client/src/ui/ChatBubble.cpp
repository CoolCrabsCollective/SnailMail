//
// Created by william on 29/04/23.
//

#include "ui/ChatBubble.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SpriteUtil.h"

ChatBubble::ChatBubble(World &world, sf::Color bubbleColor) : world(world) {
    bubbleSprite.setTexture(*world.getAssets().get(GameAssets::CHAT_BUBBLE));
    bubbleSprite.setColor(bubbleColor);

    letterTextures.push_back(world.getAssets().get(GameAssets::LADY_BUG_LETTER));
    letterTextures.push_back(world.getAssets().get(GameAssets::BEE_LETTER));
    letterTextures.push_back(world.getAssets().get(GameAssets::MOUSE_LETTER));
    letterTextures.push_back(world.getAssets().get(GameAssets::FROG_LETTER));

    letterSprite.setTexture(*letterTextures.front());
}

void ChatBubble::draw(sf::RenderTarget &target, const sf::RenderStates &states, const sf::Vector2f& friendlyPos) const {
    if (letterQueue.empty())
        return;

    if(is_mad)
    {
        bubbleSprite.setTexture(*world.getAssets().get(GameAssets::CHAT_BUBBLE_MAD));
    } else {
        bubbleSprite.setTexture(*world.getAssets().get(GameAssets::CHAT_BUBBLE));
    }
    SpriteUtil::setSpriteSize(bubbleSprite, sf::Vector2f{1.5f, 1.5f});
    SpriteUtil::setSpriteOrigin(bubbleSprite, sf::Vector2f{0.5f, 0.5f});

    bubbleSprite.setPosition(friendlyPos + bubbleRenderOffset);

    SpriteUtil::setSpriteSize(letterSprite, sf::Vector2f{.75f, .50f});
    SpriteUtil::setSpriteOrigin(letterSprite, sf::Vector2f{0.5f, 0.5f});

    letterSprite.setPosition(friendlyPos + bubbleRenderOffset + letterRenderOffset);

    if(is_shaking)
    {
        float displacement_x = distribution(generator) * shake_amount;
        float displacement_y = distribution(generator) * shake_amount;
        bubbleSprite.setPosition({bubbleSprite.getPosition().x + displacement_x, bubbleSprite.getPosition().y + displacement_y});
        letterSprite.setPosition({letterSprite.getPosition().x + displacement_x, letterSprite.getPosition().y + displacement_y});
    }
    target.draw(bubbleSprite);

    if(!is_mad)
        target.draw(letterSprite);
}

void ChatBubble::setIsShaking(bool isShaking) {
    is_shaking = isShaking;
}

void ChatBubble::setIsMad(bool isMad) {
    is_mad = isMad;
}

void ChatBubble::addLetter(FriendType letter) {
    letterQueue.push_back(letter);
    letterSprite.setTexture(*letterTextures.at(static_cast<int>(letterQueue.front())));
}

void ChatBubble::popLetter(FriendType letter) {
    auto it = std::find(letterQueue.begin(), letterQueue.end(), letter);

    if (it != letterQueue.end()) {
        letterQueue.erase(it);
    }

    if (!letterQueue.empty())
        letterSprite.setTexture(*letterTextures.at(static_cast<int>(letterQueue.front())));
}
