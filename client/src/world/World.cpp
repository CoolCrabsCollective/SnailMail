//
// Created by cedric on 4/29/23.
//

#include "world/World.h"

World::World(wiz::AssetLoader &assets) : assets(assets){

}

void World::tick(float delta) {

}

void World::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

}

wiz::AssetLoader& World::getAssets() const {
    return assets;
}
