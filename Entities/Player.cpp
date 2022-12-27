#include "Player.h"
#include "../logic/Operation.h"

//defining initializer functions
void Player::initPlayer(){
    this->acceleration = 1.f;
    this->friction = 0.1f;
    this->player_property.setRadius(10.f);
    this->player_property.setFillColor(sf::Color::Blue);
}

//defining constructor
Player::Player(float x, float y){
    this->initPlayer();
    this->player_property.setPosition(sf::Vector2f(x, y));
}

//defining main functions
void Player::playerUpdate(){
    bool shift_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    this->acceleration = shift_pressed ? 1.f : 0.1f;
    this->playerMovement();
}
void Player::playerRender(sf::RenderTarget* target){
    target->draw(this->player_property);
}

//defining transform functions
void Player::playerMovement(){
    w_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    s_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    a_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    d_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);


    if(this->w_pressed)
        this->acceleration_vector.y = -this->acceleration;
    if(this->s_pressed)
        this->acceleration_vector.y = this->acceleration;
    if(this->a_pressed)
        this->acceleration_vector.x = -this->acceleration;
    if(this->d_pressed)
        this->acceleration_vector.x = this->acceleration;
    if(!this->w_pressed && !this->s_pressed)
        this->acceleration_vector.y = 0.f;
    if(!this->a_pressed && !this->d_pressed)
        this->acceleration_vector.x = 0.f;

    this->velocity.x += this->acceleration_vector.x;
    this->velocity.y += this->acceleration_vector.y;

    //this->velocity *= 1-this->friction;

    this->player_property.move(sf::Vector2f(this->velocity));
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
sf::Vector2f Player::getPlayerVelocity(){
    return this->velocity;
}
void Player::setPlayerVelocity(sf::Vector2f vector){
    this->velocity = vector;
}