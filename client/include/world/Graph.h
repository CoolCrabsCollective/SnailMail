//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_GRAPH_H
#define LD53_CLIENT_GRAPH_H


#include <map>
#include <unordered_set>
#include "Entity.h"
#include "GraphNode.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Path.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (std::pair<T1, T2> const &v) const {
        return 31 * std::hash<T1>()(v.first) + std::hash<T2>()(v.second);
    }
};

class Graph : public Entity {
    std::vector<GraphNode*> nodes;
    std::unordered_set<std::pair<GraphNode*, GraphNode*>, pair_hash> adjacencySet;
    std::vector<Path> edges;

    mutable sf::Sprite sprite;
public:
    Graph(World& world);

    const sf::Vector2f& getLocation() override;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD53_CLIENT_GRAPH_H
