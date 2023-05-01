//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_MAILSCREEN_H
#define LD53_CLIENT_MAILSCREEN_H
//
// Created by Alexander Winter on 2022-03-29.
//

#include "WIZ/game/Screen.h"
#include "WIZ/game/WindowListener.h"
#include "SFML/Graphics/Sprite.hpp"
#include "world/World.h"
#include "world/Path.h"
#include "ui/Sidebar.h"
#include "ui/LevelCompleteMenu.h"
#include "ui/LevelIndicator.h"
#include "ui/LevelSelMenu.h"
#include "ScoreSaver.h"

class MailScreen : public wiz::Screen, public wiz::WindowListener, public wiz::InputListener {
    std::string name = "SnailMail";
    World world;
    LevelCompleteMenu completeMenu;
    Sidebar sidebar;
    LevelIndicator levelIndicator;
    LevelSelMenu levelSelMenu;
    sf::View uiView;

    std::vector<ClickableUI*> clickables;

    ScoreSaver scoreSaver;

public:
    MailScreen(wiz::Game& game);

    void tick(float delta) override;

    void render(sf::RenderTarget& target) override;

    void show() override;

    void hide() override;

    const std::string& getName() const override;

    void windowClosed() override;

    void mouseMoved(const sf::Event::MouseMoveEvent &mouseMoveEvent) override;

    void mouseButtonReleased(const sf::Event::MouseButtonEvent &mouseButtonEvent) override;

    void touchBegan(const sf::Event::TouchEvent &touchScreenEvent) override;

    void keyReleased(const sf::Event::KeyEvent &keyEvent) override;

    LevelCompleteMenu& getCompleteMenu();

    ScoreSaver& getScoreSaver();
};

#endif //LD53_CLIENT_MAILSCREEN_H
