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


const sf::Color World::snail_colors[] = {
        sf::Color(232, 59, 59),
        sf::Color(77, 155, 230),
        sf::Color(251, 255, 134)
};

World::World(wiz::AssetLoader &assets)
    : assets(assets),
      view({ 16.0f, 9.0f }, { 32.0f, 18.0f }) {

    graph = new Graph(*this);
    addEntity(graph);

    generateLevel(SnailLevel::getLevel(1));

    Snail* snail = new Snail(*this, getGraph()->getNodes()[0], snail_colors[0]);
    snails.push_back(snail);

    entitySelection = new EntitySelection(*this);

    background.setTexture(*assets.get(GameAssets::BACKGROUND));
    background.setPosition(view.getCenter());
    SpriteUtil::setSpriteSize(background, view.getSize());
    SpriteUtil::setSpriteOrigin(background, {0.5f, 0.5f});
}

void World::generateLevel(SnailLevel level) {

    // TODO CLEAR PREVIOUS LEVEL

    currentLevel = level;
    graph->generateLevel(level);

    GRand random;

    if(level.seeded)
        random.seed(level.seed);

    if(level.offices.size() + level.friends.size() >= graph->getNodes().size())
        throw std::runtime_error("Too many offices and friends for graph size");

    std::unordered_set<int> used_positions;

    for(LevelPostOffice& postOffice : level.offices) {
        if(postOffice.randomPosition)
            continue;

        if(postOffice.hardcodedVertex >= graph->getNodes().size() || postOffice.hardcodedVertex < 0) {
            std::cout << "Error: Invalid hardcoded index for post office (out of bounds)" << std::endl;
            postOffice.randomPosition = true;
            continue;
        }

        addEntity(new PostOffice(*this, graph->getNodes()[postOffice.hardcodedVertex]));
        used_positions.insert(postOffice.hardcodedVertex);
    }

    for(LevelFriend lfriend : level.friends) {
        if(lfriend.randomPosition)
            continue;

        if(lfriend.hardcodedVertex >= graph->getNodes().size()
        || lfriend.hardcodedVertex < 0
        || used_positions.contains(lfriend.hardcodedVertex)) {
            std::cout << "Error: Invalid hardcoded index for friend" << std::endl;
            lfriend.randomPosition = true;
            continue;
        }

        switch(lfriend.type) {
            case LADYBUG:
                addEntity(new LadyBug(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
            case BEE:
                addEntity(new Bee(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
            case MOUSE:
                break;
            case FROG:
                break;
        }
        used_positions.insert(lfriend.hardcodedVertex);
    }

    for(LevelPostOffice postOffice : level.offices) {
        if(!postOffice.randomPosition)
            continue;

        int randVertex = random.i(graph->getNodes().size());

        while(used_positions.contains(randVertex))
            randVertex = random.i(graph->getNodes().size());

        addEntity(new PostOffice(*this, graph->getNodes()[randVertex]));
        used_positions.insert(randVertex);
    }

    for(LevelFriend lfriend : level.friends) {
        if(!lfriend.randomPosition)
            continue;

        int randVertex = random.i(graph->getNodes().size());

        while(used_positions.contains(randVertex))
            randVertex = random.i(graph->getNodes().size());

        switch(lfriend.type) {
            case LADYBUG:
                addEntity(new LadyBug(*this, graph->getNodes()[randVertex]));
                break;
            case BEE:
                addEntity(new Bee(*this, graph->getNodes()[randVertex]));
                break;
            case MOUSE:
                break;
            case FROG:
                break;
        }
        used_positions.insert(randVertex);
    }
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

const std::vector<Snail *> &World::getSnails() const {
    return snails;
}