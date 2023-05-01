//
// Created by Alexander Winter on 2023-04-29.
//

#include "world/Graph.h"
#include "world/World.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpriteUtil.h"
#include "MathUtil.h"

Graph::Graph(World& world) : Entity(world), adjacencyMap(), lines(sf::Lines, 2) {
    sprite.setTexture(*world.getAssets().get(GameAssets::GRAPH_VERTEX));
}

const sf::Vector2f& Graph::getPosition() const {
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
    for(const auto& entry : adjacencyMap) {
        target.draw(entry.second);
    }

    // Drawing nodes
    for(GraphNode* node : nodes) {
        sprite.setPosition(node->getPosition());
        SpriteUtil::setSpriteSize(sprite, sf::Vector2f{2., 2.});
        SpriteUtil::setSpriteOrigin(sprite, sf::Vector2f{0.5f, 0.5f});
        target.draw(sprite);
    }
}

void Graph::generateLevel(Level level) {
    for(GraphNode* node : nodes)
        delete node;

    nodes.clear();
    adjacencyMap.clear();

    if(level.custom)
    {
        for(const std::pair<float, float>& pair : level.nodes)
        {
            nodes.push_back(new GraphNode({ pair.first, pair.second }));
        }

        for(const std::pair<int, int>& pair : level.adjacency_list)
        {
            GraphNode* p1 = nodes[pair.first];
            GraphNode* p2 = nodes[pair.second];

            if(p2 < p1)
            {
                GraphNode* tmp = p1;
                p1 = p2;
                p2 = tmp;
            }

            std::pair<GraphNode*, GraphNode*> graph_pair{p1, p2};
            adjacencyMap.emplace(graph_pair, Path(world.getAssets(),graph_pair.first, graph_pair.second));
        }
        level.nodeCount = nodes.size();
        return;
    }

    GRand random;

    if(level.seeded)
        random.seed(level.seed);

    float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;

    for(uint16_t i = 0; i < level.nodeCount; i++) {
        float x = static_cast<float>(random.d() * world.getView().getSize().x);
        float y = static_cast<float>(random.d() * world.getView().getSize().y);

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
    }

    minX -= world.getView().getSize().x * 0.1f;
    minY -= world.getView().getSize().y * 0.1f;

    maxX += world.getView().getSize().x * 0.4f;
    maxY += world.getView().getSize().y * 0.1f;

    float scaleX = world.getView().getSize().x / (maxX - minX);
    float scaleY = world.getView().getSize().y / (maxY - minY);

    for(GraphNode* node : nodes) {
        node->setPosition((node->getPosition() - sf::Vector2f { minX, minY }).cwiseMul({ scaleX, scaleY }));
    }

    int it = 0;
    do {
        it++;
        int node1Idx = random.i(nodes.size());
        int node2Idx = random.i(nodes.size());

        if(node1Idx == node2Idx) {
            continue;
        }

        GraphNode* node1 = nodes[node1Idx];
        GraphNode* node2 = nodes[node2Idx];

        if(areAdjacent(node1, node2)) {
            continue;
        }

        bool cancel = false;
        for(const auto& entry : adjacencyMap) {
            const std::pair<GraphNode*, GraphNode*>& pair = entry.first;
            if(MathUtil::segmentsIntersect((pair.first->getPosition() * 0.9f + pair.second->getPosition() * 0.1f),
                                           (pair.second->getPosition() * 0.9f + pair.first->getPosition() * 0.1f),
                                           (node1->getPosition() * 0.9f + node2->getPosition() * 0.1f),
                                           (node2->getPosition() * 0.9f + node1->getPosition() * 0.1f))) {
                cancel = true;
                break;
            }
        }

        if(cancel)
            continue;

        for(GraphNode* node : nodes) {
            if(node == node1 || node == node2)
                continue;

            if(MathUtil::pointSegmentDistanceSquared(node->getPosition(),
                                                     node1->getPosition(),
                                                     node2->getPosition()) < MathUtil::pow2(MAX_NODE_PATH_DISTANCE)) {
                cancel = true;
                break;
            }
        }

        if(cancel)
            continue;

        node1->addNeighbor(node2);
        node2->addNeighbor(node1);

        std::pair<GraphNode*, GraphNode*> final_pair;
        if(node1 < node2)
            final_pair = std::pair(node1, node2);
        else
            final_pair = std::pair(node2, node1);

        adjacencyMap.emplace(final_pair, Path(world.getAssets(),final_pair.first, final_pair.second));
    } while(it < 500000);

    if(!isConnected() || hasLeaf()) {
        if(level.seeded)
            level.seed++; // deterministically retry with another seed
        generateLevel(level);
        return;
    }
}

bool Graph::areAdjacent(GraphNode* node1, GraphNode* node2) {
    return node1 < node2
        ? adjacencyMap.contains(std::pair(node1, node2))
        : adjacencyMap.contains(std::pair(node2, node1));
}

Path& Graph::getPath(GraphNode *node1, GraphNode *node2) {
    return node1 < node2
           ? adjacencyMap.at(std::pair(node1, node2))
           : adjacencyMap.at(std::pair(node2, node1));
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

const std::unordered_map<std::pair<GraphNode *, GraphNode *>, Path, pair_hash> &Graph::getPaths() const {
    return adjacencyMap;
}
