#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML", sf::Style::Close | sf::Style::Titlebar);
  sf::Clock Clock;


  // create player paddle
  sf::RectangleShape playerPaddle(sf::Vector2f(5.0f, 50.0f));
  playerPaddle.setPosition(0, 275);

  // create ai paddle
  sf::RectangleShape aiPaddle(sf::Vector2f(5.0f, 50.0f));
  aiPaddle.setPosition(795, 275);

  // create ball
  sf::CircleShape ball(5);
  ball.setPosition(400, 300);
  float ballSpeed = 0.1f;
  float PI = 3.14159265f;
  //float ballAngleRad = 90 * (PI / 180);
  float ballAngleRad = 90.0;


  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }


    // move ball
    //std::cout << std::to_string(ball.getPosition().y);
    if (ball.getPosition().y > 600.0 || ball.getPosition().y < 0.0) {
      ballAngleRad = ballAngleRad * -1.0;
    }
    if (ball.getPosition().x < 0.0 || ball.getPosition().x > 800.0) {
      ballAngleRad = (PI/180) - (ballAngleRad * -1.0);
    }

    float Time = Clock.getElapsedTime().asSeconds();
    ball.move(ballSpeed * std::cos(ballAngleRad), ballSpeed * std::sin(ballAngleRad));


    // keyboard input for player paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
      //std::cout << std::to_string(playerPaddle.getPosition().y) + "\n";
      if (playerPaddle.getPosition().y > 0.0) {
        playerPaddle.move(0.0f, -0.1f);
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
      if (playerPaddle.getPosition().y < 550.0) {
        playerPaddle.move(0.0f, 0.1f);
      }
    }


    // clear screen and fill with blue
    App.clear(sf::Color::Black);

    // draw
    App.draw(playerPaddle);
    App.draw(aiPaddle);
    App.draw(ball);

    // display
    App.display();
  }

  // Done.
  return 0;
}
