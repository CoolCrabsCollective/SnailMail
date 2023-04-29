//
// Created by cedric on 4/29/23.
//

#include <algorithm>
#include "world/World.h"
#include <algorithm>

World::World(wiz::AssetLoader &assets) : assets(assets){

}

void World::tick(float delta) {

}

void World::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

}

void World::addEntity(Entity *entity) {
    toAdd.push_back(entity);
}

const std::vector<Entity *> &World::getEntities() const {
    return entities;
}

void World::removeEntities() {
    size_t i = 0;
    while (i < this->entities.size()) {
        Entity* entity = this->entities.at(i);
        if (entity->shouldBeRemoved()) {
            entities.erase(entities.begin() + i);
            removeFromZOrderMap(entity);

            delete entity;
        } else {
            i++;
        }
    }
}

void World::removeFromZOrderMap(Entity *entity) {

    ZOrder key = entity->getZOrder();

    if(!zOrderMap.contains(key))
        throw std::runtime_error("Error entity was not properly in zOrder map (DID YOU UPDATE POSITION OUTSIDE OF TICK?)");

    auto& list = zOrderMap[key];

    auto last = list.end();
    auto pos = std::find(list.begin(), last, entity);

    if(pos == last)
        throw std::runtime_error("Error entity was not properly in zOrder map (DID YOU UPDATE POSITION OUTSIDE OF TICK?)");

    list.erase(pos);

    if(list.empty())
        zOrderMap.erase(key);
}

void World::initZOrderMap() {
    zOrderMap.clear();

    for(Entity* entity : entities) {
        ZOrder key = entity->getZOrder();

        if(!zOrderMap.contains(key))
            zOrderMap[key] = { entity };
        else
            zOrderMap[key].insert(zOrderMap[key].begin(), entity);
    }
}
