//
// Created by Alexander Winter on 2022-03-12.
//

#include "TitleScreen.h"
#include "GameAssets.h"
#include "SFML/Window/Touch.hpp"
#include "MailScreen.h"

TitleScreen::TitleScreen(wiz::Game& game)
	: snailysSong(*game.getAssets().get(GameAssets::SNAILYS_SONG)), Screen(game) {
    background.setTexture(*game.getAssets().get(GameAssets::TITLE_SCREEN_BACKGROUND));

    subtext.setFont(*game.getAssets().get(GameAssets::THE_RIGHT_FONT));
    subtext.setFillColor(sf::Color(34, 32, 52));
    subtext.setCharacterSize(40);
    subtext.setString("(Click to continue)");
    sf::FloatRect subtextRect = subtext.getLocalBounds();
    subtext.setOrigin({subtextRect.left + subtextRect.width/2.0f, subtextRect.top + subtextRect.height/2.0f});

    snailysSong.setLoop(true);
    snailysSong.setVolume(50);
    snailysSong.play();
}

void TitleScreen::tick(float delta) {
	sf::Vector2f vec(getGame().getWindow().getView().getSize());

	message.setPosition(vec / 2.0f);
    subtext.setPosition(vec / 2.0f + sf::Vector2f(0, 320));

	vec.x /= static_cast<float>(background.getTextureRect().getSize().x);
	vec.y /= static_cast<float>(background.getTextureRect().getSize().y);
	background.setScale(vec);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)
	   || sf::Joystick::isButtonPressed(0, 3))
	{
		getGame().setScreen(std::shared_ptr<MailScreen>(new MailScreen(getGame())));
		return;
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Touch::isDown(1))
		getGame().setScreen(std::shared_ptr<MailScreen>(new MailScreen(getGame())));
}

void TitleScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.draw(background);
	target.draw(message);
    target.draw(subtext);
}

void TitleScreen::show() {
	getGame().addWindowListener(this);

	int i;
	for(i = 0; true; i++) {
		if(!sf::Joystick::isConnected(i))
			break;

		sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
		unsigned int buttonCount = sf::Joystick::getButtonCount(i);

		std::stringstream ss;

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::X))
			ss << "X";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::Y))
			ss << "Y";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::U))
			ss << "U";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::V))
			ss << "V";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::Z))
			ss << "Z";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::R))
			ss << "R";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::PovX))
			ss << "pX";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::PovY))
			ss << "pY";

		getLogger().info("Found controller, Name: " + id.name +
					 ", VendorID: " + std::to_string(id.vendorId) +
					 ", ProductID: " + std::to_string(id.productId) +
					 ", ButtonCount: " + std::to_string(buttonCount) +
					 ", Axis: " + ss.str());
	}
	getLogger().info("Found " + std::to_string(i) + " controllers");
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