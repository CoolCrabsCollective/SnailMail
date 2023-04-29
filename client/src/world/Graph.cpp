//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/Graph.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"

Graph::Graph(World& world) : Entity(world), adjacencySet() {
    sprite.setTexture(*world.getAssets().get(GameAssets::GRAPH_VERTEX));

    nodes.push_back(new GraphNode({ 16.0f, 9.0f }));
    nodes.push_back(new GraphNode({ 20.0f, 9.0f }));
    nodes.push_back(new GraphNode({ 5.0f, 12.0f }));
}

const sf::Vector2f &Graph::getLocation() {
    return world.getView().getCenter();
}

sf::Vector2f Graph::getVisualSize() const {
    return world.getView().getSize();
}

ZOrder Graph::getZOrder() const {
    return ZOrder::SnailPath;
}

void Graph::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {

        // edge rendering logic
    }

    for(GraphNode* node : nodes) {
        sprite.setPosition(node->getPosition());
        // sprite.setScale({1.0f / 10.0f, 1.0f / 10.0f});
        target.draw(sprite);
    }
}
