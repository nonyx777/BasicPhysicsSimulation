#include "Operation.h"

//defining tirg functions
float Operation::_sin(float degree){
    Operation::radian = degree * this->_deg2Rad();
    double radian_double = static_cast<double> (radian);
    float sin_value = sin(radian_double); 
    return sin_value;
}
float Operation::_cos(float degree){
    Operation::radian = degree * this->_deg2Rad();
    double radian_double = static_cast<double> (radian);
    float cos_value = cos(radian_double);
    return cos_value;
}
float Operation::_acos(float point){
    double point_double = point;
    float angle_value = acos(point_double) * this->_rad2Deg();
    return angle_value;
}
float Operation::_atan2(float y, float x){
    float atan2_value = atan2(y, x) * this->_rad2Deg();
    return atan2_value;
}
//angle conversion functions
float Operation::_rad2Deg(){
    return 180.f/PI;
}
float Operation::_deg2Rad(){
    return PI/180.f;
}
//vector conversion function
sf::Vector2f Operation::_scalar2Vector(float scalar){
    sf::Vector2f unit_vector = sf::Vector2f(1.f, 1.f) * scalar;
    return unit_vector;
}

//defining vector functions
float Operation::_magnitude(sf::Vector2f vector){
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}
sf::Vector2f Operation::_displacement(sf::Vector2f target_position, sf::Vector2f self_position){
    sf::Vector2f displacement = sf::Vector2f(
        target_position.x - self_position.x, target_position.y - self_position.y
    );
    return displacement;
}
float Operation::_distance(sf::Vector2f vector){
    float distance = this->_magnitude(vector);
    return distance;
}
sf::Vector2f Operation::_unitVector(sf::Vector2f vector){
    float magnitude = this->_magnitude(vector);
    sf::Vector2f unit_vector = sf::Vector2f(vector.x, vector.y)/magnitude;
    return unit_vector;
}
sf::Vector2f Operation::_rotate(sf::Vector2f vector, float angle){
    sf::Vector2f a = sf::Vector2f(this->_cos(angle), this->_sin(angle));
    sf::Vector2f b = sf::Vector2f(-this->_sin(angle), this->_cos(angle));
    sf::Vector2f rotation = sf::Vector2f(vector.x * a.x - vector.y * b.x, 
    vector.x * a.y + vector.y * b.y);
    return rotation;
}
sf::Vector2f Operation::_rotateBy90(sf::Vector2f vector){
    float x = vector.y;
    float y = -vector.x;
    sf::Vector2f rotated_vector = sf::Vector2f(x, y);
    return rotated_vector;
}
sf::Vector2f Operation::_translate(sf::Vector2f vector_a, sf::Vector2f vector_b, float speed){
    sf::Vector2f distance = this->_displacement(vector_b, vector_a);
    return vector_a += distance * speed;
}
sf::Vector2f Operation::_transalte(sf::Vector2f vector_a, sf::Vector2f _Vector_b){
    sf::Vector2f distance = this->_displacement(_Vector_b, vector_a);
    return vector_a += distance;
}
float Operation::_dotProduct(sf::Vector2f a, sf::Vector2f b){
    float dot_product = a.x * b.x + a.y * b.y;
    return dot_product;
}
bool Operation::_parallelVectors(sf::Vector2f a, sf::Vector2f b){
    sf::Vector2f rotated_vector_a = this->_rotateBy90(a);
    float dot_product = this->_dotProduct(rotated_vector_a, b);
    cout << round(dot_product) << endl;
    if(round(dot_product) >= -0.f && round(dot_product) <= 0.f)
        return true;
    else
        return false;
}
sf::Vector2f Operation::_vectorProjection(sf::Vector2f a, sf::Vector2f b){
    float p_1 = this->_dotProduct(a, b)/pow(this->_magnitude(b), 2);
    return b*p_1;
}

//...
float Operation::_clampOnRange(float x, float min, float max){
    if(x < min)
        return min;
    else if(max < x)
        return max;
    else
        return x;
}