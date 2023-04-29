//
// Created by cedric on 4/29/23.
//

#include "world/World.h"
#include <algorithm>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "world/Graph.h"
#include "world/friends/LadyBug.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "world/friends/Bee.h"
#include "world/PostOffice.h"


World::World(wiz::AssetLoader &assets)
    : assets(assets),
      view({ 16.0f, 9.0f }, { 32.0f, 18.0f }) {

    graph = new Graph(*this);
    addEntity(graph);
    GraphNode* startNode = graph->getNodes()[0];

    sf::Color snail_color_red = sf::Color(232, 59, 59);
    sf::Color snail_color_blue = sf::Color(77, 155, 230);
    sf::Color snail_color_yellow = sf::Color(251, 255, 134);

    snail = new Snail(*this, startNode, snail_color_blue);
    addEntity(snail);

    PostOffice* postOffice = new PostOffice(*this, startNode);
    addEntity(postOffice);

    LadyBug* ladyBug = new LadyBug(*this, graph->getNodes()[graph->getNodes().size() - 1]);
    addEntity(ladyBug);


    Bee* bee = new Bee(*this, graph->getNodes()[graph->getNodes().size() - 2]);
    addEntity(bee);


    entitySelection = new EntitySelection(*this);

    background.setTexture(*assets.get(GameAssets::BACKGROUND));
    background.setPosition(view.getCenter());
    SpriteUtil::setSpriteSize(background, view.getSize());
    SpriteUtil::setSpriteOrigin(background, {0.5f, 0.5f});
}

void World::tick(float delta) {
    handleSelected();

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
    target.draw(background);

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

void World::handleSelected() {
    GraphNode* selected = entitySelection->getSelected();
    if (selected) {
        snail->moveLocation(selected);
        entitySelection->setSelected(nullptr);
    }
}

wiz::AssetLoader& World::getAssets() const {
    return assets;

}

const sf::View& World::getView() const {
    return view;
}

const std::map<ZOrder, std::vector<Entity *>> &World::getZOrderMap() const {
    return zOrderMap;
}

Graph* World::getGraph() const {
    return graph;
}

EntitySelection *World::getEntitySelection() const {
    return entitySelection;
}
