#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../logic/CollisionDetectionOperation.h"

using namespace std;

class Engine{
    private:
        //initializer functions
        void initVariables();
        void initWindow();

        //window variables
        sf::RenderWindow* window;
        sf::VideoMode video_mode;
        sf::Event event;

        //instantiating objects
        CollisionDetectionOperation collisionDetectionOperation;
        Operation operation;
        Player player;
        Ball ball;

        //mouse position
        sf::Vector2i mouse_position;
        sf::Vector2f mouse_position_view;

    public:
        //constructor and destructor
        Engine();
        ~Engine();

        //window functions
        void pollEvent();
        void update();
        void render();

        //Accessors
        const bool running() const;

        //draw entities
        void collideEntities();
};