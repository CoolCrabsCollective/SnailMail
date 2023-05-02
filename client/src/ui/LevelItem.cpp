//
// Created by william on 30/04/23.
//

#include "ui/LevelItem.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/World.h"
#include "ui/LevelSelMenu.h"

LevelItem::LevelItem(World& world,
                     LevelSelMenu& levelSelMenu,
                     sf::Vector2f parentMenuOffset,
                     int levelNum)
    : ClickableUI({0.f, 0.f}, {0.f, 0.f}),
       world(world),
       levelSelMenu(levelSelMenu),
       parentMenuOffset(parentMenuOffset),
       levelNum(levelNum) {
    clickSound.setBuffer(*world.getAssets().get(GameAssets::CLICK));

    calculateOffsets();

    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_SEL_MENU_ITEM));
    backgroundSprite.setPosition(mainOffset);

    greyOutSprite.setTexture(*world.getAssets().get(GameAssets::WHITE_PIXEL));
    SpriteUtil::setSpriteSize(greyOutSprite, size);
    SpriteUtil::setSpriteOrigin(greyOutSprite, sf::Vector2f{0.5f, 0.5f});
    greyOutSprite.setColor(sf::Color(125, 125, 125, 125));
    greyOutSprite.setPosition(mainOffset);

    metalSprite.setPosition(metalOffset);

    level_num.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    level_num.setFillColor(sf::Color::Black);
    level_num.setPosition(numOffset);
    std::string levelNumString = std::to_string(levelNum);

    if (levelNumString.length() < 2) {
        levelNumString.insert(0, "0");
    }
    level_num.setString(levelNumString);

    clickable = false;
}

void LevelItem::tick(float delta) {
    if(hovered) {
        backgroundScale += delta * 8.0f;
        if(backgroundScale > 1.2f)
            backgroundScale = 1.2f;
    } else {
        backgroundScale -= delta * 10.0f;
        if(backgroundScale < 1.0f)
            backgroundScale = 1.0f;
    }
}

void LevelItem::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    SpriteUtil::setSpriteSize(backgroundSprite, size * backgroundScale);
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});
    target.draw(backgroundSprite);

    if (drawMetal) {
        SpriteUtil::setSpriteSize(metalSprite, {35.f, 35.f});
        SpriteUtil::setSpriteOrigin(metalSprite, sf::Vector2f{0.5f, 0.5f});
        target.draw(metalSprite);
    }

    target.draw(level_num);

    if (!clickable) {
        target.draw(greyOutSprite);
    }
}

void LevelItem::hitAction(bool& isHit) {
    if (isHit) {
        world.generateLevel(Level::getLevel(levelNum), levelNum);
        world.setCurrentLevelNumber(levelNum);
        bool hit = true;
        levelSelMenu.hitAction(hit);
    }
}

void LevelItem::calculateOffsets() {
    int rowNum = (levelNum - 1) / max_per_row;
    int rowNumOffset = (levelNum - 1) - rowNum*max_per_row;

    float yPos = -85.f + (size.y + 25.f) * (float) rowNum;

    float xPos = -270.f + (25.f + size.x) * (float) rowNumOffset;

    mainOffset = parentMenuOffset + sf::Vector2f{xPos, yPos};
    metalOffset = mainOffset + sf::Vector2f{0.f, -15.f};
    numOffset = mainOffset + sf::Vector2f{-10.f, 0.f};

    ClickableUI::boundingBoxBL = mainOffset - (size / 2.f);
    ClickableUI::boundingBoxTR = mainOffset + (size / 2.f);
}

void LevelItem::updateMedals() {
    drawMetal = false;
    clickable = true;

    if (!world.getScoreSaver().hasScore(levelNum)) {
        if (!world.getScoreSaver().hasScore(levelNum - 1))
            clickable = false;

        return;
    }

    Level level = Level::getLevel(levelNum);

    int deliveriesCompleted = world.getScoreSaver().loadScoreForLevel(levelNum).delivered;

    if(deliveriesCompleted >= level.deliveriesForGold) {
        metalSprite.setTexture(*world.getAssets().get(GameAssets::GOLD_SHELL), true);
        drawMetal = true;
    } else if(deliveriesCompleted >= level.deliveriesForSilver) {
        metalSprite.setTexture(*world.getAssets().get(GameAssets::SILVER_SHELL), true);
        drawMetal = true;
    } else {
        drawMetal = true;
        metalSprite.setTexture(*world.getAssets().get(GameAssets::BRONZE_SHELL), true);
    }
}

void LevelItem::hoverAction(bool& isHit) {
    hovered = isHit;
}

