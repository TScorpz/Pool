//
//  map.hpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "functions.hpp"
#include "Settings.hpp"

class Map : public sf::Drawable, public sf::Transformable
{
public:
    Map();
    int inspectTile(sf::Vector2f pos);
    int getTileType(int index);
    void setTileType(int index, int type);
    void setTileType(sf::Vector2f coord, int type);
protected:
    Tile m_map[MAP_WIDTH * MAP_HEIGHT];
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        for(int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
        {
            target.draw(m_map[i], states);
        }
    }
};

#endif /* map_hpp */
