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
#include "world/level/Mission.h"
#include "world/friends/Mouse.h"
#include "world/friends/Frog.h"
#include "MailScreen.h"
#include "world/level/Delivery.h"
#include "MathUtil.h"
#include "world/GrassPatch.h"
#include "world/friends/Ant.h"

const sf::Color World::snail_colors[] = {
        Snail::SNAIL_COLOR_BLUE,
        Snail::SNAIL_COLOR_YELLOW,
        Snail::SNAIL_COLOR_RED,
        Snail::SNAIL_COLOR_GREEN
};

World::World(wiz::AssetLoader &assets, MailScreen& screen)
    : assets(assets),
      screen(screen),
      zOrderMap(),
      view({ 16.0f, 9.0f }, { 32.0f, 18.0f }),
      successSound(),
      failureSound() {

    graph = new Graph(*this);
    addEntity(graph);

    generateLevel(Level::getLevel(currentLevelNumber), currentLevelNumber);

    background.setTexture(*assets.get(GameAssets::WHITE_PIXEL));
    background.setColor({ 25, 148, 25, 255 });
    background.setPosition(view.getCenter());
    SpriteUtil::setSpriteSize(background, view.getSize());
    SpriteUtil::setSpriteOrigin(background, {0.5f, 0.5f});

    successSound.setBuffer(*assets.get(GameAssets::SUCCESS));
    failureSound.setBuffer(*assets.get(GameAssets::FAILURE));
}

Snail* World::spawnSnail(GraphNode* node, int snailId, float speed) {
    Snail* snail = new Snail(*this, node, snail_colors[snailId]);
    snails.push_back(snail);
    snails.back()->setProgressRate(speed);
    addEntity(snail);
    return snail;
}

