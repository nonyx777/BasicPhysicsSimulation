#include "Box.h"

//defining initializer functions
void Box::initBox(){
    this->box_property.setSize(sf::Vector2f(50.f, 50.f));
    this->box_property.setFillColor(sf::Color::White);
}

//constructor
Box::Box(float x, float y){
    this->initBox();
    this->box_property.setPosition(x, y);
    this->box_origin = this->box_property.getSize()/2.f;
    this->box_property.setOrigin(this->box_origin);
}

//defining main functions
void Box::boxUpdate(sf::Vector2f target_position){
    this->boxMovement(target_position);
}
void Box::boxRender(sf::RenderTarget* target){
    target->draw(this->box_property);
}

void Box::boxMovement(sf::Vector2f target_position){
    this->box_property.setPosition(target_position);
}

//defining accessor and mutators
sf::Vector2f Box::getBoxPosition(){
    return this->box_property.getPosition();
}
sf::Vector2f Box::getBoxOrigin(){
    return this->box_origin;
}