#include <SFML/Graphics.hpp>

class Line{
    private:
        sf::Vector2f base;
        sf::Vector2f direction;

    public:
        Line();
        Line(sf::Vector2f base, sf::Vector2f direction);

        void lineRender(sf::RenderTarget* target);

        //accessors and mutators
        void setBase(sf::Vector2f base);
        void setDirection(sf::Vector2f direction);
        sf::Vector2f getBase();
        sf::Vector2f getDirection();
};