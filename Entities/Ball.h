#include <SFML/Graphics.hpp>
#include <vector>

class Ball{
    private:
        
        //attributes
        float acceleration;
        float radius;

        //initializer functions
        void initBall();
        void createBall(sf::Vector2f vector);

        //instantiating objects

    public:
        sf::CircleShape ball_property;
        //constructor
        Ball();
        //ball container vector
        std::vector<sf::CircleShape> balls;
        //main ball functions
        void ballUpdate(sf::Vector2f vector);
        void ballRender(sf::RenderTarget* target);

        //transform functions
        void ballMovement();

        //accessors and mutators
        sf::Vector2f getBallPosition();
        float getBallRadius();
        void setBallPosition(sf::Vector2f vector);
};