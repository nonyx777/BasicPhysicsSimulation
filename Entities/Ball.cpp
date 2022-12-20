#include "Ball.h"
#include "../logic/Operation.h"

//defining initializer functions
void Ball::initBall(){
    this->acceleration = 0.1f;
}

void Ball::createBall(sf::Vector2f vector){
    this->ball_property.setRadius(30.f);
    this->ball_property.setFillColor(sf::Color::White);
    this->ball_property.setPosition(vector);
    this->balls.push_back(this->ball_property);
}

//defining constructor
Ball::Ball(){
    this->initBall();
}

//defining main functions
void Ball::ballUpdate(sf::Vector2f vector){
    bool q_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    if(q_pressed)
        this->createBall(vector);
}
void Ball::ballRender(sf::RenderTarget* target){
    for(int i = 0; i < this->balls.size(); i++){
        target->draw(this->balls[i]);
    }
}

//defining transform functions
void Ball::ballMovement(){
    //..
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