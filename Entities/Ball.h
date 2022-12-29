#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Ball{
    private:
        
        //attributes
        sf::Vector2f acceleration_vector;
        float acceleration;
        float radius;
        float friction;
        float elasticity;
        float mass;
        float inverse_mass;

        //initializer functions
        void initBall();

        //instantiating objects

    public:
        //..
        int current_colliding_ball;
        sf::Vector2f velocity;
        sf::CircleShape ball_property;
        //constructor
        Ball();
        //main ball functions
        void ballUpdate();
        void ballRender(sf::RenderTarget* target);

        //transform functions
        void ballMovement();

        //accessors and mutators
        sf::Vector2f getBallPosition();
        float getBallRadius();
        void setBallPosition(sf::Vector2f vector);
        sf::Vector2f getBallVelocity();
        void setBallVelocity(sf::Vector2f);
        float getBallElasticity();
        void setBallElasticity(float elasticity);
        float getBallMass();
        void setBallMass(float mass);
        float getBallInverseMass();
};