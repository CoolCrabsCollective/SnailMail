//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/Graph.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"

Graph::Graph(World& world) : Entity(world), adjacencySet() {
    sprite.setTexture(*world.getAssets().get(GameAssets::WHITE_PIXEL));

    GraphNode* node1 = new GraphNode({ 16.0f, 9.0f });
    GraphNode* node2 = new GraphNode({ 20.0f, 9.0f });
    GraphNode* node3 = new GraphNode({ 5.0f, 12.0f });

    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);

    adjacencySet.insert({node1, node2});
    //adjacencySet.insert({node2, node3});

    for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {
        edges.push_back(Path(*world.getAssets().get(GameAssets::PATH), pair.first->getPosition(), pair.second->getPosition(), world.getView()));
    }
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
    // Drawing edges/paths
    for (Path p : edges) {
        target.draw(p);
    }

    for(GraphNode* node : nodes) {
        sprite.setPosition(node->getPosition());
        // sprite.setScale({1.0f / 10.0f, 1.0f / 10.0f});
        target.draw(sprite);
    }
}
