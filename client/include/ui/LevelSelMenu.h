//
// Created by william on 30/04/23.
//

#ifndef LD53_CLIENT_LEVELSELMENU_H
#define LD53_CLIENT_LEVELSELMENU_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "input/ClickableUI.h"
#include "LevelItem.h"
#include "SFML/Audio/Sound.hpp"
#include "world/Tickable.h"

class World;

class LevelSelMenu : public sf::Drawable, public ClickableUI, public Tickable {
    mutable sf::Sprite backgroundSprite;
    mutable sf::Text label;

    mutable sf::Sprite exitButtonSprite;

    mutable sf::Sprite buttonBackground;
    mutable sf::Text restartButton;
    float restartScale;
    bool restartHovered;

    sf::Vector2f mainOffset = {800.0f, 450.0f};
    sf::Vector2f labelOffset = {-40.f, -210.f};
    sf::Vector2f buttonOffset = {310.f, -180.f};

    sf::Vector2f mainSize = {800.f, 480.f};

    World& world;

    bool isOpen = false;

    std::vector<LevelItem*> levelItems;

public:
    sf::Sound clickSound;
    LevelSelMenu(World &world);

    void tick(float delta) override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    bool getIsOpen() const;

    void setIsOpen(bool isOpen);

    void hitAction(bool& isHit) override;

    void populateLevels();

    const std::vector<LevelItem *> &getLevelItems() const;

    ~LevelSelMenu() = default;

    void hoverAction(bool& isHit) override;

    void hover(sf::Vector2f position);

    bool hitScan(const sf::Vector2f &hit) override;
};

#endif //LD53_CLIENT_LEVELSELMENU_H
