//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_CHATBUBBLE_H
#define LD53_CLIENT_CHATBUBBLE_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"

class World;

class ChatBubble {
    mutable sf::Sprite bubbleSprite;
    mutable sf::Sprite* letterSprite;

    const sf::Vector2f bubbleRenderOffset = {1.7f, -1.7f};
    const sf::Vector2f letterRenderOffset = {2.f, 2.f};

public:
    ChatBubble(World &world, sf::Color bubbleColor, sf::Sprite* letterSprite);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states, const sf::Vector2f& friendlyPos) const;

    ~ChatBubble() = default;
};

#endif //LD53_CLIENT_CHATBUBBLE_H
