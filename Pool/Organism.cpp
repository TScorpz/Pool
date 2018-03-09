//
//  Organism.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Organism.hpp"
#include "functions.hpp"

Organism::Organism(Map *map, sf::Vector2f pos)
{
    body.setPosition(pos);
    //body.setPosition(sf::Vector2f(CELL_SIZE * 15, CELL_SIZE * 8));
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    //int color = rand() % 150 + 100;
    body.setFillColor(sf::Color(0, 100, 0));
    body.setOutlineColor(sf::Color(180, 180, 180));
    body.setOutlineThickness(-1);
    //map->setTileType(sf::Vector2f(CELL_SIZE * 15, CELL_SIZE * 8), 2);
    
    m_alive = true;
    m_life = 50;
    m_currStep = 0;
    m_minerals = 0;
    m_energy = 0;
    
    for(int i = 0; i < BRAIN_SIZE; i++)
    {
        //m_brain[i] = rand() % 32;
        m_brain[i] = 24;
        //std::cout << m_brain[i] << " ";
    }
}

int Organism::getLife()
{
    return m_life;
}

int Organism::getEnergy(){
    return m_energy;
}

int Organism::getMinerals(){
    return m_minerals;
}

int Organism::getCurrStep(){
    return m_currStep;
}

sf::Vector2f Organism::getPos()
{
    return body.getPosition();
}

void Organism::reset(Map *map){
    m_alive = true;
    m_life = 50;
    m_currStep = 0;
    m_energy = 0;
    m_minerals = 0;
}

int Organism::getBrainCell(int index)
{
    return m_brain[index];
}

void Organism::setBrainCell(int index, int newCommand){
    m_brain[index] = newCommand;
}

void Organism::collectEnergy(){
    float posY = this->body.getPosition().y;
    int energyGain = (10 - li::getRowNum(posY));
    if(energyGain < 0){
        energyGain = 0;
    }
    this->m_energy += energyGain;
}

void Organism::collectMinerals(){
    /*float posY = this->body.getPosition().y;
    int energyGain = (10 - li::getRowNum(posY));
    if(energyGain < 0){
        energyGain = 0;
    }
    this->m_energy += energyGain;*/
}

bool Organism::decHealth()
{
    m_life -= 5;
    if(m_life < 1)
    {
        std::cout << "I have ran out of life. Life - " << this->m_life << "\n";
        m_alive = false;
        return true;
    }
    else {
        return false;
    }
}

void Organism::incHealth()
{
    m_life += 10;
    //add max health
}

bool Organism::tryStepping(Map *map, sf::Vector2f pos)
{
    int tileType = map->inspectTile(pos);
    int stepInc = 0;
    switch (tileType) {
        //if empty then go
        case 0:
        {
            map->setTileType(pos, 2);
            map->setTileType(body.getPosition(), 0);
            body.setPosition(pos);
            stepInc = 0;
            if(decHealth()){
                return true;
            }
            break;
        }
        //if wall then incr m_currStep by 2
        case 1:
        {
            stepInc = 1;
            //decHealth();
            break;
        }
        //if bot then incr m_currStep by 3
        case 2:
        {
            stepInc = 2;
            //decHealth();
            break;
        }
        //if food then incr m_currStep by 4
        case 3:
        {
            stepInc = 3;
            //decHealth();
            break;
        }
        //if corpse then incr m_currStep by 5
        case 4:
        {
            stepInc = 4;
            //decHealth();
            break;
        }
    }
    m_currStep += m_brain[(m_currStep + stepInc) % BRAIN_SIZE];
    m_currStep %= BRAIN_SIZE;
    return false;
}

