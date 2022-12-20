#include "Line.h"

//defining constructor
Line::Line(){

}
Line::Line(sf::Vector2f base, sf::Vector2f direction){
    this->base = base;
    this->direction = direction;
}


void Line::lineRender(sf::RenderTarget* target){
    sf::Vertex line[] = {
        this->getBase(),
        this->getDirection()
    };
    target->draw(line, 2, sf::Lines);
}

//defining accessor and mutators
//accessors and mutators
void Line::setBase(sf::Vector2f base){
    this->base =  base;
}
void Line::setDirection(sf::Vector2f direction){
    this->direction = direction;
}

sf::Vector2f Line::getBase(){
    return this->base;
}
sf::Vector2f Line::getDirection(){
    return this->direction;
}