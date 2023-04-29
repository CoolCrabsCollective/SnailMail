//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/Graph.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"

Graph::Graph(World& world) : Entity(world), adjacencySet() {
    sprite.setTexture(*world.getAssets().get(GameAssets::WHITE_PIXEL));
}

const sf::Vector2f &Graph::getLocation() {
    return { 0.0f, 0.0f };
}

sf::Vector2f Graph::getVisualSize() const {
    return World::VIEW_SIZE;
}

ZOrder Graph::getZOrder() const {
    return ZOrder::Graph;
}

void Graph::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {

        // edge rendering logic
    }

    for(GraphNode* node : nodes) {
        sprite.setPosition(node->getPosition());
        sprite.setScale({1.0f / 160.0f, 1.0f / 90.0f});
        target.draw(sprite);
    }
}
