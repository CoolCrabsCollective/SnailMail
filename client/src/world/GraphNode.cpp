//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/GraphNode.h"

const std::vector<GraphNode*>& GraphNode::getNeighbors() const {
    return neighbors;
}

const sf::Vector2f& GraphNode::getPosition() const {
    return position;
}
