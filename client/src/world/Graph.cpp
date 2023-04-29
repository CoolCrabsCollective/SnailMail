//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/Graph.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"


Graph::Graph(World& world) : Entity(world), adjacencySet(), lines(sf::Lines, 2) {
    sprite.setTexture(*world.getAssets().get(GameAssets::GRAPH_VERTEX));
    GraphNode* node1 = new GraphNode({ 16.0f, 9.0f });
    GraphNode* node2 = new GraphNode({ 20.0f, 9.0f });
    GraphNode* node3 = new GraphNode({ 5.0f, 12.0f });
    node1->addNeighbor(node3);
    node2->addNeighbor(node3);
    node3->addNeighbor(node1);
    node3->addNeighbor(node2);

    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);

    adjacencySet.insert(std::pair(node1, node3));
    adjacencySet.insert(std::pair(node2, node3));
}

const sf::Vector2f &Graph::getLocation() {
    return world.getView().getCenter();
}

sf::Vector2f Graph::getVisualSize() const {
    return world.getView().getSize();
}

ZOrder Graph::getZOrder() const {
    return ZOrder::Path_ZOrder;
}

void Graph::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {
        lines[0].position = pair.first->getPosition();
        lines[0].color = sf::Color::Black;
        lines[1].position = pair.second->getPosition();
        lines[1].color = sf::Color::Black;
        target.draw(lines);
    }

    for(GraphNode* node : nodes) {
        sprite.setPosition(node->getPosition());
        SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
        SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});
        target.draw(sprite);
    }
}

std::vector<GraphNode *> & Graph::getNodes() {
    return nodes;
}
