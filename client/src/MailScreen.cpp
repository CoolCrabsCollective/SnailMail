//
// Created by cedric on 4/29/23.
//
//
// Created by Alexander Winter on 2022-03-29.
//

#include <iostream>
#include "MailScreen.h"
#include "GameAssets.h"
#include "world/World.h"
#include "ui/Sidebar.h"

MailScreen::MailScreen(wiz::Game& game)
        : Screen(game),
            world(game.getAssets(), *this),
            completeMenu(world),
            sidebar(world),
            levelSelMenu(world),
            levelIndicator(world, levelSelMenu),
            uiView({800.0f, 450.0f}, { 1600.0f, 900.0f }),
            scoreSaver("scores/") {
    clickables.push_back(dynamic_cast<ClickableUI*>(&levelIndicator));
    clickables.push_back(dynamic_cast<ClickableUI*>(&levelSelMenu));
    for (LevelItem* itemLevel : levelSelMenu.getLevelItems()) {
        clickables.push_back(dynamic_cast<ClickableUI*>(itemLevel));
    }
}

void MailScreen::tick(float delta) {
    world.setPaused(levelSelMenu.getIsOpen());
    levelIndicator.setClickable(!completeMenu.isVisible());

    world.tick(delta / 1000.0f);
    completeMenu.tick(delta / 1000.0f);
}

void MailScreen::render(sf::RenderTarget &target) {
    target.clear(sf::Color::Green);
    target.draw(world);

    target.setView(uiView);
    target.draw(sidebar);
    target.draw(levelIndicator);

    // Menus
    target.draw(completeMenu);
    target.draw(levelSelMenu);
}

const std::string &MailScreen::getName() const {
    return name;
}

void MailScreen::windowClosed() {
    getGame().getWindow().close();
}

void MailScreen::show() {
    getGame().addWindowListener(this);
    getGame().addInputListener(this);
}

void MailScreen::hide() {
    getGame().removeWindowListener(this);
    getGame().removeInputListener(this);
}

void MailScreen::mouseButtonReleased(const sf::Event::MouseButtonEvent &mouseButtonEvent) {
    sf::Vector2f clickVector = getWindow().mapPixelToCoords(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y),
                                                            world.getView());


    std::cout << clickVector.x << ", " << clickVector.y << std::endl;
    for (Snail* snail : world.getSnails()) {
        GraphNode* hitScan = snail->hitScan(clickVector);
        if (hitScan) {
            break;
        }
    }

    clickVector = getWindow().mapPixelToCoords(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y),

                                                            uiView);

    completeMenu.click(clickVector);

    for (ClickableUI* clickable : clickables) {
        if (clickable->hitScan(clickVector)) {
            break;
        }
    }
}

void MailScreen::mouseMoved(const sf::Event::MouseMoveEvent &mouseMoveEvent) {

    sf::Vector2f clickVector = getWindow().mapPixelToCoords(sf::Vector2i(mouseMoveEvent.x, mouseMoveEvent.y),
                                               uiView);
    completeMenu.hover(clickVector);
}

void MailScreen::touchBegan(const sf::Event::TouchEvent &touchScreenEvent) {
    sf::Vector2f touchVector = getWindow().mapPixelToCoords(sf::Vector2i(touchScreenEvent.x, touchScreenEvent.y), world.getView());

    for (Snail* snail : world.getSnails()) {
        GraphNode* hitScan = snail->hitScan(touchVector);
        if (hitScan) {
            break;
        }
    }

    touchVector = getWindow().mapPixelToCoords(sf::Vector2i(touchScreenEvent.x, touchScreenEvent.y),
                                               uiView);
    completeMenu.click(touchVector);

    for (ClickableUI* clickable : clickables) {
        if (clickable->hitScan(touchVector)) {
            break;
        }
    }
}

void MailScreen::keyReleased(const sf::Event::KeyEvent &keyEvent) {
    if(keyEvent.code == sf::Keyboard::N) {
        world.loadNextLevel();
    } else if(keyEvent.code == sf::Keyboard::R) {
        world.retry();
    }
}

LevelCompleteMenu& MailScreen::getCompleteMenu() {
    return completeMenu;
}

ScoreSaver& MailScreen::getScoreSaver() {
    return scoreSaver;
}
