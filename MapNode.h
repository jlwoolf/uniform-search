//
// Created by jlwoolf on 2/18/21.
//

#ifndef FIND_ROUTE_MAPNODE_H
#define FIND_ROUTE_MAPNODE_H
#include <string>
#include <map>
#include <utility>

struct MapNode {
    std::string name;
    std::map<MapNode*, int> edges;

    explicit MapNode(std::string name) : name(std::move(name)) {}
};


#endif //FIND_ROUTE_MAPNODE_H
