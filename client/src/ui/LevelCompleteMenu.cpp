//
// Created by Alexander Winter on 2023-04-30.
//

#include "ui/LevelCompleteMenu.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "world/World.h"

LevelCompleteMenu::LevelCompleteMenu(World& world)
    : world(world),
        assets(world.getAssets()),
        visible(false),
        won(false),
        hasPreviousBest(false),
        retryHovered(false),
        nextHovered(false),
        retryScale(1.0f),
        nextScale(1.0f) {
    background.setTexture(*assets.get(GameAssets::WHITE_PIXEL));
    background.setColor(sf::Color(0, 0, 0, 100));
    background.setPosition({0.0f, 0.0f });
    SpriteUtil::setSpriteSize(background, { 1600.0f, 900.0f });

    buttonBackground.setTexture(*assets.get(GameAssets::BUTTON));
    SpriteUtil::setSpriteSize(buttonBackground, {250.0f, 125.0f});
    SpriteUtil::setSpriteOrigin(buttonBackground, { 0.5f, 0.5f });
}

void LevelCompleteMenu::show(bool success,
                             int deliveriesCompleted,
                             int deliveriesMissed,
                             int deliveriesForBronze,
                             int deliveriesForSilver,
                             int deliveriesForGold,
                             float score) {
    visible = true;
    won = success;
    retryScale = 1.0f;
    nextScale = 1.0f;
    retryHovered = false;
    nextHovered = false;

    if(!success) {
        shell.setTexture(*assets.get(GameAssets::LOSER_SHELL), true);
        nextShellRequirement.setString("Complete " + std::to_string(deliveriesForBronze) + " to win");
    } else if(deliveriesCompleted >= deliveriesForGold) {
        shell.setTexture(*assets.get(GameAssets::GOLD_SHELL), true);
        nextShellRequirement.setString("");
    } else if(deliveriesCompleted >= deliveriesForSilver) {
        shell.setTexture(*assets.get(GameAssets::SILVER_SHELL), true);
        nextShellRequirement.setString("Complete " + std::to_string(deliveriesForGold) + " for gold");
    } else {
        shell.setTexture(*assets.get(GameAssets::BRONZE_SHELL), true);
        nextShellRequirement.setString("Complete " + std::to_string(deliveriesForGold) + " for silver");
    }

    shell.setPosition({ 300.0f, 200.0f });
    SpriteUtil::setSpriteSize(shell, { 200.0f, 200.0f });
    SpriteUtil::setSpriteOrigin(shell, { 0.0f, 0.0f });

    title.setString(success ? "Success!" : "Too late!");
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(100);
    title.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    sf::FloatRect textRect = title.getLocalBounds();
    title.setPosition({ 610.0f, 400.0f - textRect.height - 50.0f });

    countCompleted.setString(std::to_string(deliveriesCompleted) + " completed");
    countCompleted.setFillColor(sf::Color::White);
    countCompleted.setCharacterSize(45);
    countCompleted.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    countCompleted.setPosition({ 610.0f, 400.0f });
    countCompleted.setStyle(sf::Text::Bold);

    countMissed.setString(std::to_string(deliveriesMissed) + " missed");
    countMissed.setFillColor(sf::Color::White);
    countMissed.setCharacterSize(45);
    countMissed.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    countMissed.setPosition({ 610.0f, 450.0f });
    countMissed.setStyle(sf::Text::Bold);

    scoreText.setString("Score: " + std::to_string((int)score));
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(45);
    scoreText.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    scoreText.setPosition({ 610.0f, 500.0f});
    scoreText.setStyle(sf::Text::Bold);

    hasPreviousBest = false;
    yourBest.setString("Your best:");
    yourBest.setFillColor(sf::Color::White);
    yourBest.setCharacterSize(45);
    yourBest.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    yourBest.setPosition({ 910.0f, 450.0f});

    //if(!success)
    //    shell.setTexture(*assets.get(GameAssets::LOSER_SHELL), true);
    //else if(deliveriesCompleted >= deliveriesForGold)
    //    shell.setTexture(*assets.get(GameAssets::GOLD_SHELL), true);
    //else if(deliveriesCompleted >= deliveriesForSilver)
    //    shell.setTexture(*assets.get(GameAssets::SILVER_SHELL), true);
    //else
        yourBestShell.setTexture(*assets.get(GameAssets::BRONZE_SHELL), true);

    yourBestShell.setPosition({ 1100.0f, 440.0f });
    SpriteUtil::setSpriteSize(yourBestShell, { 75.0f, 75.0f });
    SpriteUtil::setSpriteOrigin(yourBestShell, { 0.0f, 0.0f });

    bestCountCompleted.setString("X completed");
    bestCountCompleted.setFillColor(sf::Color::White);
    bestCountCompleted.setCharacterSize(45);
    bestCountCompleted.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    bestCountCompleted.setPosition({ 1210.0f, 400.0f });

    bestCountMissed.setString("X missed");
    bestCountMissed.setFillColor(sf::Color::White);
    bestCountMissed.setCharacterSize(45);
    bestCountMissed.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    bestCountMissed.setPosition({ 1210.0f, 450.0f });

    bestScore.setString("Score: XXX");
    bestScore.setFillColor(sf::Color::White);
    bestScore.setCharacterSize(45);
    bestScore.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    bestScore.setPosition({ 1210.0f, 500.0f});

    retryButton.setString("Retry");
    retryButton.setFillColor(sf::Color::White);
    retryButton.setCharacterSize(90);
    retryButton.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    textRect = retryButton.getLocalBounds();
    retryButton.setPosition({ 500.0f, 675.0f + textRect.height / 2.0f});
    retryButton.setOrigin({ 0.5f * textRect.width, 0.5f * textRect.height });

    nextButton.setString("Next");
    nextButton.setFillColor(sf::Color::White);
    nextButton.setCharacterSize(90);
    nextButton.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    textRect = nextButton.getLocalBounds();
    nextButton.setPosition({ 900.0f, 675.0f + textRect.height / 2.0f});
    nextButton.setOrigin({ 0.5f * textRect.width, 0.5f * textRect.height });

    nextShellRequirement.setFillColor(sf::Color::White);
    nextShellRequirement.setCharacterSize(45);
    nextShellRequirement.setFont(*assets.get(GameAssets::THE_RIGHT_FONT));
    nextShellRequirement.setPosition({200.0f, 400.0f});
}

