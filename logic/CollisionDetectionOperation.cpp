#include "CollisionDetectionOperation.h"

//defining functions
    //intersection check
bool CollisionDetectionOperation::_boxOverlapping(float min_a, float max_a, float min_b, float max_b){
    return min_b <= max_a && min_a <= max_b;
}
bool CollisionDetectionOperation::_ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b){
    return operation._magnitude(origin_b - origin_a) <= (radius_a + radius_b);
}
bool CollisionDetectionOperation::_ballLineOverlapping(sf::CircleShape a, Line l){
    
    float x_value;
    float y_value;

    if(l.getBase().x == 640.f && l.getDirection().x == 640.f){
        x_value = 640.f;
        y_value = 0.f;
        l.setBase(sf::Vector2f(0.f, 0.f));
        l.setDirection(sf::Vector2f(0.f, 360.f));
    }else if(l.getBase().y == 360.f && l.getDirection().y == 360.f){
        x_value = 0.f;
        y_value = 360.f;
        l.setBase(sf::Vector2f(0.f, 0.f));
        l.setDirection(sf::Vector2f(640.f, 0.f));
    }else{
        x_value = 0.f;
        y_value = 0.f;
    }

    sf::Vector2f lc = this->operation._displacement(a.getPosition(), l.getBase());
    sf::Vector2f projection = this->operation._vectorProjection(lc, l.getDirection());
    nearest_point = l.getBase() + projection;
    nearest_point.x += x_value;
    nearest_point.y += y_value;
    return this->_ballPointCollide(a, nearest_point);
}
bool CollisionDetectionOperation::_ballSegmentOverlapping(sf::CircleShape a, Line l){
    if(this->_ballPointCollide(a, l.getBase())){
        nearest_point = l.getBase();
        return this->_ballPointCollide(a, nearest_point);
    }
    if(this->_ballPointCollide(a, l.getDirection())){
        nearest_point = l.getDirection();
        return this->_ballPointCollide(a, nearest_point);
    }

    sf::Vector2f d = l.getDirection() - l.getBase();
    sf::Vector2f lc = a.getPosition() - l.getBase();
    sf::Vector2f p = this->operation._vectorProjection(lc, d);
    nearest_point = l.getBase() + p;

    return this->_ballPointCollide(a, nearest_point) && 
    this->operation._magnitude(p) <= this->operation._magnitude(d) && 
    0 <= this->operation._dotProduct(p, d);
}
bool CollisionDetectionOperation::_ballLineOverlapping(Player a, Line l){
    float x_value;
    float y_value;

    if(l.getBase().x == 640.f && l.getDirection().x == 640.f){
        x_value = 640.f;
        y_value = 0.f;
        l.setBase(sf::Vector2f(0.f, 0.f));
        l.setDirection(sf::Vector2f(0.f, 360.f));
    }else if(l.getBase().y == 360.f && l.getDirection().y == 360.f){
        x_value = 0.f;
        y_value = 360.f;
        l.setBase(sf::Vector2f(0.f, 0.f));
        l.setDirection(sf::Vector2f(640.f, 0.f));
    }else{
        x_value = 0.f;
        y_value = 0.f;
    }

    sf::Vector2f lc = this->operation._displacement(a.getPlayerPosition(), l.getBase());
    sf::Vector2f projection = this->operation._vectorProjection(lc, l.getDirection());
    nearest_point = l.getBase() + projection;
    nearest_point.x += x_value;
    nearest_point.y += y_value;
    return this->_ballPointCollide(a.player_property, nearest_point);
}
//penetration and collision resolution
void CollisionDetectionOperation::_ballBallPenetrationResolution(Player a, Ball b){
    sf::Vector2f displacement = this->operation._displacement(a.getPlayerPosition(), b.getBallPosition());
    float distance = this->operation._magnitude(displacement);
    float penetration_depth = (a.getPlayerRadius() + b.getBallRadius()) - distance;
    sf::Vector2f penetration_resolution = this->operation._unitVector(displacement) * penetration_depth/(a.getPlayerInverseMass() + b.getBallInverseMass());
    this->a_ball = penetration_resolution * a.getPlayerInverseMass();
    this->b_ball = -penetration_resolution * b.getBallInverseMass();
}
void CollisionDetectionOperation::_ballBallPenetrationResolution(Ball a, Ball b){
    sf::Vector2f displacement = this->operation._displacement(a.getBallPosition(), b.getBallPosition());
    float distance = this->operation._magnitude(displacement);
    float penetration_depth = (a.getBallRadius() + b.getBallRadius()) - distance;
    sf::Vector2f penetration_resolution = this->operation._unitVector(displacement) * penetration_depth/2.f;
    this->a_ball = penetration_resolution;
    this->b_ball = -penetration_resolution;
}
void CollisionDetectionOperation::_ballBallCollisionResolution(Player a, Ball b){
    sf::Vector2f normal = this->operation._displacement(a.getPlayerPosition(), b.getBallPosition());
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(a.getPlayerVelocity(), b.getBallVelocity());
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.getPlayerInverseMass() + b.getBallInverseMass());
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.getPlayerInverseMass() * a.getPlayerElasticity();
    this->b_velocity = -impulse_vector * b.getBallInverseMass() * b.getBallElasticity();
}
void CollisionDetectionOperation::_ballBallCollisionResolution(Ball a, Ball b){
    sf::Vector2f normal = this->operation._displacement(a.getBallPosition(), b.getBallPosition());
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(a.getBallVelocity(), b.getBallVelocity());
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.getBallInverseMass() + b.getBallInverseMass());
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.getBallInverseMass() * a.getBallElasticity();
    this->b_velocity = -impulse_vector * b.getBallInverseMass() * b.getBallElasticity();
}
void CollisionDetectionOperation::_ballPointPenetrationResolution(sf::CircleShape a, sf::Vector2f p){
    sf::Vector2f displacement = this->operation._displacement(a.getPosition(), p);
    float distance = this->operation._magnitude(displacement);
    float penetration_distance = a.getRadius() - distance;
    sf::Vector2f penetration_resolution = this->operation._unitVector(displacement) * penetration_distance/2.f;
    this->a_ball = penetration_resolution;
}
void CollisionDetectionOperation::_ballPointCollisionResolution(Player player, sf::Vector2f point){
    sf::Vector2f normal = this->operation._displacement(player.getPlayerPosition(), point);
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(player.getPlayerVelocity(), sf::Vector2f(0.f, 0.f));
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->a_velocity = -separating_velocity_vector * player.getPlayerElasticity();
}
void CollisionDetectionOperation::_ballPointCollisionResolution(Ball ball, sf::Vector2f point){
    sf::Vector2f normal = this->operation._displacement(ball.getBallPosition(), point);
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(ball.getBallVelocity(), sf::Vector2f(0.f, 0.f));
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->b_velocity = -separating_velocity_vector;
}

    //actual collision functions
bool CollisionDetectionOperation::_linesCollide(Line a, Line b){
    if(operation._parallelVectors(a.getDirection(), b.getDirection()))
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

bool CollisionDetectionOperation::_ballBallCollide(sf::CircleShape a, sf::CircleShape b){
    return _ballOverlapping(a.getRadius(), b.getRadius(), a.getPosition(), b.getPosition());
}
bool CollisionDetectionOperation::_ballBallCollide(Player a, Ball b){
    return _ballOverlapping(a.getPlayerRadius(), b.getBallRadius(), a.getPlayerPosition(), b.getBallPosition());
}
bool CollisionDetectionOperation::_ballPointCollide(sf::CircleShape a, sf::Vector2f point){
    sf::Vector2f displacement = this->operation._displacement(a.getPosition(), point);
    float distance = this->operation._magnitude(displacement);
    return distance <= a.getRadius();
}

bool CollisionDetectionOperation::_ballWindowCollide(sf::CircleShape a, Line l1, Line l2, Line l3, Line l4){
    return this->_ballLineOverlapping(a, l1) || this->_ballLineOverlapping(a, l2) || this->_ballLineOverlapping(a, l3) || this->_ballLineOverlapping(a, l4);
}