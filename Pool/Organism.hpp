//
//  Organism.hpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef Organism_hpp
#define Organism_hpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "map.hpp"
#include "Settings.hpp"

class Organism : public sf::Drawable, public sf::Transformable//, protected Map
{
public:
    Organism(Map *map, sf::Vector2f pos = sf::Vector2f(0, 0));
    int getLife();
    int getEnergy();
    int getMinerals();
    int getFitness();
    int getCurrStep();
    sf::Vector2f getPos();
    void reset(Map *map);
    int getBrainCell(int index);
    void setBrainCell(int index, int newCommand);
    void collectEnergy();
    void collectMinerals();
    bool decHealth();
    void incHealth();
    bool tryStepping(Map *map, sf::Vector2f pos);
    void eat(Map *map, sf::Vector2f dir);
    void look(Map *map, sf::Vector2f dir);
    bool isAlive();
    bool isSurrounded(Map *map, sf::Vector2f pos);
    bool createOffspring(std::vector<Organism> *orgVect, Map *map);
    void swap(std::vector<Organism> *orgVect, int index);
    void copy(std::vector<Organism> *orgVect, int destIndex);
    int update(std::vector<Organism> *orgVect, Map *map);
protected:
    int m_currStep;
    bool m_alive;
    int m_life;
    int m_energy;
    int m_minerals;
    int m_brain[BRAIN_SIZE];
    
    sf::RectangleShape body;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(body, states);
    }
};

#endif /* Organism_hpp */
