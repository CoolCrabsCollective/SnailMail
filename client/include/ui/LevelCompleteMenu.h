//
// Created by Alexander Winter on 2023-04-30.
//

#ifndef LD53_CLIENT_LEVELCOMPLETEMENU_H
#define LD53_CLIENT_LEVELCOMPLETEMENU_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "WIZ/asset/AssetLoader.h"

class LevelCompleteMenu : public sf::Drawable {
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
    sf::Text retryButton, nextButton;
public:
    LevelCompleteMenu(wiz::AssetLoader& assets);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void show(bool success,
              int deliveriesCompleted,
              int deliveriesMissed,
              int deliveriesForBronze,
              int deliveriesForSilver,
              int deliveriesForGold,
              float score);

    void hide();
};


#endif //LD53_CLIENT_LEVELCOMPLETEMENU_H
