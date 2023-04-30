//
// Created by cedric on 4/29/23.
//

#include "ui/Sidebar.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "world/level/Mission.h"
#include "world/level/Delivery.h"
#include "world/friends/LadyBug.h"
#include "world/friends/Mouse.h"
#include "world/friends/Frog.h"
#include "world/friends/Bee.h"

Sidebar::Sidebar(World& world) : world(world) {}

void Sidebar::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

    constexpr float snail_margin = 40.f;
    constexpr float distance_between_snails = 50.f;
    constexpr float offset_from_delivery = 100.f;
    constexpr float snail_scale = 4.f;
    constexpr float snail_time_distance = 150.f;
    constexpr float snail_friend_distance = 250.f;
    std::vector<Snail*> snails = world.getSnails();

    std::vector<Mission*> missions = world.getMissions();

    sf::RectangleShape background;
    background.setSize(sf::Vector2f{400.f, 900.f});
    background.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR, 0.f});
    background.setFillColor(sf::Color(0x8f, 0x56, 0x3b));
    target.draw(background);

    int snail_offset = 0;
    for(int i = 0; i < snails.size(); i++)
    {
        snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
        sf::Vector2f pos = sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin, snail_margin + snail_offset};
        snail_sprite.setPosition(pos);
        snail_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});
        snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));
        snail_cap_sprite.setColor(snails[i]->getSnailColor());
        snail_cap_sprite.setPosition(pos);
        snail_cap_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});

        target.draw(snail_sprite);
        target.draw(snail_cap_sprite);

        const std::vector<Delivery*>& deliveries = missions[i]->getDeliveries();

        std::vector<Delivery*> activeDeliveries;
        for(Delivery* d : deliveries)
        {
            if(!d->isCompleted())
            {
                activeDeliveries.push_back(d);
            }
        }


        for(int j = 0; j < activeDeliveries.size(); j++)
        {
            Friend* friend_to_deliver = activeDeliveries[j]->getDestination();
            sf::Texture* friendTexture = nullptr;
            if (dynamic_cast<LadyBug*>(friend_to_deliver))
            {
                friendTexture = world.getAssets().get(GameAssets::LADY_BUG);
            }else if(dynamic_cast<Bee*>(friend_to_deliver)){

                friendTexture = world.getAssets().get(GameAssets::BEE);
            }
            else if(dynamic_cast<Frog*>(friend_to_deliver)){

                friendTexture = world.getAssets().get(GameAssets::FROG);
            }
            else if(dynamic_cast<Mouse*>(friend_to_deliver)){

                friendTexture = world.getAssets().get(GameAssets::MOUSE);
            }
            else {
                throw std::runtime_error("Could not find friend for delivery!!");
            }

            int time_left = std::round(activeDeliveries[j]->getTimeLeft());

            std::string time_str = std::to_string(time_left);
            number_text.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin + snail_time_distance, snail_margin + snail_offset});
            number_text.setString(time_str);
            number_text.setFillColor(sf::Color::Black);
            number_text.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));

            if(activeDeliveries[j]->isExpired())
            {
                number_text.setString("X");
            } else if(!std::isfinite(activeDeliveries[j]->getTimeLeft()))
                number_text.setString("");
            target.draw(number_text);

            friend_sprite.setTexture(*friendTexture);
            friend_sprite.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + snail_margin + snail_friend_distance, snail_margin + snail_offset});
            SpriteUtil::setSpriteSize(friend_sprite, sf::Vector2f{70., 70.});
            SpriteUtil::setSpriteOrigin(friend_sprite, sf::Vector2f{0.5, 0.25});
            target.draw(friend_sprite);

            snail_offset += offset_from_delivery;
        }


        if(i < snails.size() - 1)
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