//
//  GBMaps.h
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-10.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#ifndef GBMaps_h
#define GBMaps_h

#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
using std::string;
using std::vector;

class Map {
public:
    class Node;
    
    Map();
    Map(int playerNumber, std::vector<std::vector<std::string>> nodes);
    Map(int& playerNumber, std::vector<Node*> nodes);
    ~Map();
    Map(const Map& toCopy);
    void operator=(Map& rhs);
    bool testConnected();

    inline int* getPlayerNum() const { return playerNum; };
    
    class Node {
    public:
        Node();
        Node(std::string resource);
        Node(const Node& toCopy);
        void operator=(Node& rhs);
        ~Node();
        inline std::vector<Node*>* getAdjNodes() { return pAdjNodes; };
        inline std::string getResourceType() {return *resourceType; };
    private:
        std::vector<Node*>* pAdjNodes;
        std::string* resourceType;
    };
    


  

    Map::Node* addNode(std::string resource);
    void addEdge(int from, int to);
    inline std::vector<Node*>* getMapNodes() { return mapNodes; };

    inline void setMapNodes(std::vector<Node*>* c) { mapNodes = c; }

private:
    int* playerNum;
    std::vector<Node*>* mapNodes;
    static bool testIndividualGraph(std::vector<Node*>* toTest, bool isConnected);
    static void dfs(std::set<std::string>* visitedNodes, Node* nodes, bool connectedTest);
};

#endif /* GBMaps_h */
