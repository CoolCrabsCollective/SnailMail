//
// Created by adrien on 29/04/23.
//

#include "world/Path.h"

Path::Path(const sf::Texture& pathTexture) {
   pathSprite = sf::Sprite(pathTexture);
}

void Path::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(pathSprite);
}
