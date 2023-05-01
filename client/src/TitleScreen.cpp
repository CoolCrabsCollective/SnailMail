//
// Created by Alexander Winter on 2022-03-12.
//

#include "TitleScreen.h"

#include <memory>
#include "GameAssets.h"
#include "SFML/Window/Touch.hpp"
#include "MailScreen.h"

TitleScreen::TitleScreen(wiz::Game& game)
	: Screen(game),
        snailysSong(*game.getAssets().get(GameAssets::SNAILYS_SONG)),
        click() {
    background.setTexture(*game.getAssets().get(GameAssets::TITLE_SCREEN_BACKGROUND));

    subtext.setFont(*game.getAssets().get(GameAssets::THE_RIGHT_FONT));
    subtext.setFillColor(sf::Color(34, 32, 52));
    subtext.setCharacterSize(40);
    subtext.setString("(Click to continue)");
    sf::FloatRect subtextRect = subtext.getLocalBounds();
    subtext.setOrigin({subtextRect.left + subtextRect.width/2.0f, subtextRect.top + subtextRect.height/2.0f});
    click.setBuffer(*game.getAssets().get(GameAssets::CLICK));
}

void TitleScreen::tick(float delta) {
	sf::Vector2f vec(getGame().getWindow().getView().getSize());
    musicDelay += delta;

    if(musicDelay > 0.5f && snailysSong.getStatus() != sf::SoundSource::Playing)
        snailysSong.play();

	message.setPosition(vec / 2.0f);
    subtext.setPosition(vec / 2.0f + sf::Vector2f(0, 320));

	vec.x /= static_cast<float>(background.getTextureRect().getSize().x);
	vec.y /= static_cast<float>(background.getTextureRect().getSize().y);
	background.setScale(vec);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i pos = sf::Mouse::getPosition(getWindow());

        if(pos.x >= 0 && pos.y >= 0 && pos.x <= getWindow().getSize().x && pos.y <= getWindow().getSize().y) {
            click.play();
            getGame().setScreen(std::make_shared<MailScreen>(getGame()));
            return;
        }
    }

    if(sf::Touch::isDown(1)) {
        sf::Vector2i pos = sf::Touch::getPosition(1, getWindow());

        if(pos.x >= 0 && pos.y >= 0 && pos.x <= getWindow().getSize().x && pos.y <= getWindow().getSize().y) {
            click.play();
            getGame().setScreen(std::make_shared<MailScreen>(getGame()));
            return;
        }
    }
}

void TitleScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.draw(background);
	target.draw(message);
    target.draw(subtext);
}

void TitleScreen::show() {
	getGame().addWindowListener(this);
    snailysSong.setLoop(true);
    snailysSong.setVolume(75);
}

void TitleScreen::hide() {
	getGame().removeWindowListener(this);
    snailysSong.stop();
}

const std::string& TitleScreen::getName() const {
	return name;
}

void TitleScreen::windowClosed() {
	getGame().getWindow().close();
}