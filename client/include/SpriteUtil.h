//
// Created by Alexander Winter on 2023-01-08.
//

#ifndef LD52_CLIENT_SPRITEUTIL_H
#define LD52_CLIENT_SPRITEUTIL_H

#include <algorithm>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

namespace SpriteUtil {
    inline void setSpriteSize(sf::Sprite& sprite, sf::Vector2f worldUnitSize) {
        sprite.setScale({ worldUnitSize.x / static_cast<float>(sprite.getTexture()->getSize().x),
                          worldUnitSize.y / static_cast<float>(sprite.getTexture()->getSize().y) });
    }

    inline void setSpriteOrigin(sf::Sprite& sprite, sf::Vector2f localOrigin) {
        sprite.setOrigin({
                 localOrigin.x * static_cast<float>(sprite.getTexture()->getSize().x),
                 localOrigin.y * static_cast<float>(sprite.getTexture()->getSize().y)
         });
    }

    inline void setSpriteOpacity(sf::Sprite& sprite, float opacity) {
        sprite.setColor(sf::Color {
                sprite.getColor().r,
                sprite.getColor().g,
                sprite.getColor().b,
                (sf::Uint8)round(std::clamp(opacity, 0.0f, 1.0f) * 255)
        });
    }
}

#endif //LD52_CLIENT_SPRITEUTIL_H