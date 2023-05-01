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
    smailsmanText.setStyle(sf::Text::Italic);

    recipientText.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    recipientText.setFillColor(sf::Color::White);
    recipientText.setCharacterSize(30);
    recipientText.setString("Recipient");
    recipientText.setStyle(sf::Text::Italic);

    timeLeftText.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    timeLeftText.setFillColor(sf::Color::White);
    timeLeftText.setCharacterSize(30);
    timeLeftText.setString("Time Left");
    timeLeftText.setStyle(sf::Text::Italic);
}

void Sidebar::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    constexpr float snail_margin = 40.f;
    constexpr float offset_from_delivery = 100.f;
    constexpr float snail_scale = 3.f;
    constexpr float snail_time_distance = 150.f;
    constexpr float top_bar_offset = 75.f;
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
    //smailsmanText.setOrigin({smailsmanRect.left + smailsmanRect.width/2.0f, smailsmanRect.top + smailsmanRect.height/2.0f});
    smailsmanText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + 15.0f, deliveryRect.height + 60.0f});
    target.draw(smailsmanText);

    sf::FloatRect recipientRect = recipientText.getLocalBounds();
    recipientText.setOrigin({recipientText.getLocalBounds().width/2.0f, 0});
    recipientText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + background_width * 0.5f + 10.0f, recipientRect.height + 60.0f});
    target.draw(recipientText);

    sf::FloatRect timeLeftRect = timeLeftText.getLocalBounds();
    //smailsmanText.setOrigin({smailsmanRect.left + smailsmanRect.width/2.0f, smailsmanRect.top + smailsmanRect.height/2.0f});
    timeLeftText.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + background_width - timeLeftRect.width, recipientRect.height + 60.0f});
    target.draw(timeLeftText);

    float snail_offset = 150.0f;
    for(int i = 0; i < missions.size(); i++) {
        if(missions[i]->getSnail() == nullptr)
            continue;

        float second_or_more_snail_offset = i > 0 ? 30.f : 0.f;
        snail_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY));
        sf::Vector2f pos = sf::Vector2f{DISTANCE_TO_SIDEBAR + background_width/6 + 7.5f, snail_margin + snail_offset + second_or_more_snail_offset};
        snail_sprite.setPosition(pos);
        snail_sprite.setScale(sf::Vector2f{snail_scale, snail_scale});
        SpriteUtil::setSpriteOrigin(snail_sprite, sf::Vector2f{0.5, 0.5});
        snail_cap_sprite.setTexture(*world.getAssets().get(GameAssets::SNAILY_CAP));
        snail_cap_sprite.setColor(missions[i]->getSnail()->getSnailColor());
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
            number_text.setFillColor(sf::Color::Black);
            number_text.setCharacterSize((int)total_char_size);
            number_text.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
            if (activeDeliveries[j]->isExpired()) {
                number_text.setString("X");
                number_text.setCharacterSize(64);
            } else if(!std::isfinite(activeDeliveries[j]->getTimeLeft())) {
                number_text.setString("");
            }
            number_text.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + background_width - (snail_margin) - 5.0f, //+ snail_time_distance + character_size / 2.f,
                                                 snail_margin + snail_offset + second_or_more_snail_offset});
            target.draw(number_text);

            friend_sprite.setTexture(*friendTexture);
            SpriteUtil::setSpriteSize(friend_sprite, sf::Vector2f{70., 70.});
            SpriteUtil::setSpriteOrigin(friend_sprite, sf::Vector2f{0.5, 0.5});
            friend_sprite.setPosition(sf::Vector2f{DISTANCE_TO_SIDEBAR + (snail_margin/2) + ((0.5f)*background_width),
                                                   snail_margin + snail_offset + second_or_more_snail_offset});
            target.draw(friend_sprite);

            snail_offset += offset_from_delivery;
        }

        if(done_delivering) {
            post_office_sprite.setTexture(*world.getAssets().get(GameAssets::POST_OFFICE));
            SpriteUtil::setSpriteSize(post_office_sprite, sf::Vector2f{70., 70.});
            SpriteUtil::setSpriteOrigin(post_office_sprite, sf::Vector2f{0.0, 0.5});
            post_office_sprite.setPosition(sf::Vector2f{Sidebar::DISTANCE_TO_SIDEBAR + background_width * 0.5f + 10.0f, recipientRect.height + 60.0f});
            target.draw(post_office_sprite);
            snail_offset += offset_from_delivery;
        }

        float minimum_offset =  150.f;
        float total_snail_offset = std::max(snail_offset, top_bar_offset + minimum_offset * (i + 1));
        if(i < missions.size() - 1) {
            sf::RectangleShape line;
            line.setFillColor(sf::Color(116.f, 63.f, 57.f));
            line.setSize(sf::Vector2f{400.f, 10.f});
            line.setPosition(sf::Vector2f {DISTANCE_TO_SIDEBAR, total_snail_offset});
            target.draw(line);
        }

        snail_offset = total_snail_offset;
    }
}