void Organism::eat(Map *map, sf::Vector2f dir)
{
    int tileType = map->inspectTile(dir);
    int stepInc = 0;
    switch (tileType) {
        //if empty then incr m_currStep by 1
        case 0:
        {
            stepInc = 4;
            break;
        }
        //if wall then incr m_currStep by 2
        case 1:{
            stepInc = 3;
            break;
        }
        //if bot then incr m_currStep by 3
        case 2:
        {
            //incHealth();
            /*for(int i = 0; i < INIT_POP_SIZE; i++){
                if((*orgVect)[i].getPos() == dir){
                    (*orgVect)[i].m_alive = false;
                    break;
                }
            }
            //  change bot's color to more reddish
            sf::Color col = this->body.getFillColor();
            col.g -= 10;
            col.r += 10;
            this->body.setFillColor(col);*/
            stepInc = 2;
            break;
        }
        //if food then eat it
        case 3:
        {
            incHealth();
            map->setTileType(li::ctoi(dir), 0);
            //std::cout << &this->m_life << "Food generated.\n";
            //  change bot's color to more greenish
            /*sf::Color col = this->body.getFillColor();
            col.b += 10;
            col.r -= 10;
            this->body.setFillColor(col);*/
            stepInc = 1;
            break;
        }
        //if corpse then eat it
        case 4:
        {
            incHealth();
            map->setTileType(li::ctoi(dir), 0);
            decHealth();
            stepInc = 5;
            break;
        }
    }
    m_currStep += m_brain[(m_currStep + stepInc) % BRAIN_SIZE];
    m_currStep %= BRAIN_SIZE;
    //std::cout << "End of eat()\n";
}

void Organism::look(Map *map, sf::Vector2f dir){
    int tileType = map->inspectTile(dir);
    int stepInc = 0;
    switch (tileType) {
        //if empty space
        case 0:{
            stepInc = 1;
            break;
        }
        //if wall
        case 1:{
            stepInc = 2;
            break;
        }
        //if bot
        case 2:{
            stepInc = 3;
            break;
        }
        //if food
        case 3:{
            stepInc = 4;
            break;
        }
        //if relative bot
        case 4:{
            stepInc = 5;
            break;
        }
    }
    m_currStep += m_brain[(m_currStep + stepInc) % BRAIN_SIZE];
    m_currStep %= BRAIN_SIZE;
}

bool Organism::isAlive()
{
    return m_alive;
}


bool Organism::isSurrounded(Map *map, sf::Vector2f pos){
    bool surrounded = true;
    
    // check north
    if(map->inspectTile(sf::Vector2f(pos.x, pos.y - CELL_SIZE)) == 0){
        return false;
    }
    
    // check north-east
    if(map->inspectTile(sf::Vector2f(li::fixCoord(pos.x + CELL_SIZE), pos.y - CELL_SIZE)) == 0){
        return false;
    }
    
    // check east
    if(map->inspectTile(sf::Vector2f(li::fixCoord(pos.x + CELL_SIZE), pos.y)) == 0){
        return false;
    }
    
    // check south-east
    if(map->inspectTile(sf::Vector2f(li::fixCoord(pos.x + CELL_SIZE), pos.y + CELL_SIZE)) == 0){
        return false;
    }
    
    // check south
    if(map->inspectTile(sf::Vector2f(pos.x, pos.y + CELL_SIZE)) == 0){
        return false;
    }
    
    // check south-west
    if(map->inspectTile(sf::Vector2f(li::fixCoord(pos.x - CELL_SIZE), pos.y + CELL_SIZE)) == 0){
        return false;
    }
    
    // check west
    if(map->inspectTile(sf::Vector2f(li::fixCoord(pos.x - CELL_SIZE), pos.y)) == 0){
        return false;
    }
    
    // check north-west
    if(map->inspectTile(sf::Vector2f(li::fixCoord(pos.x - CELL_SIZE), pos.y - CELL_SIZE)) == 0){
        return false;
    }
    
    return true;
}

