//
// Created by william on 29/04/23.
//

#include "input/EntitySelection.h"

EntitySelection::EntitySelection(World &world) : world(world) {
}

void EntitySelection::clickScan(sf::Vector2f clickPos) {
    const std::map<ZOrder, std::vector<Entity*>> zOrderMap = world.getZOrderMap();

//    for(int i = 0; i < ZOrder::ENUM_LENGTH; i++) {
//        for(Entity* entity: zOrderMap[static_cast<ZOrder>(i)]) {
//
//        }
//    }
}