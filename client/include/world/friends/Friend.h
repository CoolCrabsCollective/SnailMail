//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_FRIEND_H
#define LD53_CLIENT_FRIEND_H

#include "SFML/Graphics/Sprite.hpp"
#include "world/GraphEntity.h"
#include "world/World.h"
#include "ui/ChatBubble.h"
#include "world/Tickable.h"

#define FRIEND_TEXTURE_SIZE 32

class Friend : public GraphEntity, public Tickable {
    mutable sf::Sprite sprite;
    sf::IntRect spriteRect;

    ChatBubble chatBubble;

    float timeTillNextAnim = 0;
    const float frameDelay;
    const float animationDelay;
    bool isMad = false;

public:
    Friend(World& world, GraphNode* node, const sf::Texture &texture, float frameDelay, float animationDelay);

    const sf::Vector2f& getPosition() const;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void tick(float delta) override;
    ChatBubble& getChatBubble();

    virtual const FriendType getFriendType() const = 0;
};

#endif //LD53_CLIENT_FRIEND_H
