//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_GRAPHNODE_H
#define LD53_CLIENT_GRAPHNODE_H


#include <vector>
#include "SFML/System/Vector2.hpp"

class GraphNode {
    std::vector<GraphNode*> neighbors;
    sf::Vector2f position;
public:
    GraphNode() = default;

    [[nodiscard]]
    const std::vector<GraphNode*>& getNeighbors() const;

    [[nodiscard]]
    const sf::Vector2f& getPosition() const;
};


#endif //LD53_CLIENT_GRAPHNODE_H