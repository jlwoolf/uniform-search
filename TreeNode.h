//
// Created by jlwoolf on 2/18/21.
//

#ifndef FIND_ROUTE_TREENODE_H
#define FIND_ROUTE_TREENODE_H
#include <string>
#include <utility>

struct TreeNode {
    TreeNode* parent = nullptr;
    std::string name;
    int fullWeight = 0;
    int weight = 0;

    explicit TreeNode(std::string name) : name(std::move(name)) {}
    TreeNode(TreeNode* parent, std::string name) : parent(parent), name(std::move(name)) {}
};


#endif //FIND_ROUTE_TREENODE_H
