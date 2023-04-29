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
#include "Box2D/Dynamics/b2World.h"
#include "SFML/Graphics/Sprite.hpp"
#include "world/World.h"
#include "world/Path.h"

class MailScreen : public wiz::Screen, public wiz::WindowListener {
    std::string name = "SnailMail";
    World world;

public:
    MailScreen(wiz::Game& game);

    void tick(float delta) override;

    void render(sf::RenderTarget& target) override;

    void show() override;

    void hide() override;

    const std::string& getName() const override;

    void windowClosed() override;
};

#endif //LD53_CLIENT_MAILSCREEN_H
