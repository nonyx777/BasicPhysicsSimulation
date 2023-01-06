#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265

using namespace std;

class Operation{
    private:
        float radian;
    public:
        //trig operations
        float _sin(float degree);
        float _cos(float degree);
        float _acos(float point);
        float _atan2(float y, float x);

        //angle conversion operations
        float _rad2Deg();
        float _deg2Rad();
        //vector conversion operation
        sf::Vector2f _scalar2Vector(float scalar);

        //vector operations
        float _magnitude(sf::Vector2f vector);
        sf::Vector2f _displacement(sf::Vector2f target_position, sf::Vector2f self_position);
        float _distance(sf::Vector2f vector);
        sf::Vector2f _unitVector(sf::Vector2f _displacement);
        sf::Vector2f _rotate(sf::Vector2f vector, float angle);
        sf::Vector2f _rotateBy90(sf::Vector2f vector);
        sf::Vector2f _translate(sf::Vector2f vector_a, sf::Vector2f vector_b, float speed);
        sf::Vector2f _transalte(sf::Vector2f vector_a, sf::Vector2f vector_b);
        float _dotProduct(sf::Vector2f a, sf::Vector2f b);
        bool _parallelVectors(sf::Vector2f a, sf::Vector2f b);
        sf::Vector2f _vectorProjection(sf::Vector2f a, sf::Vector2f b);

        //...
        float _clampOnRange(float x, float min, float max);
};