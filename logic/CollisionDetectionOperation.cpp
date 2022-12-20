#include "CollisionDetectionOperation.h"

//defining functions
    //intersection check
bool CollisionDetectionOperation::_boxOverlapping(float min_a, float max_a, float min_b, float max_b){
    return min_b <= max_a && min_a <= max_b;
}
bool CollisionDetectionOperation::_ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b){
    sf::Vector2f distance_vector = origin_b - origin_a;
    float distance_between_balls = operation._magnitude(distance_vector);

    return (radius_a + radius_b) >= distance_between_balls;
}
//penetration and collision resolution
void CollisionDetectionOperation::_ballBallPenetrationResolution(sf::CircleShape a, sf::CircleShape b){
    sf::Vector2f displacement = this->operation._displacement(b.getPosition(), a.getPosition());
    float distance = this->operation._magnitude(displacement);
    float penetration_depth = (a.getRadius() + b.getRadius()) - distance;
    sf::Vector2f penetration_resolution = this->operation._unitVector(displacement) * penetration_depth/2.f;
    this->a_ball = -penetration_resolution;
    this->b_ball = penetration_resolution;
}

    //actual collision functions
bool CollisionDetectionOperation::_linesCollide(Line a, Line b){
    if(operation._parallel_vectors(a.getDirection(), b.getDirection()))
        return false;
    else 
        return true;
}

bool CollisionDetectionOperation::_boxCollide(Box a, Box b){
    sf::FloatRect a_bound = a.box_property.getGlobalBounds();
    sf::FloatRect b_bound = b.box_property.getGlobalBounds();
    float a_left = a_bound.left;
    float a_right = a_bound.left + a_bound.width;
    float b_left = b_bound.left;
    float b_right = b_bound.left + b_bound.width;

    float a_bottom = a_bound.top + a_bound.height;
    float a_top = a_bound.top;
    float b_bottom = b_bound.top + b_bound.height;
    float b_top = b_bound.top;

    return this->_boxOverlapping(a_left, a_right, b_left, b_right) && this->_boxOverlapping(a_top, a_bottom, b_top, b_bottom);
}

bool CollisionDetectionOperation::_ballCollide(sf::CircleShape a, sf::CircleShape b){
    float a_radius = a.getRadius();
    float b_radius = b.getRadius();

    return _ballOverlapping(a_radius, b_radius, a.getPosition(), b.getPosition());
}