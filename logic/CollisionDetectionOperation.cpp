#include "CollisionDetectionOperation.h"

//defining functions
    //intersection check
bool CollisionDetectionOperation::_boxOverlapping(float min_a, float max_a, float min_b, float max_b){
    return min_b <= max_a && min_a <= max_b;
}
bool CollisionDetectionOperation::_ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b){
    return operation._magnitude(origin_b - origin_a) <= (radius_a + radius_b);
}
bool CollisionDetectionOperation::_ballLineOverlapping(sf::CircleShape &a, Line &l){
    
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
bool CollisionDetectionOperation::_ballSegmentOverlapping(sf::CircleShape &a, Line &l){
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
bool CollisionDetectionOperation::_ballLineOverlapping(Player &a, Line &l){
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
    //ball-ball penetration resoultion
void CollisionDetectionOperation::_ballBallPenetrationResolution(Player &a, Ball &b){
    sf::Vector2f normal = this->operation._displacement(a.getPlayerPosition(), b.getBallPosition());
    float distance = this->operation._magnitude(normal);
    float penetration_depth = (a.getPlayerRadius() + b.getBallRadius()) - distance;
    sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_depth/(a.getPlayerInverseMass() + b.getBallInverseMass());
    this->a_position = penetration_resolution_vector * a.getPlayerInverseMass();
    this->b_position = -penetration_resolution_vector * b.getBallInverseMass();
}
void CollisionDetectionOperation::_ballBallPenetrationResolution(Ball &a, Ball &b){
    sf::Vector2f normal = this->operation._displacement(a.getBallPosition(), b.getBallPosition());
    float distance = this->operation._magnitude(normal);
    float penetration_depth = (a.getBallRadius() + b.getBallRadius()) - distance;
    sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_depth/2.f;
    this->a_position = penetration_resolution_vector;
    this->b_position = -penetration_resolution_vector;
}
    //ball-ball collision resolution
void CollisionDetectionOperation::_ballBallCollisionResolution(Player &a, Ball &b){
    sf::Vector2f normal = this->operation._displacement(a.getPlayerPosition(), b.getBallPosition());
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(a.getPlayerVelocity(), b.getBallVelocity());
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.getPlayerInverseMass() + b.getBallInverseMass());
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.getPlayerInverseMass() * a.getPlayerElasticity();
    this->b_velocity = -impulse_vector * b.getBallInverseMass() * b.getBallElasticity();
}
void CollisionDetectionOperation::_ballBallCollisionResolution(Ball &a, Ball &b){
    sf::Vector2f normal = this->operation._displacement(a.getBallPosition(), b.getBallPosition());
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(a.getBallVelocity(), b.getBallVelocity());
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.getBallInverseMass() + b.getBallInverseMass());
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.getBallInverseMass() * a.getBallElasticity();
    this->b_velocity = -impulse_vector * b.getBallInverseMass() * b.getBallElasticity();
}
    //ball-point penetration resolution
void CollisionDetectionOperation::_ballPointPenetrationResolution(sf::CircleShape &a, sf::Vector2f &p){
    sf::Vector2f normal = this->operation._displacement(a.getPosition(), p);
    float distance = this->operation._magnitude(normal);
    float penetration_distance = a.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_distance/2.f;
    this->a_position = penetration_resolution_vector;
}
    //ball-point collision resolution
void CollisionDetectionOperation::_ballPointCollisionResolution(Player &player, sf::Vector2f &point){
    sf::Vector2f normal = this->operation._displacement(player.getPlayerPosition(), point);
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(player.getPlayerVelocity(), sf::Vector2f(0.f, 0.f));
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->a_velocity = -separating_velocity_vector * player.getPlayerElasticity();
}
void CollisionDetectionOperation::_ballPointCollisionResolution(Ball &ball, sf::Vector2f &point){
    sf::Vector2f normal = this->operation._displacement(ball.getBallPosition(), point);
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(ball.getBallVelocity(), sf::Vector2f(0.f, 0.f));
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->b_velocity = -separating_velocity_vector;
}

    //box-box penetration resoultion
void CollisionDetectionOperation::_boxBoxPenetrationResolution(Box &a, Box &b){
    sf::Vector2f normal = a.getBoxPosition() - b.getBoxPosition();
    float distance = this->operation._magnitude(normal);
    float a_x_half = a.box_property.getSize().x/2.f;
    float b_x_half = b.box_property.getSize().x/2.f;
    float overlap_x = normal.x - (a_x_half + b_x_half);
    float overlap_y = normal.y - (a_x_half + b_x_half);
    float penetration_depth = min(overlap_x, overlap_y);
    sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_depth/(a_x_half + b_x_half);

    this->a_position = -penetration_resolution_vector;
    this->b_position = penetration_resolution_vector;
}
    //box-box collision resolution
void CollisionDetectionOperation::_boxBoxCollisionResolution(Box &a, Box &b){
    sf::Vector2f normal = a.getBoxPosition() - b.getBoxPosition();
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = a.getBoxVelocity() - b.getBoxVelocity();
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->a_velocity = -separating_velocity_vector;
    this->b_velocity = separating_velocity_vector;
}
    //ball-box penetration resolution
void CollisionDetectionOperation::_ballBoxPenetrationResolution(Ball &ball, Box &box){
    sf::Vector2f normal = ball.getBallPosition() - box.getBoxPosition();
    normal = this->operation._unitVector(normal);
    sf::Vector2f nearest_position = this->clampOnRectangle(ball.getBallPosition(), box);
    float distance = this->operation._magnitude(ball.getBallPosition() - nearest_position);
    float penetration_depth = ball.getBallRadius() - distance;
    sf::Vector2f penetration_resolution_vector = normal * penetration_depth;
    this->a_position = penetration_resolution_vector;
    this->b_position = -penetration_resolution_vector;
}
void CollisionDetectionOperation::_ballBoxPenetrationResolution(Player &player, Box &box){
    sf::Vector2f normal = player.getPlayerPosition() - box.getBoxPosition();
    normal = this->operation._unitVector(normal);
    sf::Vector2f nearest_position = this->clampOnRectangle(player.getPlayerPosition(), box);
    float distance = this->operation._magnitude(player.getPlayerPosition() - nearest_position);
    float penetration_depth = player.getPlayerRadius() - distance;
    sf::Vector2f penetration_resolution_vector = normal * penetration_depth;
    this->a_position = penetration_resolution_vector;
    this->b_position = -penetration_resolution_vector;
}

    //ball-box collision resolution

    //actual collision functions
bool CollisionDetectionOperation::_linesCollide(Line &a, Line &b){
    if(operation._parallelVectors(a.getDirection(), b.getDirection()))
        return false;
    else 
        return true;
}

bool CollisionDetectionOperation::_boxCollide(Box &a, Box &b){
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

bool CollisionDetectionOperation::_ballCollide(sf::CircleShape &a, sf::CircleShape &b){
    return _ballOverlapping(a.getRadius(), b.getRadius(), a.getPosition(), b.getPosition());
}
bool CollisionDetectionOperation::_ballCollide(Player &a, Ball &b){
    return _ballOverlapping(a.getPlayerRadius(), b.getBallRadius(), a.getPlayerPosition(), b.getBallPosition());
}
bool CollisionDetectionOperation::_ballPointCollide(sf::CircleShape &a, sf::Vector2f point){
    sf::Vector2f displacement = this->operation._displacement(a.getPosition(), point);
    float distance = this->operation._magnitude(displacement);
    return distance <= a.getRadius();
}
bool CollisionDetectionOperation::_ballWindowCollide(sf::CircleShape &a, Line l1, Line l2, Line l3, Line l4){
    return this->_ballLineOverlapping(a, l1) || this->_ballLineOverlapping(a, l2) || this->_ballLineOverlapping(a, l3) || this->_ballLineOverlapping(a, l4);
}
bool CollisionDetectionOperation::_ballBoxCollide(Ball &ball, Box &box){
    sf::Vector2f clamped = this->clampOnRectangle(ball.getBallPosition(), box);
    tempo_position = clamped;
    return this->_ballPointCollide(ball.ball_property, clamped);
}
bool CollisionDetectionOperation::_ballBoxCollide(Player &player, Box &box){
    sf::Vector2f clamped = this->clampOnRectangle(player.getPlayerPosition(), box);
    tempo_position = clamped;
    return this->_ballPointCollide(player.player_property, clamped);
}

//...
sf::Vector2f CollisionDetectionOperation::clampOnRectangle(sf::Vector2f point, Box box){
    sf::Vector2f clamp;
    clamp.x = this->operation._clampOnRange(point.x, box.box_property.getGlobalBounds().left, box.box_property.getGlobalBounds().left + box.box_property.getGlobalBounds().width);
    clamp.y = this->operation._clampOnRange(point.y, box.box_property.getGlobalBounds().top, box.box_property.getGlobalBounds().top + box.box_property.getGlobalBounds().height);
    return clamp;
}