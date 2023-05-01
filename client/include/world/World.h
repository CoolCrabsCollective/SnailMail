//
// Created by cedric on 4/29/23.
//

//
// Created by Alexander Winter on 2023-01-06.
//

#ifndef LD52_CLIENT_SPACE_H
#define LD52_CLIENT_SPACE_H


#include "SFML/Graphics/Drawable.hpp"
#include "Tickable.h"
#include "WIZ/asset/AssetLoader.h"
#include "Entity.h"
#include "SFML/Graphics/View.hpp"
#include "Graph.h"
#include "SFML/Graphics/Sprite.hpp"
#include "world/snail/Snail.h"
#include "ui/LevelCompleteMenu.h"
#include "WIZ/asset/MusicAsset.h"

class Friend;
class PostOffice;
class Mission;
class MailScreen;

class World : public Tickable, public sf::Drawable {
protected:

    wiz::AssetLoader& assets;
    MailScreen& screen;
    std::vector<Entity*> entities, toAdd;
    mutable std::unordered_map<ZOrder, std::vector<Entity*>> zOrderMap;
    const sf::View view;

    Graph* graph = nullptr;
    std::vector<Snail*> snails;

    mutable sf::Sprite background;

    Level currentLevel;
    std::vector<Mission*> missions;
    std::unordered_map<int, Friend*> friends;
    std::unordered_map<int, PostOffice*> postOffices;

    bool paused = false;

public:
    const std::unordered_map<int, PostOffice *> &getPostOffices() const;

protected:

    void removeFromZOrderMap(Entity* entity);

public:
    const Level &getCurrentLevel() const;
    const static sf::Color snail_colors[];

protected:
    int currentLevelNumber = 1;
    float timeSpent = 0.0f;
public:
    constexpr const static sf::Vector2f VIEW_SIZE = { 16.0f, 9.0f };

    World(wiz::AssetLoader& assets, MailScreen& screen);

    void generateLevel(Level level);

    void loadNextLevel();

    void retry();

    void tick(float delta) override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    wiz::AssetLoader& getAssets() const;

    const std::vector<Entity*>& getEntities() const;

    void addEntity(Entity* entity);

    void removeTrashToBeDeleted();

    const sf::View& getView() const;

    const std::unordered_map<ZOrder, std::vector<Entity *>>& getZOrderMap() const;

    Graph* getGraph() const;

    const std::vector<Snail*>& getSnails() const;

    const std::vector<Mission *> &getMissions() const;

    Snail* spawnSnail(GraphNode *node, int i, float snail_speed);

    PostOffice* getPostOffice(int id);

    Friend* getFriend(int id);

    int getCurrentLevelNumber() const;

    void stopAllMusic();

    const wiz::MusicAsset& getSong(int number);

    void setCurrentLevelNumber(int currentLevelNumber);

    void setPaused(bool paused);
};


#endif //LD52_CLIENT_SPACE_H
