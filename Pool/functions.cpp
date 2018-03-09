//
//  functions.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "functions.hpp"

int li::ctoi(sf::Vector2f pos)
{
    int x = pos.x / CELL_SIZE,
        y = pos.y / CELL_SIZE;
    
    return x + y * MAP_WIDTH;
}

sf::Vector2f li::itoc(int index)
{
    int y = index / MAP_WIDTH,
        x = index % MAP_WIDTH;
    
    return sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
}

void li::center_out(sf::Text &value, sf::RectangleShape &container)
{
    sf::FloatRect textRect = value.getLocalBounds();
    value.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
    value.setPosition(sf::Vector2f(container.getSize().x / 2.0f + container.getPosition().x, container.getSize().y / 2.0f + container.getPosition().y));
}

float li::fixCoord(float X){
    if(X >= MAP_WIDTH * CELL_SIZE){
        X = 0;
    }
    else if(X < 0){
        X = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
    }
    
    return X;
}

int li::getRowNum(sf::Vector2f pos){
    return pos.y / MAP_WIDTH;
}

int li::getRowNum(float posY){
    return posY / MAP_WIDTH;
}
