//
// Created by william on 29/04/23.
//

#include "input/EntitySelection.h"
#include "input/Clickable.h"
#include "world/World.h"

EntitySelection::EntitySelection(World &world) : world(world) {
}

GraphNode* EntitySelection::clickScan(sf::Vector2f clickPos) {
    const std::map<ZOrder, std::vector<Entity*>> zOrderMap = world.getZOrderMap();
    Clickable* clickable = nullptr;

    // Iterate entities in Z order
//    for(int i = ENUM_LENGTH - 1; i >= 0; i--) {
//        for(Entity* entity: zOrderMap.at(static_cast<ZOrder>(i))) {
//            clickable = dynamic_cast<Clickable*>(entity);
//            if (clickable && clickable->hitScan(clickPos, entity->getLocation())) {
//                selected = entity;
//                return entity;
//            }
//        }
//    }

    // Iterate graph nodes
//    for (GraphNode* entity : world.getGraph()->getNodes()) {
//        if (entity->hitScan(clickPos)) {
//            selected = entity;
//            return entity;
//        }
//    }

    selected = nullptr;
    return nullptr;
}

GraphNode *EntitySelection::getSelected() const {
    return selected;
}

void EntitySelection::setSelected(GraphNode *selected) {
    EntitySelection::selected = selected;
}
