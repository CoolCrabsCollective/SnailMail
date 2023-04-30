//
// Created by william on 29/04/23.
//

#include "ui/ChatBubble.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SpriteUtil.h"

ChatBubble::ChatBubble(World &world, sf::Color bubbleColor) {
    bubbleSprite.setTexture(*world.getAssets().get(GameAssets::CHAT_BUBBLE));
    bubbleSprite.setColor(bubbleColor);

    const std::vector<sf::Texture> letterTextures = {
            *world.getAssets().get(GameAssets::LADY_BUG_LETTER),
            *world.getAssets().get(GameAssets::BEE_LETTER),
            *world.getAssets().get(GameAssets::MOUSE_LETTER),
            *world.getAssets().get(GameAssets::FROG_LETTER),
    };

    letterSprite.setTexture(letterTextures.at(0));
}

void ChatBubble::draw(sf::RenderTarget &target, const sf::RenderStates &states, const sf::Vector2f& friendlyPos) const {
    if (letterQueue.empty())
        return;

    SpriteUtil::setSpriteSize(bubbleSprite, sf::Vector2f{1.5f, 1.5f});
    SpriteUtil::setSpriteOrigin(bubbleSprite, sf::Vector2f{0.5f, 0.5f});

    bubbleSprite.setPosition(friendlyPos + bubbleRenderOffset);
    target.draw(bubbleSprite);

    SpriteUtil::setSpriteSize(letterSprite, sf::Vector2f{.75f, .50f});
    SpriteUtil::setSpriteOrigin(letterSprite, sf::Vector2f{0.5f, 0.5f});

    letterSprite.setPosition(friendlyPos + bubbleRenderOffset + letterRenderOffset);
    target.draw(letterSprite);
}

void ChatBubble::addLetter(FriendType letter) {
    letterQueue.push(letter);
}

void ChatBubble::popLetter() {
    letterQueue.pop();
    letterSprite.setTexture(letterTextures.at(letterQueue.front()));
}
