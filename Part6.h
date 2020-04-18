#pragma once

#include <vector>
#include "VGMap.h"
#include "GBMaps.h"

using namespace std;

class Score {
    public :
        Score();
        int countFinalPoints(VGMap villageBoard);
};

class CountResources {
    public:
        CountResources();
        vector<int> calculResourceMarkers(Map board /*, bool itIsTheShipmentTile*/);
    private:
        int recursiveCountResourceFromSquare(int res, Map::Node* node);
};
