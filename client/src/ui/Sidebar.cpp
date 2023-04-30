//
// Created by cedric on 4/29/23.
//

#include "ui/Sidebar.h"
#include "GameAssets.h"
Sidebar::Sidebar(World& world) : world(world) {}

void Sidebar::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

    std::vector<sf::Color> colors = { Snail::SNAIL_COLOR_BLUE, Snail::SNAIL_COLOR_YELLOW, Snail::SNAIL_COLOR_RED};

    for(int i = 0; i < colors.size(); i++)
    {
        snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
        snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));
        snail_cap_sprite.setColor(colors[i]);
    }

}