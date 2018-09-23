// This class represents the ball used during pong.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

float PI = 3.14159265f;

class Ball{

private:
  sf::CircleShape ball;
  float ballSpeed;
  float ballAngleRad;
  float radius;

public:
  // constructor
  Ball(float radius = 5.0) {
    ball.setRadius(5);
    ball.setPosition(400, 300);
    float ballSpeed = 0.1f;
    float PI = 3.14159265f;
    float ballAngleRad = 90.0;
  }

};
