//
// Created by william on 30/04/23.
//

#include "ui/LevelSelMenu.h"
#include "GameAssets.h"
#include "SpriteUtil.h"
#include "world/World.h"

LevelSelMenu::LevelSelMenu(World &world)
    : ClickableUI({0.f, 0.f},
                  {0.f, 0.f}),
      world(world),
      clickSound(),
      buttonBackground(),
      restartButton(),
      restartScale(1.0f),
      restartHovered(false) {
    buttonBackground.setTexture(*world.getAssets().get(GameAssets::BUTTON));
    SpriteUtil::setSpriteOrigin(buttonBackground, { 0.5f, 0.5f });
    buttonBackground.setPosition({ 800.0f, 800.0f });
    SpriteUtil::setSpriteSize(buttonBackground, { 300.0f, 100.0f });

    restartButton.setString("Restart Level");
    restartButton.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    restartButton.setCharacterSize(50);
    sf::FloatRect rect = restartButton.getLocalBounds();

    restartButton.setPosition({ 800.0f - rect.width / 2.0f, 800.0f - rect.height * 3.0f / 2.0f });

    backgroundSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_SEL_MENU_BACKDROP));
    backgroundSprite.setPosition(mainOffset);
    SpriteUtil::setSpriteSize(backgroundSprite, mainSize);
    SpriteUtil::setSpriteOrigin(backgroundSprite, sf::Vector2f{0.5f, 0.5f});

    label.setFont(*world.getAssets().get(GameAssets::THE_RIGHT_FONT));
    label.setFillColor(sf::Color::Black);
    label.setPosition(mainOffset + labelOffset);
    label.setString("LEVELS");

    exitButtonSprite.setTexture(*world.getAssets().get(GameAssets::LEVEL_SEL_MENU_EXIT));
    exitButtonSprite.setPosition(mainOffset + buttonOffset);
    SpriteUtil::setSpriteSize(exitButtonSprite, sf::Vector2f{50.f, 50.f});
    SpriteUtil::setSpriteOrigin(exitButtonSprite, sf::Vector2f{0.5f, 0.5f});

    boundingBoxBL = mainOffset + buttonOffset - (sf::Vector2f{50.f, 50.f} / 2.f);
    boundingBoxTR = mainOffset + buttonOffset + (sf::Vector2f{50.f, 50.f} / 2.f);

    populateLevels();

    clickable = false;
    clickSound.setBuffer(*world.getAssets().get(GameAssets::CLICK));
}

void LevelSelMenu::tick(float delta) {
    if(restartHovered) {
        restartScale += delta * 8.0f;
        if(restartScale > 1.2f)
            restartScale = 1.2f;
    } else {
        restartScale -= delta * 10.0f;
        if(restartScale < 1.0f)
            restartScale = 1.0f;
    }

    for (LevelItem* levelItem : levelItems) {
        levelItem->tick(delta);
    }
}

void LevelSelMenu::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if (!isOpen)
        return;

    target.draw(backgroundSprite);
    target.draw(label);
    target.draw(exitButtonSprite);

    for (LevelItem* levelItem : levelItems) {
        target.draw(*levelItem);
    }

    buttonBackground.setScale(buttonBackground.getScale() * restartScale);
    target.draw(buttonBackground);
    buttonBackground.setScale(buttonBackground.getScale() / restartScale);


    restartButton.setScale(restartButton.getScale() * restartScale);
    sf::FloatRect rect = restartButton.getLocalBounds();

    restartButton.setPosition({ 800.0f - rect.width / 2.0f * restartScale, 800.0f - rect.height * 3.0f / 2.0f * restartScale });
    target.draw(restartButton);
    restartButton.setScale(restartButton.getScale() / restartScale);
}

bool LevelSelMenu::getIsOpen() const {
    return isOpen;
}

void LevelSelMenu::setIsOpen(bool isOpen) {
    world.setPaused(isOpen);
    clickable = isOpen;
    for (LevelItem* levelItem : levelItems) {
        levelItem->setClickable(clickable);
    }
    LevelSelMenu::isOpen = isOpen;

    if (isOpen) {
        for (LevelItem* levelItem : levelItems) {
            levelItem->updateMedals();
        }
    }
}

void LevelSelMenu::hitAction(bool& isHit) {
    if(isHit) {
        setIsOpen(false);
        clickSound.play();
    }
}

bool LevelSelMenu::hitScan(const sf::Vector2f& hit) {
    if(!isOpen)
        return false;

    if(buttonBackground.getGlobalBounds().contains(hit)) {
        world.retry();
        setIsOpen(false);
        clickSound.play();
        return true;
    }

    return ClickableUI::hitScan(hit);
}

void LevelSelMenu::hoverAction(bool &isHit) {}

void LevelSelMenu::hover(sf::Vector2f position) {
    if(!isOpen)
        return;
    restartHovered = buttonBackground.getGlobalBounds().contains(position);
}

void LevelSelMenu::populateLevels() {
    for (int i = 0; i<Level::LEVELS.size(); i++) {
        levelItems.push_back(new LevelItem(world, *this, mainOffset, i + 1));
    }
}

const std::vector<LevelItem *> &LevelSelMenu::getLevelItems() const {
    return levelItems;
}
