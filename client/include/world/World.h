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
#include "input/EntitySelection.h"
#include "world/snail/Snail.h"

class World : public Tickable, public sf::Drawable {
protected:
    wiz::AssetLoader& assets;
    std::vector<Entity*> entities, toAdd;
    mutable std::map<ZOrder, std::vector<Entity*>> zOrderMap;
    const sf::View view;

    Graph* graph = nullptr;
    std::vector<Snail*> snails;

    void removeFromZOrderMap(Entity* entity);

    mutable sf::Sprite background;
    EntitySelection* entitySelection = nullptr;

public:
    constexpr const static sf::Vector2f VIEW_SIZE = { 16.0f, 9.0f };

    World(wiz::AssetLoader& assets);

    void tick(float delta) override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    wiz::AssetLoader& getAssets() const;

    const std::vector<Entity*>& getEntities() const;

    void addEntity(Entity* entity);

    void removeTrashToBeDeleted();

    const sf::View& getView() const;

    const std::map<ZOrder, std::vector<Entity *>> &getZOrderMap() const;

    EntitySelection *getEntitySelection() const;

    Graph *getGraph() const;

    const std::vector<Snail *> &getSnails() const;
};


#endif //LD52_CLIENT_SPACE_H
