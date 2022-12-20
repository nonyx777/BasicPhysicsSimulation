#include "Engine.h"

//defining initializer functions
void Engine::initVariables(){
    this->window = nullptr;
}
void Engine::initWindow(){
    this->video_mode.width = 640;
    this->video_mode.height = 360;
    this->window = new sf::RenderWindow(this->video_mode, "Collision Detection", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

//defining constructor and destructor
Engine::Engine(){
    this->initVariables();
    this->initWindow();
}
Engine::~Engine(){
    delete this->window;
}

//defining accessors
const bool Engine::running() const{
    return this->window->isOpen();
}

void Engine::collideEntities(){
    for(auto &ball : this->ball.balls){
        if(this->collisionDetectionOperation._ballCollide(this->player.player_property, ball)){
            this->collisionDetectionOperation._ballBallPenetrationResolution(this->player.player_property, ball);
            this->player.player_property.move(this->collisionDetectionOperation.a_ball);
            ball.move(this->collisionDetectionOperation.b_ball);
        }
    }
}

//defining window functions
void Engine::pollEvent(){
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){
            case sf::Event::Closed:
                this->window->close();
                break;
        }
    }
}
void Engine::update(){
    this->pollEvent();
    this->collideEntities();
    this->mouse_position = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(this->mouse_position);
    this->player.playerUpdate(this->mouse_position_view);
    this->ball.ballUpdate(this->mouse_position_view);

}
void Engine::render(){
    this->window->clear(sf::Color::Black);
    this->player.playerRender(this->window);
    this->ball.ballRender(this->window);
    this->window->display();
}
