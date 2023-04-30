//
// Created by cedric on 4/29/23.
//

#include "ui/Sidebar.h"
#include "GameAssets.h"
Sidebar::Sidebar(World& world) : world(world) {}

void Sidebar::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

    constexpr float snail_margin = 20.f;
    constexpr float distance_between_snails = 150.f;
    constexpr float snail_scale = 4.f;
    std::vector<sf::Color> colors = { Snail::SNAIL_COLOR_BLUE, Snail::SNAIL_COLOR_YELLOW, Snail::SNAIL_COLOR_RED};
    sf::RectangleShape background;
    background.setSize(sf::Vector2f{400.f, 900.f});
    background.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR, 0.f});
    background.setFillColor(sf::Color(0x8f, 0x56, 0x3b));
    target.draw(background);

    for(int i = 0; i < colors.size(); i++)
    {
        snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
        sf::Vector2f pos = sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin, snail_margin + distance_between_snails * i};
        snail_sprite.setPosition(pos);
        snail_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});
        snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));
        snail_cap_sprite.setColor(colors[i]);
        snail_cap_sprite.setPosition(pos);
        snail_cap_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});

        target.draw(snail_sprite);
        target.draw(snail_cap_sprite);
    }

}