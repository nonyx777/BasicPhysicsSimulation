#include "Player.h"
#include "../logic/Operation.h"

//defining initializer functions
void Player::initPlayer(){
    this->acceleration = 0.05f;
    this->player_property.setRadius(30.f);
    this->player_property.setFillColor(sf::Color::Blue);
    
}

//defining constructor
Player::Player(float x, float y){
    this->initPlayer();
    this->player_property.setPosition(sf::Vector2f(x, y));
}

//defining main functions
void Player::playerUpdate(sf::Vector2f vector){
    bool shift_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    this->acceleration = shift_pressed ? 0.1f : 0.05f;
    this->playerMovement(vector);
}
void Player::playerRender(sf::RenderTarget* target){
    target->draw(this->player_property);
}

//defining transform functions
void Player::playerMovement(sf::Vector2f target_position){
    Operation operation;
    sf::Vector2f new_position = operation._translate(this->player_property.getPosition(), target_position, this->acceleration);
    this->player_property.setPosition(new_position);
}

//defiining accessors and mutators
sf::Vector2f Player::getPlayerPosition(){
    return this->player_property.getPosition();
}
float Player::getPlayerRadius(){
    return this->player_property.getRadius();
}
void Player::setPlayerPosition(sf::Vector2f vector){
    this->player_property.setPosition(vector);
}