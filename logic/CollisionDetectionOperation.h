#include <iostream>
#include <SFML/Graphics.hpp>
#include "Operation.h"
#include "../Entities/Player.h"
#include "../Entities/Line.h"
#include "../Entities/Box.h"
#include "../Entities/Ball.h"

using namespace std;

class CollisionDetectionOperation{
    private:
        //instantiating objects
        Operation operation;
        Player player;
        Box box;
        Ball ball;


    public:
        //variables
        sf::Vector2f a_ball;
        sf::Vector2f b_ball;
        //intersection check
        bool _boxOverlapping(float min_a, float max_a, float min_b, float max_b);
        bool _ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b);
        bool _ballWindowOverlapping();
        bool _boxWindowOverlapping();
        //penetretion and collision resolution
        void _ballBallPenetrationResolution(sf::CircleShape a, sf::CircleShape b);

        //actual collision function
        bool _linesCollide(Line a, Line b);
        bool _boxCollide(Box a, Box b);
        bool _ballCollide(sf::CircleShape a, sf::CircleShape b);
        bool _ballWindowCollide();
        bool _boxWindowCollider();
};