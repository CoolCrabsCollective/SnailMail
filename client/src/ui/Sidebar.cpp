//
// Created by cedric on 4/29/23.
//

#include <iostream>
#include "ui/Sidebar.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "world/level/Mission.h"
#include "world/level/Delivery.h"
#include "world/friends/LadyBug.h"
#include "world/friends/Mouse.h"
#include "world/friends/Frog.h"
#include "world/friends/Bee.h"

Sidebar::Sidebar(World& world) : world(world) {
    deliveryText.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    deliveryText.setFillColor(sf::Color::White);
    deliveryText.setCharacterSize(40);
    deliveryText.setString("Deliveries");
    deliveryText.setStyle(sf::Text::Underlined);

    smailsmanText.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    smailsmanText.setFillColor(sf::Color::White);
    smailsmanText.setCharacterSize(30);
    smailsmanText.setString("Smailsman");

    recipientText.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    recipientText.setFillColor(sf::Color::White);
    recipientText.setCharacterSize(30);
    recipientText.setString("Recipient");

    timeLeftText.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    timeLeftText.setFillColor(sf::Color::White);
    timeLeftText.setCharacterSize(30);
    timeLeftText.setString("Time");
}

void Sidebar::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    constexpr float snail_scale = 3.f;
    constexpr float v_friend_offset = 55.f;
    constexpr float v_time_offset = 40.f;
    constexpr float v_snail_offset = 40.f;
    constexpr float v_distance_between_friends = 80.f;
    constexpr float v_top_bar_offset = 130.f;
    constexpr float v_friend_bottom_padding = 15.f;

    constexpr float h_snail_spacing = 80.f;
    constexpr float h_friend_offset = 220.f;
    constexpr float h_time_offset = 345.f;

    std::vector<Snail*> snails = world.getSnails();

    std::vector<Mission*> missions = world.getMissions();

    sf::Sprite background;
    background.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR, 0.f});
    background.setTexture(*world.getAssets().get(GameAssets::ALEXS_DESIRE));
    background.setScale({10.f, 10.f});
    target.draw(background);
    const float background_width = background.getGlobalBounds().width;

    sf::FloatRect deliveryRect = deliveryText.getLocalBounds();
    deliveryText.setOrigin({deliveryRect.left + deliveryRect.width / 2.0f, deliveryRect.top + deliveryRect.height / 2.0f});
    deliveryText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + background.getGlobalBounds().width /2, deliveryRect.height + 10.0f});
    target.draw(deliveryText);

    sf::FloatRect smailsmanRect = smailsmanText.getLocalBounds();
    smailsmanText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + 15.0f, deliveryRect.height + 60.0f});
    target.draw(smailsmanText);

    sf::FloatRect recipientRect = recipientText.getLocalBounds();
    recipientText.setOrigin({recipientText.getLocalBounds().width/2.0f, 0});
    recipientText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + background_width * 0.5f + 10.0f, recipientRect.height + 60.0f});
    target.draw(recipientText);

    sf::FloatRect timeLeftRect = timeLeftText.getLocalBounds();
    timeLeftText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + 320.f, recipientRect.height + 60.0f});
    target.draw(timeLeftText);

    int alpha_from_waiting = 80;
    float last_top_bar = v_top_bar_offset;

    int current_mission_index = 0;
    for(int i = 0; i < missions.size(); i++) {
        if(missions[i]->isCompleted())
        {
            continue;
        }

        bool snail_is_queued = missions[i]->getSnail() == nullptr;

        sf::Color snail_color;

        if(snail_is_queued)
        {
            sf::Color base_color = World::snail_colors[world.getCurrentLevel().missions[i].snailId];
            snail_color = sf::Color(base_color.r, base_color.g, base_color.b, alpha_from_waiting);
        }
        else
        {
            snail_color = missions[i]->getSnail()->getSnailColor();
        }

        snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
        sf::Vector2f pos = sf::Vector2f{DISTANCE_TO_SIDEBAR + h_snail_spacing, last_top_bar + v_snail_offset};
        snail_sprite.setPosition(pos);
        snail_sprite.setColor(sf::Color(255.f, 255.f, 255.f, snail_is_queued ? alpha_from_waiting : 255.f));
        snail_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});
        SpriteUtil::setSpriteOrigin(snail_sprite, sf::Vector2f{0.5, 0.5});

        snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));
        snail_cap_sprite.setColor(sf::Color(snail_color.r, snail_color.g, snail_color.b, snail_is_queued ? 160 : 255));
        snail_cap_sprite.setPosition(pos);
        snail_cap_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});
        SpriteUtil::setSpriteOrigin(snail_cap_sprite, sf::Vector2f{0.5, 0.5});

        target.draw(snail_sprite);
        target.draw(snail_cap_sprite);

        const std::vector<Delivery*>& deliveries = missions[i]->getDeliveries();

        std::vector<Delivery*> activeDeliveries;
        bool done_delivering = true;
        for(Delivery* d : deliveries) {
            if(!d->isCompleted()) {
                activeDeliveries.push_back(d);
                done_delivering = false;
            }
        }

        for (int j = 0; j < activeDeliveries.size(); j++) {
            Friend* friend_to_deliver = activeDeliveries[j]->getDestination();
            sf::Texture* friendTexture = nullptr;
            if (dynamic_cast<LadyBug*>(friend_to_deliver)) {
                friendTexture = world.getAssets().get(GameAssets::LADY_BUG);
            } else if(dynamic_cast<Bee*>(friend_to_deliver)){
                friendTexture = world.getAssets().get(GameAssets::BEE);
            } else if(dynamic_cast<Frog*>(friend_to_deliver)){
                friendTexture = world.getAssets().get(GameAssets::FROG);
            } else if(dynamic_cast<Mouse*>(friend_to_deliver)){
                friendTexture = world.getAssets().get(GameAssets::MOUSE);
            } else {
                throw std::runtime_error("Could not find friend for delivery!!");
            }

            float time_left_float = activeDeliveries[j]->getTimeLeft();
            float modulo_float = time_left_float - std::floor(time_left_float);
            float v = (modulo_float - 0.5f);
            float time_multiplier = 1.f - (4 * v*v);
            int time_left = std::round(time_left_float);

            float character_size = 64.f;
            float character_bigger_delta = 16.f;
            float total_char_size = (character_size + character_bigger_delta * time_multiplier);

            if(time_left_float >= 10.f) {
                total_char_size = character_size;
            }
            std::string time_str = std::to_string(time_left);
            number_text.setOrigin({total_char_size / 2.f, total_char_size / 2.f});
            number_text.setString(time_str);
            number_text.setFillColor(snail_is_queued ? sf::Color(0, 0, 0, alpha_from_waiting) : sf::Color::Black);
            number_text.setCharacterSize((int)total_char_size);
            number_text.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
            if (activeDeliveries[j]->isExpired()) {
                number_text.setString("X");
                number_text.setCharacterSize(64);
            } else if(!std::isfinite(activeDeliveries[j]->getTimeLeft())) {
                number_text.setString("");
            }
            number_text.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + h_time_offset, last_top_bar + v_time_offset + v_distance_between_friends * j});
            target.draw(number_text);

            friend_sprite.setTexture(*friendTexture);
            friend_sprite.setColor(sf::Color(255, 255, 255, snail_is_queued ? alpha_from_waiting : 255));
            SpriteUtil::setSpriteSize(friend_sprite, sf::Vector2f{70., 70.});
            SpriteUtil::setSpriteOrigin(friend_sprite, sf::Vector2f{0.5, 0.5});
            friend_sprite.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + h_friend_offset, last_top_bar + v_friend_offset + v_distance_between_friends * j});
            target.draw(friend_sprite);
        }

        if(done_delivering) {
            post_office_sprite.setTexture(*world.getAssets().get(GameAssets::POST_OFFICE));
            SpriteUtil::setSpriteSize(post_office_sprite, sf::Vector2f{70., 70.});
            SpriteUtil::setSpriteOrigin(post_office_sprite, sf::Vector2f{0.5, 0.5});
            post_office_sprite.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + h_friend_offset,
                                                        last_top_bar + v_friend_offset });
            target.draw(post_office_sprite);
        }


        int num_entries_in_row = std::max(static_cast<size_t>(1), activeDeliveries.size());
        last_top_bar += num_entries_in_row * v_distance_between_friends + v_friend_bottom_padding;
        if(i < missions.size() - 1) {
            sf::RectangleShape line;
            line.setFillColor(sf::Color(116.f, 63.f, 57.f));
            line.setSize(sf::Vector2f{400.f, 10.f});
            line.setPosition(sf::Vector2f {DISTANCE_TO_SIDEBAR, last_top_bar});
            target.draw(line);
        }

        current_mission_index++;
    }
}