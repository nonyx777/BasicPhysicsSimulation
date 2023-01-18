#include "Engine.h"

//defining initializer functions
void Engine::initVariables(){
    this->window = nullptr;
    this->window_boundaries.push_back(line1);
    this->window_boundaries.push_back(line2);
    this->window_boundaries.push_back(line3);
    this->window_boundaries.push_back(line4);
    this->window_boundaries.push_back(n_line);
}
void Engine::initWindow(){
    this->video_mode.width = 640;
    this->video_mode.height = 360;
    this->window = new sf::RenderWindow(this->video_mode, "Collision Detection", sf::Style::Titlebar | sf::Style::Resize |sf::Style::Close);
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
 
 //custom functions
    //create entities
void Engine::createBalls(sf::Vector2f vector){
    Ball ball;
    ball.ball_property.setRadius(10.f);
    ball.ball_property.setFillColor(sf::Color::White);
    ball.ball_property.setOrigin(sf::Vector2f(ball.getBallRadius(), ball.getBallRadius()));
    ball.ball_property.setOutlineColor(sf::Color::White);
    ball.ball_property.setOutlineThickness(1.f);
    ball.ball_property.setPosition(vector);
    this->balls.push_back(ball);
}
void Engine::createBoxes(sf::Vector2f vector){
    Box box;
    box.box_property.setSize(sf::Vector2f(5.f, 5.f));
    box.box_property.setOrigin(box.box_property.getSize().x/2.f, box.box_property.getSize().y/2.f);
    box.box_property.setFillColor(sf::Color::Transparent);
    box.box_property.setOutlineColor(sf::Color::Cyan);
    box.box_property.setOutlineThickness(1.f);
    box.box_property.setPosition(vector);
    this->boxes.push_back(box);
}

void Engine::collideEntities(){
    //penetration resolution and collision resolution
        //player and window
    for(auto &boundary : this->window_boundaries){
        if(collisionDetectionOperation._ballSegmentOverlapping(this->player.player_property, boundary)){
            this->collisionDetectionOperation._ballPointPenetrationResolution(this->player.player_property, this->collisionDetectionOperation.nearest_point);
            this->player.player_property.move(this->collisionDetectionOperation.a_position);
            this->collisionDetectionOperation._ballPointCollisionResolution(this->player, collisionDetectionOperation.nearest_point);
            this->player.setPlayerVelocity(this->collisionDetectionOperation.a_velocity);
        }
    }
        //player and ball
    for(auto &ball : this->balls){
        if(this->collisionDetectionOperation._ballCollide(this->player.player_property, ball.ball_property)){
            this->collisionDetectionOperation._ballBallPenetrationResolution(this->player, ball);
            this->player.player_property.move(this->collisionDetectionOperation.a_position);
            ball.ball_property.move(this->collisionDetectionOperation.b_position);
            this->collisionDetectionOperation._ballBallCollisionResolution(this->player, ball);
            // this->player.setPlayerVelocity(this->collisionDetectionOperation.a_velocity);
            // ball.setBallVelocity(this->collisionDetectionOperation.b_velocity);
        }
    }
        //ball and window(line)
    for(auto &boundary : this->window_boundaries){
        for(auto &ball : this->balls){
            if(collisionDetectionOperation._ballSegmentOverlapping(ball.ball_property, boundary)){
                this->collisionDetectionOperation._ballPointPenetrationResolution(ball.ball_property, this->collisionDetectionOperation.nearest_point);
                ball.ball_property.move(this->collisionDetectionOperation.a_position);
                this->collisionDetectionOperation._ballPointCollisionResolution(ball, collisionDetectionOperation.nearest_point);
                ball.setBallVelocity(this->collisionDetectionOperation.b_velocity);
            }
        }   
    }
        //ball and ball
    for(int i = 0; i < this->balls.size(); i++){
        for(int j = i+1; j < this->balls.size(); j++){
            if(this->collisionDetectionOperation._ballCollide(this->balls[i].ball_property, this->balls[j].ball_property)){
                this->collisionDetectionOperation._ballBallPenetrationResolution(this->balls[i], this->balls[j]);
                this->balls[i].ball_property.move(this->collisionDetectionOperation.a_position);
                this->balls[j].ball_property.move(this->collisionDetectionOperation.b_position);
                // this->collisionDetectionOperation._ballBallCollisionResolution(this->balls[i], this->balls[j]);
                // this->balls[i].setBallVelocity(this->collisionDetectionOperation.a_velocity);
                // this->balls[j].setBallVelocity(this->collisionDetectionOperation.b_velocity);
            }
        }
    }
        //box and box
    for(int i = 0; i < this->boxes.size(); i++){
        for(int j = i+1; j < this->boxes.size(); j++){
            if(this->collisionDetectionOperation._boxCollide(this->boxes[i], this->boxes[j])){
                this->collisionDetectionOperation._boxBoxPenetrationResolution(this->boxes[i], this->boxes[j]);
                this->boxes[i].box_property.move(this->collisionDetectionOperation.a_position);
                this->boxes[j].box_property.move(this->collisionDetectionOperation.b_position);
                // this->collisionDetectionOperation._boxBoxCollisionResolution(this->boxes[i], this->boxes[j]);
                // this->boxes[i].setBoxVelocity(this->collisionDetectionOperation.a_velocity);
                // this->boxes[j].setBoxVelocity(this->collisionDetectionOperation.b_velocity);
            }
        }
    }
        //ball and box
    for(auto &ball : this->balls){
        for(auto &box : this->boxes){
            if(this->collisionDetectionOperation._ballBoxCollide(ball, box)){
                this->collisionDetectionOperation._ballBoxPenetrationResolution(ball, box);
                this->c_line.setBase(ball.getBallPosition());
                this->c_line.setDirection(this->collisionDetectionOperation.tempo_position);
                ball.ball_property.move(this->collisionDetectionOperation.a_position);
                box.box_property.move(this->collisionDetectionOperation.b_position);
            }
        }
    }
        //player and box
    for(auto &box : this->boxes){
        if(this->collisionDetectionOperation._ballBoxCollide(this->player, box)){
            this->collisionDetectionOperation._ballBoxPenetrationResolution(this->player, box);
            this->c_line.setBase(player.getPlayerPosition());
            this->c_line.setDirection(this->collisionDetectionOperation.tempo_position);
            player.player_property.move(this->collisionDetectionOperation.a_position);
            box.box_property.move(this->collisionDetectionOperation.b_position);
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

    bool q_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    bool e_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    if(q_pressed)
        this->createBalls(this->mouse_position_view);
    if(e_pressed)
        this->createBoxes(this->mouse_position_view);

    // this->player.playerUpdate();

    for(auto &ball : this->balls)
        ball.ballUpdate();
    for(auto &box : this->boxes)
        box.boxUpdate();
}
void Engine::render(){
    this->window->clear(sf::Color::Black);
    for(auto &ball : this->balls)
        ball.ballRender(this->window);
    for(auto &box : this->boxes)
        box.boxRender(this->window);
    for(auto &line : this->window_boundaries)
        line.lineRender(this->window);
    this->player.playerRender(this->window);
    
    this->c_line.lineRender(this->window);
    this->window->display();
}
