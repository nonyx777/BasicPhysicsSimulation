#include "Ball.h"
#include "../logic/Operation.h"

//defining initializer functions
void Ball::initBall(){
    this->acceleration = 0.1f;
    this->elasticity = 1.f;
    this->mass = 20.f;
    this->inverse_mass = this->mass == 0.f ? 0.f : 1.f/this->mass;
}

//defining constructor
Ball::Ball(){
    this->initBall();
}

//defining main functions
void Ball::ballUpdate(){  
    this->ballMovement();
}
void Ball::ballRender(sf::RenderTarget* target){
    target->draw(this->ball_property);
}

//defining transform functions
void Ball::ballMovement(){
    this->ball_property.move(this->getBallVelocity());
}

//defiining accessors and mutators
sf::Vector2f Ball::getBallPosition(){
    return this->ball_property.getPosition();
}
float Ball::getBallRadius(){
    return this->ball_property.getRadius();
}
void Ball::setBallPosition(sf::Vector2f vector){
    this->ball_property.setPosition(vector);
}
sf::Vector2f Ball::getBallVelocity(){
    return this->velocity;
}
void Ball::setBallVelocity(sf::Vector2f velocity){
    this->velocity = velocity;
}
float Ball::getBallElasticity(){
    return this->elasticity;
}
void Ball::setBallElasticity(float elasticity){
    this->elasticity = elasticity;
}
float Ball::getBallMass(){
    return this->mass;
}
void Ball::setBallMass(float mass){
    this->mass = mass;
}
float Ball::getBallInverseMass(){
    return this->inverse_mass;
}