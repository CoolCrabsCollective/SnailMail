//
// Created by Alexander Winter on 2023-04-29.
//

#include <iostream>
#include "world/Graph.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"
#include "MathUtil.h"

Graph::Graph(World& world) : Entity(world), adjacencySet(), lines(sf::Lines, 2) {
    sprite.setTexture(*world.getAssets().get(GameAssets::GRAPH_VERTEX));

    generateRandom(10);
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
    // Drawing edges/paths
    for (Path p : edges) {
        target.draw(p);
    }

    /*
    for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {
        lines[0].position = pair.first->getPosition();
        lines[0].color = sf::Color::Black;
        lines[1].position = pair.second->getPosition();
        lines[1].color = sf::Color::Black;
        target.draw(lines);
    }
    */

    for(GraphNode* node : nodes) {
        sprite.setPosition(node->getPosition());
        SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
        SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});
        target.draw(sprite);
    }
}

void Graph::generateRandom(uint16_t nodeCount) {
    float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;

    for(uint16_t i = 0; i < nodeCount; i++) {
        float x = static_cast<float>(rand() / (RAND_MAX + 1.0)) * world.getView().getSize().x;
        float y = static_cast<float>(rand() / (RAND_MAX + 1.0)) * world.getView().getSize().y;

        bool cancel = false;

        for(GraphNode* node : nodes) {
            if((node->getPosition() - sf::Vector2f {x, y}).lengthSq() < MathUtil::pow2(MIN_NODE_DISTANCE)) {
                cancel = true;
            }
        }

        if(cancel) {
            i--;
            continue;
        }

        nodes.push_back(new GraphNode({ x, y }));

        minX = std::min(x, minX);
        minY = std::min(y, minY);
        maxX = std::max(x, maxX);
        maxY = std::max(y, maxY);

        std::cout << "X: " << x << ", Y: " << y << std::endl;
    }

    minX -= world.getView().getSize().x * 0.1f;
    minY -= world.getView().getSize().y * 0.1f;

    maxX += world.getView().getSize().x * 0.1f;
    maxY += world.getView().getSize().y * 0.1f;

    float scaleX = world.getView().getSize().x / (maxX - minX);
    float scaleY = world.getView().getSize().y / (maxY - minY);

    for(GraphNode* node : nodes) {
        node->setPosition((node->getPosition() - sf::Vector2f { minX, minY }).cwiseMul({ scaleX, scaleY }));
    }

    int it = 0;
    do {
        it++;
        int node1Idx = rand() % nodeCount;
        int node2Idx = rand() % nodeCount;

        if(node1Idx == node2Idx) {
            continue;
        }

        GraphNode* node1 = nodes[node1Idx];
        GraphNode* node2 = nodes[node2Idx];

        if(areAdjacent(node1, node2)) {
            continue;
        }

        bool cancel = false;
        for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {
            if(MathUtil::segmentsIntersect((pair.first->getPosition() + pair.second->getPosition() * 0.1f) / 1.1f,
                                           (pair.second->getPosition() + pair.first->getPosition() * 0.1f) / 1.1f,
                                           (node1->getPosition() + node2->getPosition() * 0.1f) / 1.1f,
                                           (node2->getPosition() + node2->getPosition() * 0.1f) / 1.1f)) {
                cancel = true;
            }
        }
        if(cancel)
            continue;

        node1->addNeighbor(node2);
        node2->addNeighbor(node1);

        if(node1 < node2)
            adjacencySet.insert(std::pair(node1, node2));
        else
            adjacencySet.insert(std::pair(node2, node1));
    } while((hasLeaf() || !isConnected()) && it < 500);


    for(const std::pair<GraphNode*, GraphNode*>& pair : adjacencySet) {
        edges.emplace_back(*world.getAssets().get(GameAssets::PATH),
                             pair.first->getPosition(),
                             pair.second->getPosition(),
                             world.getView());
    }
}

bool Graph::areAdjacent(GraphNode* node1, GraphNode* node2) {
    return node1 < node2
        ? adjacencySet.contains(std::pair(node1, node2))
        : adjacencySet.contains(std::pair(node2, node1));
}

std::vector<GraphNode*>& Graph::getNodes() {
    return nodes;
}

bool Graph::hasLeaf() {
    for(GraphNode* node : nodes) {
        if(node->getNeighbors().size() <= 1)
            return true;
    }
    return false;
}

bool Graph::isConnected() {
    if(nodes.empty())
        return true;

    std::unordered_set<GraphNode*> visited;
    std::vector<GraphNode*> toProcess { nodes[0] };

    while(!toProcess.empty()) {
        GraphNode* node = toProcess[toProcess.size() - 1];
        toProcess.erase(toProcess.end() - 1);
        visited.insert(node);
        for(GraphNode* neighbor : node->getNeighbors()) {
            if(!visited.contains(neighbor)) {
                toProcess.push_back(neighbor);
            }
        }
    }

    return visited.size() == nodes.size();
}
