#include "Box.h"

//defining initializer functions
void Box::initBox(){
    this->acceleration = 0.1f;
    this->elasticity = 1.f;
    this->mass = 2.5f;
    this->inverse_mass = this->mass == 0.f ? 0.f : 1.f/this->mass;
}

//constructor
Box::Box(){
    this->initBox();
}

//defining main functions
void Box::boxUpdate(){
    this->boxMovement();
}
void Box::boxRender(sf::RenderTarget* target){
    target->draw(this->box_property);
}

void Box::boxMovement(){
    this->box_property.move(this->getBoxVelocity());
}

//defining accessor and mutators
sf::Vector2f Box::getBoxPosition(){
    return this->box_property.getPosition();
}
void Box::setBoxPosition(sf::Vector2f vector){
    this->box_property.setPosition(vector);
}
sf::Vector2f Box::getBoxVelocity(){
    return this->velocity;
}
void Box::setBoxVelocity(sf::Vector2f velocity){
    this->velocity = velocity;
}
float Box::getBoxElasticity(){
    return this->elasticity;
}
void Box::setBoxElasticity(float elasticity){
    this->elasticity = elasticity;
}
float Box::getBoxMass(){
    return this->mass;
}
void Box::setBoxMass(float mass){
    this->mass = mass;
}
float Box::getBoxInverseMass(){
    return this->inverse_mass;
}