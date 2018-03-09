//
//  map.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "map.hpp"

Map::Map(){
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++){
            if(i == 0 || i == MAP_HEIGHT - 1) {
                // fill with walls on top and bottom
                m_map[i * MAP_WIDTH + j].setType(1);
            }
            else{
                // fill with empty space
                m_map[i * MAP_WIDTH + j].setType(0);
            }
            m_map[i * MAP_WIDTH + j].setPos(li::itoc(i * MAP_WIDTH + j));
        }
    }
}

int Map::inspectTile(sf::Vector2f pos){
    return m_map[li::ctoi(pos)].getType();
}

int Map::getTileType(int index){
    return m_map[index].getType();
}

void Map::setTileType(int index, int type){
    m_map[index].setType(type);
}

void Map::setTileType(sf::Vector2f coord, int type){
    int index = li::ctoi(coord);
    m_map[index].setType(type);
}
