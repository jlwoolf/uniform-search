#include <iostream>
#include <list>
#include <fstream>

#include "MapNode.h"
#include "TreeNode.h"

//used to check for inifinite distance. Value represents if all nodes
//were in a straight line and the start and end were on opposite ends of the line.
int maxLength = 0;

//used to sort the queue.
bool compareFullWeight(const TreeNode* node1, const TreeNode* node2) {
    return node1->fullWeight < node2->fullWeight;
}

//reads the input file and creates a map with each node name linking
//to a pointer to a MapNode structure that contains information about connected nodes.
std::map<std::string, MapNode*> readInput(std::string filename) {
    std::ifstream fin(filename);
    if(fin.fail()) {
        std::cerr << "Error: file not found" << std::endl;
        exit(-1);
    }

    std::map<std::string, MapNode*> diagraph;
    std::string node1, node2; int weight;
    while(fin >> node1 >> node2 >> weight) {
        maxLength += weight;
        if(diagraph[node1] == nullptr)
            diagraph[node1] = new MapNode(node1);
        if(diagraph[node2] == nullptr)
            diagraph[node2] = new MapNode(node2);
        diagraph[node1]->edges[diagraph[node2]] = weight;
        diagraph[node2]->edges[diagraph[node1]] = weight;
    }

    return diagraph;
}

//used to print the route. Since the program finishes at the goal, printRoute()
//backtracks to up the list of parent nodes until the initial node, constructing
//a string that will properly print an output.
void printRoute(TreeNode* end) {
    std::string route;
    auto* trace = end;

    while(trace->parent != nullptr) {
        route = trace->parent->name + " to " + trace->name + ", " + std::to_string(trace->weight) + " km\n" + route;
        trace = trace->parent;
    }

    if(route.empty()) {
        route = end->name + " to " + end->name + ", 0 km\n";
    }

    std::cout << route;
}


int main(int argc, char* argv[]) {
    if(argc != 4) {
        std::cerr << "Error: invalid input, should be ./find_route input_file origin_city destination_city" << std::endl;
        exit(-1);
    }
    //reads the input file into the diagraph along with store arguments as values
    std::map<std::string, MapNode*> diagraph = readInput(argv[1]);
    std::string start = argv[2], goal = argv[3];

    if(diagraph.find(start) == diagraph.end()) {
        std::cerr << "Error: origin city is not contained in input file" << std::endl;
        exit(-1);
    } else if(diagraph.find(goal) == diagraph.end()) {
        std::cerr << "Error: destination city is not contained in input file" << std::endl;
        exit(-1);
    }

    //initializes the initial node of the uniform-search tree and the
    //queue used to search
    auto* initial = new TreeNode(start);
    std::list<TreeNode*> queue;
    queue.push_back(initial);

    while(true) {
        //two lines used to "pop" as a linked list was used for easy sorting
        TreeNode* currentNode = queue.front();
        queue.erase(queue.begin());

        //checks for goal condition, and if reached, prints distance and route
        if(currentNode->name == goal) {
            std::cout << "distance: " << currentNode->fullWeight << " km" << std::endl;
            std::cout << "route: " << std::endl;
            printRoute(currentNode);
            break;
        //checks if goal condition is unreachable, printing infinite distance and no route
        } else if(currentNode->fullWeight >= maxLength) {
            std::cout << "distance: infinity" << std::endl;
            std::cout << "route: " << std::endl << "none" << std::endl;
            break;
        }

        //for each connected node to the current node...
        for(auto edge : diagraph[currentNode->name]->edges) {
            auto* childNode = new TreeNode(currentNode, edge.first->name);
            childNode->weight = edge.second; childNode->fullWeight = currentNode->fullWeight + edge.second;

            bool contains = false;
            for(auto& node : queue) {
                //checks if node is already in the queue to avoid repetition
                if(childNode->name == node->name) {
                    contains = true;
                    //checks if a node of shorter distance to the same state is in the queue and replaces
                    //the one with the longer distance. This is used to prevent flooding of queue when potential
                    //looping occurs in an unreachable state.
                    if(childNode->fullWeight < node->fullWeight)
                        node = childNode;
                }
            }

            //if the node is not already in the queue, add it.
            if(!contains)
                queue.push_back(childNode);
            //sort the queue
            queue.sort(compareFullWeight);
        }
    }
}
