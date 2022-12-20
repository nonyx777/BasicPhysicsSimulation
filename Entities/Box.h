#include <SFML/Graphics.hpp>

class Box{
    private:
        sf::Vector2f box_origin;

        //initializer functions
        void initBox();
    
    public:
        sf::RectangleShape box_property;
        //constructor and destructor
        Box(float x = 640.f/2, float y = 360.f/2);

        //main box functions
        void boxUpdate(sf::Vector2f vector);
        void boxRender(sf::RenderTarget* target);

        //transform functions
        void boxMovement(sf::Vector2f target_position);

        //accessors and mutators
        sf::Vector2f getBoxPosition();
        sf::Vector2f getBoxOrigin();

};