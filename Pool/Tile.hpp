//
//  Tile.hpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

//#include "Organism.hpp"

#include "Settings.hpp"

class Tile : public sf::Drawable, public sf::Transformable
{
public:
    Tile(int type = 0, float size = CELL_SIZE);
    
    int getType();
    float getSize();
    sf::Vector2f getPos();
    
    void setType(int type);
    void setSize(float size);
    void setPos(sf::Vector2f pos);
    
    //std::vector<Organism> *getLocOrg();
private:
protected:
    // pointer to Organism on this tile if there is one
    //std::vector<Organism> *m_localOrg;
    
    float m_size;
    int m_type;
    sf::RectangleShape m_shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        /*if(m_type == 0)
        {
            return;
        }*/
        target.draw(m_shape, states);
    }
};

#endif /* Tile_hpp */
