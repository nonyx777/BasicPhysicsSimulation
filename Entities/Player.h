#include <SFML/Graphics.hpp>

class Player{
    private:
        //attributes
        float acceleration;
        float radius;

        //initializer functions
        void initPlayer();

        //instantiating objects

    public:
        sf::CircleShape player_property;
        //constructor
        Player(float x = 640.f/2, float y = 360.f/2);

        //main player functions
        void playerUpdate(sf::Vector2f vector);
        void playerRender(sf::RenderTarget* target);

        //transform functions
        void playerMovement(sf::Vector2f target_position);

        //accessors and mutators
        sf::Vector2f getPlayerPosition();
        float getPlayerRadius();
        void setPlayerPosition(sf::Vector2f vector);
};