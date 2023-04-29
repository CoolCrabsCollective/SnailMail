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
#include <list>

class World : public Tickable, public sf::Drawable {
protected:
    wiz::AssetLoader& assets;
    std::vector<Entity*> entities, toAdd;


    mutable std::vector<Entity*> entities_draw_list;
public:
    constexpr const static sf::Vector2f VIEW_SIZE = { 16.0f, 9.0f };
    constexpr const static float CHUNK_SIZE = 4.0f;
    constexpr const static float MAP_RADIUS = 80.0f;

    World(wiz::AssetLoader& assets);

    void tick(float delta) override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    wiz::AssetLoader& getAssets() const;

    const std::vector<Entity*>& getEntities() const;

    void addEntity(Entity* entity);

    bool gameover = false; // why is this public
    bool paused = false; // why not scrub
};


#endif //LD52_CLIENT_SPACE_H
