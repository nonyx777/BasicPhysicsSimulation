#include <SFML/Graphics.hpp>

class Box{
    private:
        //physics attributes
        sf::Vector2f velocity, acceleration_vector;
        float acceleration, friction, elasticity, mass, inverse_mass;

        //initializer functions
        void initBox();
    
    public:
        sf::RectangleShape box_property;
        //constructor and destructor
        Box();

        //main box functions
        void boxUpdate();
        void boxRender(sf::RenderTarget* target);

        //transform functions
        void boxMovement();

        //accessors and mutators
        sf::Vector2f getBoxPosition();
        void setBoxPosition(sf::Vector2f vector);
        sf::Vector2f getBoxVelocity();
        void setBoxVelocity(sf::Vector2f vector);
        float getBoxElasticity();
        void setBoxElasticity(float elasticity);
        float getBoxMass();
        void setBoxMass(float mass);
        float getBoxInverseMass();
};