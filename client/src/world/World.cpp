//
// Created by cedric on 4/29/23.
//

#include "world/World.h"
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "world/Graph.h"

World::World(wiz::AssetLoader &assets)
    : assets(assets),
      view({ 16.0f, 9.0f }, { 32.0f, 18.0f }) {

    addEntity(new Graph(*this));
}

void World::tick(float delta) {
    for(Entity* entity : entities) {
        if(Tickable* tickable = dynamic_cast<Tickable*>(entity)) {
            tickable->tick(delta);
        }
    }
    removeTrashToBeDeleted();
    for(Entity* entity : toAdd) {
        entities.push_back(entity);

        ZOrder key = entity->getZOrder();

        if(!zOrderMap.contains(key))
            zOrderMap[key] = { entity };
        else
            zOrderMap[key].insert(zOrderMap[key].begin(), entity);
    }
    toAdd.clear();
}

void World::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

    target.setView(view);
    for(int i = 0; i < ZOrder::ENUM_LENGTH; i++) {
        for(Entity* entity: zOrderMap[static_cast<ZOrder>(i)]) {
            target.draw(*entity);
        }
    }
}

void World::addEntity(Entity* entity) {
    toAdd.push_back(entity);

    if(!zOrderMap.contains(entity->getZOrder()))
        zOrderMap[entity->getZOrder()] = {entity};
    else
        zOrderMap[entity->getZOrder()].insert(zOrderMap[entity->getZOrder()].begin(), entity);
}

const std::vector<Entity *> &World::getEntities() const {
    return entities;
}

void World::removeTrashToBeDeleted() {
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

wiz::AssetLoader& World::getAssets() const {
    return assets;

}

const sf::View& World::getView() const {
    return view;
}
