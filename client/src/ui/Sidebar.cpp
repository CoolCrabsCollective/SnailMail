//
// Created by cedric on 4/29/23.
//

#include "ui/Sidebar.h"
#include "GameAssets.h"
#include "SpriteUtil.h"

Sidebar::Sidebar(World& world) : world(world) {}

void Sidebar::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

    constexpr float snail_margin = 40.f;
    constexpr float distance_between_snails = 50.f;
    constexpr float offset_from_delivery = 100.f;
    constexpr float snail_scale = 4.f;
    constexpr float snail_time_distance = 150.f;
    constexpr float snail_friend_distance = 250.f;
    std::vector<sf::Color> colors = { Snail::SNAIL_COLOR_BLUE, Snail::SNAIL_COLOR_YELLOW, Snail::SNAIL_COLOR_RED};
    std::vector<std::vector<int>> delivery_ids = {{0, 1}, {1, 2, 3}, {0, 3}};
    std::vector<std::vector<int>> time_left = {{7, 12}, {3, 15, 22}, {17, 25}};

    sf::RectangleShape background;
    background.setSize(sf::Vector2f{400.f, 900.f});
    background.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR, 0.f});
    background.setFillColor(sf::Color(0x8f, 0x56, 0x3b));
    target.draw(background);

    int snail_offset = 0;
    for(int i = 0; i < colors.size(); i++)
    {
        snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
        sf::Vector2f pos = sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin, snail_margin + snail_offset};
        snail_sprite.setPosition(pos);
        snail_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});
        snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));
        snail_cap_sprite.setColor(colors[i]);
        snail_cap_sprite.setPosition(pos);
        snail_cap_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});

        target.draw(snail_sprite);
        target.draw(snail_cap_sprite);

        std::vector<int>& deliveries = delivery_ids[i];
        std::vector<int>& times = time_left[i];

        std::vector<sf::Texture*> friend_textures = {
                world.getAssets().get(GameAssets::LADY_BUG),
                world.getAssets().get(GameAssets::BEE),
                world.getAssets().get(GameAssets::FROG),
                world.getAssets().get(GameAssets::MOUSE)
        };

        for(int j = 0; j < deliveries.size(); j++)
        {
            int delivery_id = deliveries[j];
            int time_left = times[j];

            std::string time_str = std::to_string(time_left);
            number_text.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin + snail_time_distance, snail_margin + snail_offset});
            number_text.setString(time_str);
            number_text.setFillColor(sf::Color::Black);
            number_text.setFont(*world.getAssets().get(GameAssets::SANS_TTF));

            target.draw(number_text);



            sf::Texture* texture = friend_textures[delivery_id];
            friend_sprite.setTexture(*texture);
            friend_sprite.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin + snail_friend_distance, snail_margin + snail_offset});
            SpriteUtil::setSpriteSize(friend_sprite, sf::Vector2f{70., 70.});
            SpriteUtil::setSpriteOrigin(friend_sprite, sf::Vector2f{0.5, 0.25});
            target.draw(friend_sprite);

            snail_offset += offset_from_delivery;
        }


        if(i < colors.size() - 1)
        {
            sf::RectangleShape line;
            line.setFillColor(sf::Color::Black);
            line.setSize(sf::Vector2f{400.f, 10.f});
            line.setPosition(sf::Vector2f {DISTANCE_TO_SIDEBAR, snail_margin + snail_offset});
            target.draw(line);
        }
        snail_offset += distance_between_snails;
    }


}