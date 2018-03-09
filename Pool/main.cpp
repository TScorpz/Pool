
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "Organism.hpp"
#include "map.hpp"
//#include "Engine.hpp"
#include "functions.hpp"

#include "Settings.hpp"

void sortVector(std::vector<Organism> *vect){
    int vecSize = vect->size();
    for(int i = 0; i < vecSize - 1; i++){
        int fittestInd = i;
        for(int j = i + 1; j < vecSize; j++){
            if((*vect)[fittestInd].getLife() < (*vect)[j].getLife()){
                fittestInd = j;
            }
        }
        if(i != fittestInd){
            (*vect).at(i).swap(vect, fittestInd);
        }
    }
}

/*void createOffsprings(std::vector<Organism> *myPop, Map *map){
    int popSize = myPop->size();
            (*myPop)[e].copy(myPop, ELITE_ORG_NUM + (e * OFFSPRING_NUM) + i);
            (*myPop)[ELITE_ORG_NUM + (e * OFFSPRING_NUM) + i].reset(map);
            int roll = rand() % 100;
            if(roll < MUTATION_CHANCE){
                roll = rand() % BRAIN_SIZE;
                int newCommand = rand() % 64;
                (*myPop)[ELITE_ORG_NUM + (e * OFFSPRING_NUM) + i].setBrainCell(roll, newCommand);
            }
    }
}*/

void newWorld(std::vector<Organism> *myPop, Map *map){
    sortVector(myPop);
    
    for(int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++){
        if(map->getTileType(i) == 2){
            map->setTileType(i, 0);
        }
    }
    
    //createOffsprings(myPop, map);
}

int main(int, char const**){
    srand(time(NULL));
    
    //load map
    Map map;
    
    //create creatures
    std::vector<Organism> myPop;
    int myPopSize = 0;
    
    //for(int i = 0; i < INIT_POP_SIZE; i++){
    Organism tempOrg(&map, sf::Vector2f(CELL_SIZE * 15, CELL_SIZE * 8));
    myPop.push_back(tempOrg);
    map.setTileType(sf::Vector2f(CELL_SIZE * 15, CELL_SIZE * 8), 2);
    //}
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 650), "SFML window");
    window.setFramerateLimit(FPS);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::White);
    
    //frame counter
    int frameNum = 0;
    sf::Text frameNumTxt(std::to_string(frameNum), font, 30);
    frameNumTxt.setFillColor(sf::Color::Red);
    frameNumTxt.setPosition(30, 600);
    
    //Organism counter
    int orgNum = myPop.size();
    sf::Text orgNumTxt(std::to_string(orgNum), font , 30);
    orgNumTxt.setFillColor(sf::Color::Red);
    orgNumTxt.setPosition(30, 550);

    // Start the game loop
    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // 1 pressed: change fps to 1
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
                window.setFramerateLimit(1);
            }
            
            // 2 pressed: change fps to 10
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
                window.setFramerateLimit(10);
            }
            
            // 3 pressed: change fps to 20
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
                window.setFramerateLimit(20);
            }
            
            // 4 pressed: change fps to 30
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
                window.setFramerateLimit(30);
            }
            
            // 5 pressed: change fps to 60
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
                window.setFramerateLimit(0);
            }
            
            // C pressed: clear console
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                system("CLS");
            }
            
            // M button clicked
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M){
                for(int i = 0; i < MAP_HEIGHT; i++){
                    for(int j = 0; j < MAP_WIDTH; j++){
                        std::cout << map.getTileType(i * MAP_WIDTH + j);
                    }
                    std::cout << "\n";
                }
                
                int botNum = 0;
                int tileType = 0;
                for(int y = 0; y < MAP_HEIGHT; y++){
                    for(int x = 0; x < MAP_WIDTH; x++){
                        tileType = map.getTileType(y * MAP_WIDTH + x);
                        if(tileType == 2){
                            botNum++;
                        }
                    }
                }
                std::cout << "bot num: " << botNum << "\n";
            }
            
            // if mouse clicked
            if(event.type == sf::Event::MouseButtonReleased){
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                int x = (int)localPosition.x / CELL_SIZE,
                    y = (int)localPosition.y / CELL_SIZE;
                x *= CELL_SIZE;
                y *= CELL_SIZE;
                
                myPopSize = myPop.size();
                for(int i = 0; i < myPopSize; i++){
                    if(myPop[i].getPos() == sf::Vector2f(x, y)){
                        std::cout << "Current step: " << myPop[i].getCurrStep() << "\n";
                        for(int j = 0; j < BRAIN_SIZE; j++){
                            std::cout << j << ") " << myPop[i].getBrainCell(j) << "\n";
                        }
                        std::cout << "Life: " << myPop[i].getLife() << "\n";
                        std::cout << "Energy: " << myPop[i].getEnergy() << "\n";
                        std::cout << "Minerals: " << myPop[i].getMinerals() << "\n";
                        std::cout << "Position: " << myPop[i].getPos().x << ";" << myPop[i].getPos().y << "\n";
                        std::cout << "end\n\n";
                    }
                }
                //std::cout << "Position: " << localPosition.x << ";" << localPosition.y << "\n";
            }
        }
        
        //std::cout << "\n************\nBefore update\n";
        myPopSize = myPop.size();
        for(int i = 0; i < myPopSize; i++){
            int result = myPop[i].update(&myPop, &map);
            if(result == -1){  //
                myPop.erase(myPop.begin() + i); // error here
                i--;                            //
            }
            else if(result == 1){
                
            }
        }
        //std::cout << "After update\n************\n";
        
        // Clear screen
        window.clear();
        
        window.draw(map);
        window.draw(frameNumTxt);
        window.draw(orgNumTxt);
        
        //myPopSize = myPop.size();
        //int entDrawn = 0;
        //std::cout << "myPop size: " << myPopSize << "\n";
        /*for(int i = 0; i < myPop.size(); i++){
            //if(myPop[i].isAlive()){
                window.draw(myPop[i]);
                //std::cout << "Pos " << myPop[i].getPos().x << ";" << myPop[i].getPos().y << "\n";
                entDrawn++;
            //}
        }*/
        //std::cout << "Entities drawn " << entDrawn << "/" << myPopSize << "\n";

        // Update the window
        window.display();
        
        //update counters
        frameNum++;
        frameNumTxt.setString("Frames passed: " + std::to_string(frameNum));
        
        orgNum = myPop.size();
        orgNumTxt.setString("Organism count: " + std::to_string(orgNum));
    }
    std::cout << "End of program\n";

    return EXIT_SUCCESS;
}
