//
// Created by william on 29/04/23.
//

#ifndef LD53_CLIENT_PATHSELECTIONARROWUI_H
#define LD53_CLIENT_PATHSELECTIONARROWUI_H

#include <unordered_map>
#include "world/Tickable.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "input/ClickableUI.h"
#include "world/GraphNode.h"

class World;

struct SelectionArrow {
    sf::Vector2f position;
    float angle;
    float scale;
    bool hovered;
    float alpha;
};

class PathSelectionArrowUI {
    mutable sf::Sprite sprite;

    World& world;

    std::unordered_map<GraphNode*, SelectionArrow> arrows;
    GraphNode* currentArrowNode;

    float spawnRadius = 2.0f;

    sf::Vector2f boundingBoxBL;
    sf::Vector2f boundingBoxTR;

public:
    PathSelectionArrowUI(World& world, sf::Color color);

    ~PathSelectionArrowUI() = default;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;

    void tick(float delta, bool moving, GraphNode* currentNode, sf::Color snail_color);

    GraphNode* hitScanAll(const sf::Vector2f& hit);

    bool hitScan(const sf::Vector2f& hit, const sf::Vector2f& entityPos);

    bool hover(const sf::Vector2f& position);
};

#endif //LD53_CLIENT_PATHSELECTIONARROWUI_H
