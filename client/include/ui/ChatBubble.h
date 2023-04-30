//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_CHATBUBBLE_H
#define LD53_CLIENT_CHATBUBBLE_H

#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "world/level/Level.h"
#include <random>

class World;

class ChatBubble {
    mutable sf::Sprite bubbleSprite;
    mutable sf::Sprite letterSprite;

    const sf::Vector2f bubbleRenderOffset = {1.7f, -1.7f};
    const sf::Vector2f letterRenderOffset = {0.f, -.25f};

    std::vector<sf::Texture*> letterTextures;

    std::vector<FriendType> letterQueue;
    World& world;


    float shake_amount = 0.05f;
    bool is_mad = false;
    bool is_shaking = false;
    mutable std::default_random_engine generator;
    mutable std::uniform_real_distribution<float> distribution{-1.0f, 1.0f};

public:
    ChatBubble(World &world, sf::Color bubbleColor);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states, const sf::Vector2f& friendlyPos) const;

    void addLetter(FriendType letter);

    void popLetter(FriendType letter);

    ~ChatBubble() = default;

    void setIsShaking(bool isShaking);

    void setIsMad(bool isMad);
};

#endif //LD53_CLIENT_CHATBUBBLE_H
