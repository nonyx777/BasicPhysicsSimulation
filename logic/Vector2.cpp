#include "Vector2.h"

//defining constructor
Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

//defining accessors and modifiers
void Vector2::setX(float x){
    this->x = x;
}
void Vector2::setY(float y){
    this->y = y;
}
float Vector2::getX(){
    return this->x;
}
float Vector2::getY(){
    return this->y;
}