#include <SFML/Graphics.hpp>

class Player{
    private:
        //attributes
        sf::Vector2f acceleration_vector;
        float acceleration;
        float friction;
        float radius;
        float elasticity;
        float mass;
        float inverse_mass;

        //inputs
        bool w_pressed;
        bool s_pressed;
        bool a_pressed;
        bool d_pressed;

        //initializer functions
        void initPlayer();

        //instantiating objects

    public:
        sf::Vector2f velocity;
        sf::CircleShape player_property;
        //constructor
        Player(float x = 640.f/2, float y = 360.f/2);

        //main player functions
        void playerUpdate();
        void playerRender(sf::RenderTarget* target);

        //transform functions
        void playerMovement();

        //accessors and mutators
        sf::Vector2f getPlayerPosition();
        float getPlayerRadius();
        void setPlayerPosition(sf::Vector2f vector);
        sf::Vector2f getPlayerVelocity();
        void setPlayerVelocity(sf::Vector2f vector);
        float getPlayerElasticity();
        void setPlayerElasticity(float elasticity);
        float getPlayerMass();
        void setPlayerMass(float mass);
        float getPlayerInverseMass();
};