#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../logic/CollisionDetectionOperation.h"
#include <vector>

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
        vector<Line> window_boundaries;


        //instantiating objects
        CollisionDetectionOperation collisionDetectionOperation;
        Operation operation;
        Player player;
        Ball ball;
        Line line1 = Line(sf::Vector2f(0.f, 0.f), sf::Vector2f(640.f, 0.f));//up
        Line line2 = Line(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 360.f));//left
        Line line3 = Line(sf::Vector2f(640.f, 0.f), sf::Vector2f(640.f, 360.f));//right
        Line line4 = Line(sf::Vector2f(0.f, 360.f), sf::Vector2f(640.f, 360.f));//down

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