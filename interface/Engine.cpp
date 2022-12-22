#include "Engine.h"

//defining initializer functions
void Engine::initVariables(){
    this->window = nullptr;
    this->window_boundaries.push_back(line1);
    this->window_boundaries.push_back(line2);
    this->window_boundaries.push_back(line3);
    this->window_boundaries.push_back(line4);
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
        if(this->collisionDetectionOperation._ballBallCollide(this->player.player_property, ball)){
            this->collisionDetectionOperation._ballBallPenetrationResolution(this->player.player_property, ball);
            this->player.player_property.move(this->collisionDetectionOperation.a_ball);
            ball.move(this->collisionDetectionOperation.b_ball);
        }
    }
    for(auto &boundary : this->window_boundaries){
        if(collisionDetectionOperation._ballLineOverlapping(this->player.player_property, boundary)){
            this->collisionDetectionOperation._ballPointPenetrationResolution(this->player.player_property, this->collisionDetectionOperation.nearest_point);
            this->player.player_property.move(this->collisionDetectionOperation.a_ball);
        }
    }
    for(auto &ball : this->ball.balls){
        for(auto &boundary : this->window_boundaries){
            if(collisionDetectionOperation._ballLineOverlapping(ball, boundary)){
                this->collisionDetectionOperation._ballPointPenetrationResolution(ball, this->collisionDetectionOperation.nearest_point);
                ball.move(this->collisionDetectionOperation.a_ball);
            }
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
    this->line1.lineRender(this->window);
    this->line2.lineRender(this->window);
    this->line3.lineRender(this->window);
    this->line4.lineRender(this->window);
    this->window->display();
}
