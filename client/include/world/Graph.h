//
// Created by Alexander Winter on 2023-04-29.
//

#ifndef LD53_CLIENT_GRAPH_H
#define LD53_CLIENT_GRAPH_H

#include <map>
#include <unordered_set>
#include <string>
#include "Entity.h"
#include "GraphNode.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Path.h"
#include "SFML/Graphics/VertexArray.hpp"
#include "world/level/Level.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (std::pair<T1, T2> const &v) const {
        return 31 * std::hash<T1>()(v.first) + std::hash<T2>()(v.second);
    }
};

class Graph : public Entity {
    std::vector<GraphNode*> nodes;
    std::unordered_map<std::pair<GraphNode*, GraphNode*>, Path, pair_hash> adjacencyMap;

    mutable sf::Sprite sprite;
    mutable sf::VertexArray lines;

    mutable sf::Text numberLabel;
public:

    constexpr const static float MIN_NODE_DISTANCE = 5.0f;
    constexpr const static float MAX_NODE_PATH_DISTANCE = 2.0f;
    Graph(World& world);

    void generateLevel(Level level);

    const sf::Vector2f& getPosition() const override;

    sf::Vector2f getVisualSize() const override;

    ZOrder getZOrder() const override;

    bool areAdjacent(GraphNode* node1, GraphNode* node2);

    bool hasLeaf();

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    std::vector<GraphNode*>& getNodes();

    bool isConnected();

    Path& getPath(GraphNode *node1, GraphNode *node2);

    const std::unordered_map<std::pair<GraphNode *, GraphNode *>, Path, pair_hash> &getPaths() const;
};


#endif //LD53_CLIENT_GRAPH_H
