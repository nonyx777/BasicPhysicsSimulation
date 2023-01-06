#include <iostream>
#include <SFML/Graphics.hpp>

class Ball{
    private:
        //physics attributes
        sf::Vector2f velocity, acceleration_vector;
        float acceleration, friction, elasticity, mass, inverse_mass;

        //shape related attributes
        float radius;

        //initializer functions
        void initBall();

    public:
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
        void setBallVelocity(sf::Vector2f vector);
        float getBallElasticity();
        void setBallElasticity(float elasticity);
        float getBallMass();
        void setBallMass(float mass);
        float getBallInverseMass();
};