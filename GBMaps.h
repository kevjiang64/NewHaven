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
#include <sstream>
using std::string;
using std::vector;

class Map {
public:
    class Node;
    class Tile;

    Map();
    Map(int playerNumber, std::vector<Node> nodes);
    ~Map();
    Map(const Map& toCopy);
    void operator=(Map& rhs);
    bool testConnected();


    inline int* getPlayerNum() const { return playerNum; };

    class Tile {
    public:
        Tile();
        Tile(Node topLeft, Node topRight, Node bottomRight, Node bottomLeft);
        Tile(const Tile& toCopy);
        void operator=(Tile& rhs);
        ~Tile();
        inline Node* getTopLeft() { return topLeft; }
        inline void setTopLeft(Node* n) { topLeft = n; }
        inline Node* getTopRight() { return topRight; }
        inline void setTopRight(Node* n) { topRight = n; }
        inline Node* getBottomRight() { return bottomRight; }
        inline void setBottomRight(Node* n) { bottomRight = n; }
        inline Node* getBottomLeft() { return bottomLeft; }
        inline void setBottomLeft(Node* n) { bottomLeft = n; }
    private:
        Node* topLeft;
        Node* topRight;
        Node* bottomRight;
        Node* bottomLeft;
    };

    class Node {
    public:
        Node();
        Node(int resource, std::vector<Node> pAdjNode, bool counted);
        Node(const Node& toCopy);
        void operator=(Node& rhs);
        ~Node();
        inline std::vector<Node*>* getAdjNodes() { return pAdjNodes; };
        inline int* getResourceType() { return resourceType; };
        inline void setResourceType(int* resource) { resourceType = resource; }
        inline bool* getCounted() { return isCounted; }
        inline void setCounted(bool* counted) { isCounted = counted; }
    private:
        std::vector<Node*>* pAdjNodes;
        int* resourceType;
        bool* isCounted;
    };



    Map::Node* addNode(int resource, std::vector<Node> pAdjNode, bool counted);
    void addEdge(int from, int to);
    inline std::vector<Node*>* getMapNodes() { return mapNodes; };
    inline void setMapNodes(std::vector<Node*>* nodes) { mapNodes = nodes; }
    void placeHarvestTile(Tile tile);

private:
    int* playerNum;
    std::vector<Node*>* mapNodes;
    static bool testIndividualGraph(std::vector<Node*>* toTest, bool isConnected);
    static void dfs(std::set<int*>* visitedNodes, Node* nodes, bool connectedTest);
};

#endif /* GBMaps_h */