void World::generateLevel(Level level, int levelNum) {

    setPaused(false);
    hasSnailMadeFirstMove = false;
    stopAllMusic();

    const wiz::MusicAsset& song = getSong(levelNum);
    getAssets().get(song)->setLoop(true);
    getAssets().get(song)->play();

    for(Entity* entity : entities)
        delete entity;
    entities.clear();
    snails.clear();
    missions.clear();
    toAdd.clear();
    zOrderMap.clear();
    postOffices.clear();
    friends.clear();
    timeSpent = 0.0f;
    graph = new Graph(*this);
    addEntity(graph);

    currentLevel = level;
    graph->generateLevel(level);

    std::vector<GrassPatch*> patches;

    int it = 0;
    do {
        it++;
        float x = static_cast<float>(random.d() * getView().getSize().x);
        float y = static_cast<float>(random.d() * getView().getSize().y);

        bool cancel = false;

        for(GraphNode* node : graph->getNodes()) {
            if((node->getPosition() - sf::Vector2f {x, y}).lengthSq() < MathUtil::pow2(Graph::MIN_NODE_DISTANCE / 2.0f)) {
                cancel = true;
                break;
            }
        }

        if(cancel)
            continue;

        for(GrassPatch* patch : patches) {
            if((patch->getPosition() - sf::Vector2f {x, y}).lengthSq() < MathUtil::pow2(Graph::MIN_NODE_DISTANCE / 2.0f)) {
                cancel = true;
                break;
            }
        }

        if(cancel)
            continue;


        for(auto& path : graph->getPaths()) {
            if(MathUtil::pointSegmentDistanceSquared({ x, y }, path.first.first->getPosition(), path.first.second->getPosition()) < MathUtil::pow2(Graph::MIN_NODE_DISTANCE / 4.0f)) {
                cancel = true;
                break;
            }
        }

        if(cancel)
            continue;

        GrassType type;

        if(random.d() > 0.95f) {
            type = GrassType::RED_FLOWER;
        } else if(random.d() > 0.90f) {
            type = GrassType::YELLOW_FLOWER;
        } else if(random.d() > 0.85f) {
            type = GrassType::BLUE_FLOWER;
        } else {
            type = GrassType::GRASS;
        }

        patches.push_back(new GrassPatch(*this, { x, y }, type));

    } while(it < 500000);

    for(GrassPatch* patch : patches)
        addEntity(patch);

    if(level.seeded)
        random.seed(level.seed);

    if(level.offices.size() + level.friends.size() > graph->getNodes().size())
        throw std::runtime_error("Too many offices and friends for graph size");

    std::unordered_set<int> used_positions;

    int id = -1;
    for(LevelPostOffice& postOffice : level.offices) {
        id++;
        if(postOffice.randomPosition)
            continue;

        if(postOffice.hardcodedVertex >= graph->getNodes().size() || postOffice.hardcodedVertex < 0) {
            std::cout << "Error: Invalid hardcoded index for post office (out of bounds)" << std::endl;
            postOffice.randomPosition = true;
            continue;
        }

        PostOffice* po = new PostOffice(*this, graph->getNodes()[postOffice.hardcodedVertex]);
        addEntity(po);
        postOffices.emplace(id, po);
        used_positions.insert(postOffice.hardcodedVertex);
    }

    id = -1;
    for(LevelFriend lfriend : level.friends) {
        id++;
        if(lfriend.randomPosition)
            continue;

        if(lfriend.hardcodedVertex >= graph->getNodes().size()
        || lfriend.hardcodedVertex < 0
        || used_positions.contains(lfriend.hardcodedVertex)) {
            std::cout << "Error: Invalid hardcoded index for friend" << std::endl;
            lfriend.randomPosition = true;
            continue;
        }

        Friend* spawned = nullptr;

        switch(lfriend.type) {
            case LADYBUG:
                addEntity(spawned = new LadyBug(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
            case BEE:
                addEntity(spawned = new Bee(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
            case MOUSE:
                addEntity(spawned = new Mouse(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
            case FROG:
                addEntity(spawned = new Frog(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
            case ANT:
                addEntity(spawned = new Ant(*this, graph->getNodes()[lfriend.hardcodedVertex]));
                break;
        }
        friends.emplace(id, spawned);
        used_positions.insert(lfriend.hardcodedVertex);
    }

    id = -1;
    for(LevelPostOffice postOffice : level.offices) {
        id++;
        if(!postOffice.randomPosition)
            continue;

        int randVertex = random.i(graph->getNodes().size());

        while(used_positions.contains(randVertex))
            randVertex = random.i(graph->getNodes().size());

        PostOffice* po = new PostOffice(*this, graph->getNodes()[randVertex]);
        addEntity(po);
        postOffices.emplace(id, po);
        used_positions.insert(randVertex);
    }

    id = -1;
    for(LevelFriend lfriend : level.friends) {
        id++;
        if(!lfriend.randomPosition)
            continue;

        int randVertex = random.i(graph->getNodes().size());

        while(used_positions.contains(randVertex))
            randVertex = random.i(graph->getNodes().size());

        Friend* spawned = nullptr;

        switch(lfriend.type) {
            case LADYBUG:
                addEntity(spawned = new LadyBug(*this, graph->getNodes()[randVertex]));
                break;
            case BEE:
                addEntity(spawned = new Bee(*this, graph->getNodes()[randVertex]));
                break;
            case MOUSE:
                addEntity(spawned = new Mouse(*this, graph->getNodes()[randVertex]));
                break;
            case FROG:
                addEntity(spawned = new Frog(*this, graph->getNodes()[randVertex]));
                break;
        }
        friends.emplace(id, spawned);
        used_positions.insert(randVertex);
    }

    for(LevelDeliveryMission mission : level.missions) {
        missions.push_back(new Mission(*this, mission));
    }
}

void World::tick(float delta) {
    if (paused) {
        return;
    }

    if(!screen.getCompleteMenu().isVisible())
        timeSpent += delta;

    for(Entity* entity : entities) {
        if(Tickable* tickable = dynamic_cast<Tickable*>(entity)) {
            tickable->tick(delta);
        }
    }
    bool allMissionsCompleted = true;

    for(Mission* mission : missions) {
        mission->tick(delta);
        if(!mission->isCompleted())
            allMissionsCompleted = false;
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

    if(!screen.getCompleteMenu().isVisible() && allMissionsCompleted) {
        int deliveriesCompleted = 0;
        int deliveriesMissed = 0;

        for(Mission* mission : missions) {
            for(Delivery* delivery : mission->getDeliveries()) {
                if(delivery->isCompleted()) {
                    deliveriesCompleted++;
                } else if(delivery->isExpired()) {
                    deliveriesMissed++;
                }
            }
        }

        bool success = deliveriesCompleted >= currentLevel.deliveriesForBronze;
        float score = std::max(500.0f * deliveriesCompleted - 250.0f * deliveriesMissed,
                               1000.0f * deliveriesCompleted - 500.0f * deliveriesMissed - timeSpent * 10.0f);
        score = std::max(score, 0.0f);

        bool hasPreviousScore = screen.getScoreSaver().hasScore(currentLevelNumber);
        Score previousBest;

        if(hasPreviousScore)
            previousBest = screen.getScoreSaver().loadScoreForLevel(currentLevelNumber);

        if(success) {
            screen.getScoreSaver().saveScore({ currentLevelNumber, deliveriesCompleted, deliveriesMissed, score });
        }

        screen.getCompleteMenu().show(success,
                                      deliveriesCompleted,
                                      deliveriesMissed,
                                      currentLevel.deliveriesForBronze,
                                      currentLevel.deliveriesForSilver,
                                      currentLevel.deliveriesForGold,
                                      score,
                                      hasPreviousScore,
                                      previousBest);

        if(success)
            successSound.play();
        else
            failureSound.play();
    }

    bool allSoftLocked = true;

    for(Snail* snail : snails) {
            if(snail->isMoving() and !snail->isBlockedMoving()
        or !snail->isMoving() and snail->hasMovementOption())
            allSoftLocked = false;
    }

    if(allSoftLocked) {
        for(Mission* mission : missions) {
            if(mission->isCompleted())
                continue;

            if(!mission->hasSpawnedSnail() && mission->canSpawnSnail())
                allSoftLocked = false;
        }
    }

    if(allSoftLocked) {
        bool allMissionsCompleted = true;
        for(Mission* mission : missions) {
            if(!mission->isCompleted()) {
                allMissionsCompleted = false;
            }
        }

        allSoftLocked = !allMissionsCompleted;
    }

    if(allSoftLocked) {
        screen.getCompleteMenu().softlock();
        failureSound.play();
    }
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
}

const std::vector<Entity*>& World::getEntities() const {
    return entities;
}

void World::removeTrashToBeDeleted() {
    size_t i = 0;
    while (i < this->entities.size()) {
        Entity* entity = this->entities.at(i);
        if (entity->shouldBeRemoved()) {
            entities.erase(entities.begin() + i);
            removeFromZOrderMap(entity);

            if(dynamic_cast<Snail*>(entity))
                snails.erase(std::find(snails.begin(), snails.end(), entity));

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

const std::unordered_map<ZOrder, std::vector<Entity*>>& World::getZOrderMap() const {
    return zOrderMap;
}

Graph* World::getGraph() const {
    return graph;
}

const std::vector<Snail*>& World::getSnails() const {
    return snails;
}

PostOffice* World::getPostOffice(int id) {
    return postOffices[id];
}

const std::vector<Mission *> &World::getMissions() const {
    return missions;
}
Friend* World::getFriend(int id) {
    return friends[id];
}

void World::loadNextLevel() {
    hasSnailMadeFirstMove = false;
    setPaused(false);
    currentLevelNumber++;
    generateLevel(Level::getLevel(currentLevelNumber), currentLevelNumber);
}

void World::retry() {
    hasSnailMadeFirstMove = false;
    setPaused(false);
    generateLevel(Level::getLevel(currentLevelNumber), currentLevelNumber);
}

const Level &World::getCurrentLevel() const {
    return currentLevel;
}

int World::getCurrentLevelNumber() const {
    return currentLevelNumber;
}

const std::unordered_map<int, PostOffice *> &World::getPostOffices() const {
    return postOffices;
}

void World::stopAllMusic() {
    getAssets().get(GameAssets::SNAIL_FRIENDS_60)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_70)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_80)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_90)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_100)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_110)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_120)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_130)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_140)->stop();
    getAssets().get(GameAssets::SNAIL_FRIENDS_150)->stop();
}

const wiz::MusicAsset& World::getSong(int levelNumber) {
    switch(levelNumber) {
        case 1: return GameAssets::SNAIL_FRIENDS_60;
        case 2: return GameAssets::SNAIL_FRIENDS_70;
        case 3: return GameAssets::SNAIL_FRIENDS_80;
        case 4: return GameAssets::SNAIL_FRIENDS_90;
        case 5: return GameAssets::SNAIL_FRIENDS_100;
        case 6: return GameAssets::SNAIL_FRIENDS_110;
        case 7: return GameAssets::SNAIL_FRIENDS_120;
        case 8: return GameAssets::SNAIL_FRIENDS_130;
        case 9: return GameAssets::SNAIL_FRIENDS_140;
        default: return GameAssets::SNAIL_FRIENDS_150;
    }
}

void World::setCurrentLevelNumber(int currentLevelNumber) {
    World::currentLevelNumber = currentLevelNumber;
}

GRand& World::getRandom() {
    return random;
}

void World::setPaused(bool paused) {
    World::paused = paused;
}

const ScoreSaver& World::getScoreSaver() {
    return screen.getScoreSaver();
}

