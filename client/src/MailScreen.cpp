//
// Created by cedric on 4/29/23.
//
//
// Created by Alexander Winter on 2022-03-29.
//

#include "MailScreen.h"
#include "GameAssets.h"
#include "world/World.h"
#include "ui/Sidebar.h"

MailScreen::MailScreen(wiz::Game& game)
        : Screen(game),
            completeMenu(game.getAssets()),
            world(game.getAssets(), completeMenu),
            sidebar(world) {
}

void MailScreen::tick(float delta) {
    world.tick(delta / 1000.f);
}

void MailScreen::render(sf::RenderTarget &target) {
    target.clear(sf::Color::Green);
    target.setView(sf::View({800.0f, 450.0f}, { 1600.0f, 900.0f }));
    target.draw(world);

    target.setView(sf::View({800.0f, 450.0f}, { 1600.0f, 900.0f }));
    target.draw(sidebar);
    target.draw(completeMenu);
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

    world.getEntitySelection()->clickScan(clickVector);
}

void MailScreen::touchBegan(const sf::Event::TouchEvent &touchScreenEvent) {
    sf::Vector2f touchVector = getWindow().mapPixelToCoords(sf::Vector2i(touchScreenEvent.x, touchScreenEvent.y), world.getView());

    world.getEntitySelection()->clickScan(touchVector);
}

void MailScreen::keyReleased(const sf::Event::KeyEvent &keyEvent) {
    if(keyEvent.code == sf::Keyboard::Escape) {
        completeMenu.show(false, 0, 10, 0, 0, 0, 0.0f);
    } else if(keyEvent.code == sf::Keyboard::N) {
        world.loadNextLevel();
    }
}