bool Organism::createOffspring(std::vector<Organism> *orgVect, Map *map){
    //if there is an empty space around create offspring
    
    if(!this->isSurrounded(map, this->body.getPosition())){
        bool spawned = false;
        do{
            sf::Vector2f pos = this->body.getPosition();
            int dir = rand() % 8;
            switch (dir) {
                case 0:{
                    pos.y -= CELL_SIZE;
                    break;
                }
                case 1:{
                    pos.x += CELL_SIZE;
                    pos.y -= CELL_SIZE;
                    break;
                }
                case 2:{
                    pos.x += CELL_SIZE;
                    break;
                }
                case 3:{
                    pos.x += CELL_SIZE;
                    pos.y += CELL_SIZE;
                    break;
                }
                case 4:{
                    pos.y += CELL_SIZE;
                    break;
                }
                case 5:{
                    pos.x -= CELL_SIZE;
                    pos.y += CELL_SIZE;
                    break;
                }
                case 6:{
                    pos.x -= CELL_SIZE;
                    break;
                }
                case 7:{
                    pos.x -= CELL_SIZE;
                    pos.y -= CELL_SIZE;
                    break;
                }
            }
            pos.x = li::fixCoord(pos.x);
            //std::cout << "trying pos " << pos.x << ";" << pos.y << "\n";
            if(map->inspectTile(pos) == 0){
                //create child here
                Organism tempOrg(map, pos);
                
                //copy genes and mutate
                
                orgVect->push_back(tempOrg);
                //std::cout << "orgVect size: " << orgVect->size() << "\n";
                this->copy(orgVect, orgVect->size() - 1);
                //std::cout << "orgVect last element: " << orgVect->back().body.getPosition().x << ";" << orgVect->back().body.getPosition().y << "\n";
                
                map->setTileType(pos, 2);
                orgVect->back().reset(map);
                orgVect->back().body.setPosition(pos);
                //std::cout << "orgVect last element: " << orgVect->back().body.getPosition().x << ";" << orgVect->back().body.getPosition().y << "\n";
                
                //reduce father's live after giving birth
                this->m_life -= 250;
                
                //orgVect->back().body.setFillColor(sf::Color(0, 100, 0));////////
                
                int roll = rand() % 100;
                if(roll < MUTATION_CHANCE){
                    roll = rand() % BRAIN_SIZE;
                    for(int mutNum = 0; mutNum < MUTATION_SIZE; mutNum++){
                        int newCommand = rand() % 64;
                        orgVect->back().setBrainCell((roll + mutNum) % BRAIN_SIZE, newCommand);
                    }
                    //std::cout << "*****Mutated child*****\n";
                }
                
                spawned = true;
                
                //std::cout << "Father at " << this->body.getPosition().x << ";" << this->body.getPosition().y << ". Child at " << pos.x << ";" << pos.y << "\n";
                return true;
            }
        }while(!spawned);
        return false;
    }
    //kill bot if sourrounded
    else{
        //std::cout << "I'm surrounded (" << this->body.getPosition().x << ";" << this->body.getPosition().y << "). I had " << this->m_life << " life.\n";
        this->m_alive = false;
        map->setTileType(this->body.getPosition(), 4);
        return false;
    }
}

void Organism::swap(std::vector<Organism> *orgVect, int index)
{
    int tempInt = (*orgVect).at(index).m_currStep;
    (*orgVect).at(index).m_currStep = this->m_currStep;
    this->m_currStep = tempInt;
    
    bool tempBool = (*orgVect).at(index).m_alive;
    (*orgVect).at(index).m_alive = this->m_alive;
    this->m_alive = tempBool;
    
    tempInt = (*orgVect).at(index).m_life;
    (*orgVect).at(index).m_life = this->m_life;
    this->m_life = tempInt;
    
    int tempIntArr[BRAIN_SIZE];
    std::copy(std::begin((*orgVect).at(index).m_brain), std::end((*orgVect).at(index).m_brain), std::begin(tempIntArr));
    std::copy(std::begin(this->m_brain), std::end(this->m_brain), std::begin((*orgVect).at(index).m_brain));
    std::copy(std::begin(tempIntArr), std::end(tempIntArr), std::begin(this->m_brain));

    sf::RectangleShape tempBody = (*orgVect).at(index).body;
    (*orgVect).at(index).body = this->body;
    this->body = tempBody;
}

void Organism::copy(std::vector<Organism> *orgVect, int destIndex)
{
    (*orgVect).at(destIndex).m_currStep = this->m_currStep;
    (*orgVect).at(destIndex).m_alive = this->m_alive;
    (*orgVect).at(destIndex).m_life = this->m_life;
    std::copy(std::begin(this->m_brain), std::end(this->m_brain), std::begin((*orgVect).at(destIndex).m_brain));
    (*orgVect).at(destIndex).body = this->body;
}

