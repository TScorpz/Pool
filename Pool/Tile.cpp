//
//  Tile.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(int type, float size)
{
    m_size = size;
    m_type = type;
    m_shape.setSize(sf::Vector2f(size, size));
    setType(type);
    //m_localOrg = NULL;
}

int Tile::getType()
{
    return m_type;
}

float Tile::getSize()
{
    return m_size;
}

sf::Vector2f Tile::getPos()
{
    return m_shape.getPosition();
}

void Tile::setType(int type)
{
    m_type = type;
    
    switch(type)
    {
        case 0: //empty space
        {
            m_shape.setFillColor(sf::Color(60, 60, 60));
            m_shape.setOutlineThickness(0);
            break;
        }
        case 1: //wall
        {
            m_shape.setFillColor(sf::Color(180, 180, 180));
            m_shape.setOutlineThickness(0);
            break;
        }
        case 2:{ // organism
            m_shape.setFillColor(sf::Color(40, 160, 40));
            m_shape.setOutlineColor(sf::Color(180, 180, 180));
            m_shape.setOutlineThickness(-1);
            break;
        }
        case 3: //food
        {
            m_shape.setFillColor(sf::Color(30, 180, 30));
            m_shape.setOutlineThickness(0);
            break;
        }
        case 4:{ // corpse
            m_shape.setFillColor(sf::Color(165, 40, 40));
            m_shape.setOutlineColor(sf::Color(180, 180, 180));
            m_shape.setOutlineThickness(-1);
            break;
        }
    };
}

void Tile::setSize(float size)
{
    m_size = size;
}

void Tile::setPos(sf::Vector2f pos)
{
    m_shape.setPosition(pos);
}

/*std::vector<Organism> *Organism::getLocOrg(){
    return m_localOrg;
}*/
