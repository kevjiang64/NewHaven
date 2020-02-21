//
//  VGMapLoader.h
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-21.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#ifndef VGMapLoader_h
#define VGMapLoader_h
#include "GBMap.h"

 class MapLoader {
 public:
     explicit MapLoader(std::string mapFile = "");
     virtual ~MapLoader();
     MapLoader(const MapLoader& toCopy);
     void operator=(MapLoader& rhs);
     std::string* pMapFile;
     void setMapFile(std::string newMapFile);
     virtual Map* readMapFile();

#endif /* VGMapLoader_h */