//should return 0 or 1 to show if Organism was deleted and same index should be updated or delete all dead after update in a loop
int Organism::update(std::vector<Organism> *orgVect, Map *map)
{
    //check if alive
    if(!m_alive)
        return;
    
    //std::cout << "Energy: " << this->m_energy << ". Life: " << this->m_life << "\n";
    
    int attempts = 0;
    bool acted = false;
    
    //collect energy and minerals
    collectEnergy();
    //collectMinerals();
    
    sf::Vector2f pos = body.getPosition();
    do{
        switch (m_brain[m_currStep]) {
            //go N
            case 0:
            {
                pos.y -= CELL_SIZE;
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go NE
            case 1:
            {
                pos.x += CELL_SIZE;
                pos.y -= CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go E
            case 2:
            {
                pos.x += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go SE
            case 3:
            {
                pos.x += CELL_SIZE;
                pos.y += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go S
            case 4:
            {
                pos.y += CELL_SIZE;
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go SW
            case 5:
            {
                pos.x -= CELL_SIZE;
                pos.y += CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go W
            case 6:
            {
                pos.x -= CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //go NW
            case 7:
            {
                pos.x -= CELL_SIZE;
                pos.y -= CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                if(tryStepping(map, pos)){
                    return -1;
                }
                acted = true;
                break;
            }
            //eat N
            case 8:
            {
                pos.y -= CELL_SIZE;
                eat(map, pos);
                acted = true;
                break;
            }
            //eat NE
            case 9:
            {
                pos.y -= CELL_SIZE;
                pos.x += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                eat(map, pos);
                acted = true;
                break;
            }
            //eat E
            case 10:
            {
                pos.x += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                eat(map, pos);
                acted = true;
                break;
            }
            //eat SE
            case 11:
            {
                pos.x += CELL_SIZE;
                pos.y += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                eat(map, pos);
                acted = true;
                break;
            }
            //eat S
            case 12:
            {
                pos.y += CELL_SIZE;
                eat(map, pos);
                acted = true;
                break;
            }
            //eat SW
            case 13:
            {
                pos.x -= CELL_SIZE;
                pos.y += CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                eat(map, pos);
                acted = true;
                break;
            }
            //eat W
            case 14:
            {
                pos.x -= CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                eat(map, pos);
                acted = true;
                break;
            }
            //eat NW
            case 15:
            {
                pos.x -= CELL_SIZE;
                pos.y -= CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                eat(map, pos);
                acted = true;
                break;
            }
            //look N
            case 16:
            {
                pos.y -= CELL_SIZE;
                look(map, pos);
                acted = true;
                break;
            }
            //look NE
            case 17:
            {
                pos.x += CELL_SIZE;
                pos.y -= CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                look(map, pos);
                acted = true;
                break;
            }
            //look E
            case 18:
            {
                pos.x += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                look(map, pos);
                acted = true;
                break;
            }
            //look SE
            case 19:
            {
                pos.x += CELL_SIZE;
                pos.y += CELL_SIZE;
                if(pos.x >= MAP_WIDTH * CELL_SIZE){
                    pos.x = 0;
                }
                look(map, pos);
                acted = true;
                break;
            }
            //look S
            case 20:
            {
                pos.y += CELL_SIZE;
                look(map, pos);
                acted = true;
                break;
            }
            //look SW
            case 21:
            {
                pos.x -= CELL_SIZE;
                pos.y += CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                look(map, pos);
                acted = true;
                break;
            }
            //look W
            case 22:
            {
                pos.x -= CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                look(map, pos);
                acted = true;
                break;
            }
            //look NW
            case 23:
            {
                pos.x -= CELL_SIZE;
                pos.y -= CELL_SIZE;
                if(pos.x < 0){
                    pos.x = MAP_WIDTH * CELL_SIZE - CELL_SIZE;
                }
                look(map, pos);
                acted = true;
                break;
            }
            // photosynthesis
            case 24:{
                m_life += m_energy;
                if(m_life > MIN_HEALTH_TO_REPRODUCE){
                    if(createOffspring(orgVect, map)){
                        return 1;
                    }
                    else {
                        return -1;
                    }
                }
                if(m_life > MAX_HEALTH){
                    m_life = MAX_HEALTH;
                }
                
                m_energy = 0;
                m_currStep++;
                acted = true;
                return 0;
            }
            // convert minerals to life
            case 25:{
                m_life += m_minerals;
                m_minerals = 0;
                m_currStep++;
                acted = true;
                break;
            }
            default:
            {
                m_currStep += m_brain[m_currStep];
                break;
            }
        }
        if(m_currStep >= BRAIN_SIZE){
            m_currStep %= BRAIN_SIZE;
        }
        attempts++;
    }while(attempts < 10 && !acted);
    return -2;
    //std::cout << &this->m_currStep << " attempts:\t" << attempts << "\n";
}