void LevelCompleteMenu::hide() {
    visible = false;
}

void LevelCompleteMenu::tick(float delta) {
    if(retryHovered) {
        retryScale += delta * 8.0f;
        if(retryScale > 1.2f)
            retryScale = 1.2f;
    } else {
        retryScale -= delta * 10.0f;
        if(retryScale < 1.0f)
            retryScale = 1.0f;
    }

    if(nextHovered) {
        nextScale += delta * 8.0f;
        if(nextScale > 1.2f)
            nextScale = 1.2f;
    } else {
        nextScale -= delta * 10.0f;
        if(nextScale < 1.0f)
            nextScale = 1.0f;
    }
}

void LevelCompleteMenu::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if(!visible)
        return;

    target.draw(background);
    target.draw(shell);
    target.draw(nextShellRequirement);

    target.draw(title);

    target.draw(countCompleted);
    target.draw(countMissed);
    target.draw(scoreText);

    if(hasPreviousBest) {
        target.draw(yourBest);
        target.draw(yourBestShell);
        target.draw(bestCountCompleted);
        target.draw(bestCountMissed);
        target.draw(bestScore);
    }
    buttonBackground.setPosition({ 500.0f, 735.0f });
    buttonBackground.setScale(buttonBackground.getScale() * retryScale);
    target.draw(buttonBackground);
    retryButton.setScale(retryButton.getScale() * retryScale);
    target.draw(retryButton);
    retryButton.setScale(retryButton.getScale() / retryScale);
    buttonBackground.setScale(buttonBackground.getScale() / retryScale);

    if(won) {
        buttonBackground.setPosition({ 900.0f, 735.0f });
        buttonBackground.setScale(buttonBackground.getScale() * nextScale);
        target.draw(buttonBackground);
        nextButton.setScale(nextButton.getScale() * nextScale);
        target.draw(nextButton);
        nextButton.setScale(nextButton.getScale() / nextScale);
        buttonBackground.setScale(buttonBackground.getScale() / nextScale);
    }
}

void LevelCompleteMenu::click(sf::Vector2f position) {
    if(!visible)
        return;

    if(position.x >= 375.0f && position.x <= 625.0f && position.y >= 735.0f - 62.5f && position.y <= 735.0f + 62.5f) {
        world.retry();
        hide();
    }

    if(won && position.x >= 775.0f && position.x <= 1025.0f && position.y >= 735.0f - 62.5f && position.y <= 735.0f + 62.5f) {
        world.loadNextLevel();
        hide();
    }
}

void LevelCompleteMenu::hover(sf::Vector2f position) {
    if(!visible)
        return;

    retryHovered = false;
    nextHovered = false;
    if(position.x >= 375.0f && position.x <= 625.0f && position.y >= 735.0f - 62.5f && position.y <= 735.0f + 62.5f) {
        retryHovered = true;
    }

    if(won && position.x >= 775.0f && position.x <= 1025.0f && position.y >= 735.0f - 62.5f && position.y <= 735.0f + 62.5f) {
        nextHovered = true;
    }
}

bool LevelCompleteMenu::isVisible() {
    return visible;
}
