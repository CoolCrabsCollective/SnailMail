//
// Created by Alexander Winter on 2023-04-30.
//

#ifndef LD53_CLIENT_LEVELCOMPLETEMENU_H
#define LD53_CLIENT_LEVELCOMPLETEMENU_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "world/Tickable.h"
#include "ScoreSaver.h"
#include "SFML/Audio/Sound.hpp"

class World;

class LevelCompleteMenu : public sf::Drawable, public Tickable {
    World& world;
    wiz::AssetLoader& assets;

    bool visible, won;
    sf::Sprite shell;
    sf::Sprite background;
    sf::Text title;
    sf::Text nextShellRequirement;

    sf::Text countCompleted;
    sf::Text countMissed;
    sf::Text scoreText;

    bool hasPreviousBest;
    sf::Text yourBest;
    sf::Sprite yourBestShell;
    sf::Text bestCountCompleted;
    sf::Text bestCountMissed;
    sf::Text bestScore;

    mutable sf::Sprite buttonBackground;
    mutable sf::Text retryButton, nextButton;
    float retryScale, nextScale;
    bool retryHovered, nextHovered;

    sf::Sound clickSound;
public:
    LevelCompleteMenu(World& world);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void tick(float delta) override;

    void show(bool success,
              int deliveriesCompleted,
              int deliveriesMissed,
              int deliveriesForBronze,
              int deliveriesForSilver,
              int deliveriesForGold,
              float score,
              bool hasPreviousScore,
              Score previousBest);

    void hide();

    void click(sf::Vector2f position);

    void hover(sf::Vector2f position);

    bool isVisible();

    void softlock();
};


#endif //LD53_CLIENT_LEVELCOMPLETEMENU_H
