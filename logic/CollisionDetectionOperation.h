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
        //storing vital positions
        sf::Vector2f a_position;
        sf::Vector2f b_position;
        sf::Vector2f nearest_point;
        sf::Vector2f a_velocity;
        sf::Vector2f b_velocity;
        sf::Vector2f tempo_position;
        //intersection check
        bool _boxOverlapping(float min_a, float max_a, float min_b, float max_b);
        bool _ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b);
        bool _boxLineOverlapping();
        bool _ballLineOverlapping(sf::CircleShape &a, Line &l);
        bool _ballSegmentOverlapping(sf::CircleShape &a, Line &l);
        bool _ballLineOverlapping(Player &a, Line &l);
        //penetretion and collision resolution
        void _ballBallPenetrationResolution(Player &a, Ball &b);
        void _ballBallPenetrationResolution(Ball &a, Ball &b);
        void _ballBallCollisionResolution(Player &a, Ball &b);
        void _ballBallCollisionResolution(Ball &a, Ball &b);
        void _ballPointPenetrationResolution(sf::CircleShape &a, sf::Vector2f &p);
        void _ballPointCollisionResolution(Player &player, sf::Vector2f &point);
        void _ballPointCollisionResolution(Ball &ball, sf::Vector2f &point);
        void _boxBoxPenetrationResolution(Box &a, Box &b);
        void _boxBoxCollisionResolution(Box &a, Box &b);
        void _ballBoxPenetrationResolution(Ball &ball, Box &box);
        void _ballBoxPenetrationResolution(Player &player, Box &box);
        void _ballBoxCollisionResolution(Ball &ball, Box &box);

        //actual collision function
        bool _linesCollide(Line &a, Line &b);
        bool _boxCollide(Box &a, Box &b);
        bool _ballCollide(sf::CircleShape &a, sf::CircleShape &b);
        bool _ballCollide(Player &a, Ball &b);
        bool _boxLineCollide();
        bool _ballPointCollide(sf::CircleShape &a, sf::Vector2f point);
        bool _ballWindowCollide(sf::CircleShape &a, Line l1, Line l2, Line l3, Line l4);
        bool _ballBoxCollide(Ball &ball, Box &box);
        bool _ballBoxCollide(Player &player, Box &box);

        //...
        sf::Vector2f clampOnRectangle(sf::Vector2f point, Box box);
};