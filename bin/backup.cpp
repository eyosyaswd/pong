

// This is the Game Application Layer. It will include things like
// -- the game loop
// -- SFML layer

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Pong", sf::Style::Close | sf::Style::Titlebar);

  // load the background
  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("../res/images/soccer_field_background.jpg")) {
    std::cout << "Error occued while loading background image file" << std::endl;
  }
  sf::Sprite backgroundSprite;
  sf::Vector2u backgroundSize = backgroundTexture.getSize();
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setOrigin(18, 10);



  // load the font
  sf::Font font;
  if (!font.loadFromFile("../res/fonts/neuropol_x_rg.ttf")){
    std::cout << "Error occured while loading font file" << std::endl;
  }

  // create player's score
  int playerScore = 5;
  sf::Text playerScoreTxt;
  playerScoreTxt.setFont(font);
  playerScoreTxt.setString(std::to_string(playerScore));
  playerScoreTxt.setCharacterSize(50);
  playerScoreTxt.setPosition(50, 0);

  // create ai's score
  int aiScore = 11;
  sf::Text aiScoreTxt;
  aiScoreTxt.setFont(font);
  aiScoreTxt.setString(std::to_string(aiScore));
  aiScoreTxt.setCharacterSize(50);
  aiScoreTxt.setPosition(App.getSize().x - 100, 0);

  // create player paddle
  sf::RectangleShape playerPaddle(sf::Vector2f(10.0f, 100.0f));
  playerPaddle.setOrigin(5, 50);
  playerPaddle.setPosition(0, 275);

  // create ai paddle
  sf::RectangleShape aiPaddle(sf::Vector2f(10.0f, 100.0f));
  aiPaddle.setPosition(790, 275);

  // create ball
  // sf::Texture ballTexture;
  // if (!backgroundTexture.loadFromFile("../res/images/ball.png")) {
  //   std::cout << "Error occued while loading ball image file" << std::endl;
  // }
  float ballRadius = 8.0;
  float ballSpeed = 0.2f;
  // sf::Vector2f direction()

  sf::CircleShape ball(ballRadius);
  // ball.setTexture(&ballTexture);
  // ball.setTextureRect(sf::IntRect(1, 1, 10, 10));
  ball.setOrigin(ballRadius, ballRadius);
  ball.setPosition(App.getSize().x / 2, App.getSize().y / 2);

  float PI = 3.14159265f;
  //float ballAngleRad = 90 * (PI / 180);
  float ballAngleRad = 90.0;

  bool gameStarted = false;


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
    if (ball.getPosition().y > 600.0) {
      ballAngleRad = ballAngleRad * -1.0;
    } else if (ball.getPosition().y < 0.0) {
      ballAngleRad = ballAngleRad * -1.0;
    } else if (ball.getPosition().x < 10.0) {
      ballAngleRad = (PI/180) - (ballAngleRad * -1.0);
    } else if (ball.getPosition().x > 780.0) {
      ballAngleRad = (PI/180) - (ballAngleRad * -1.0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      gameStarted = true;
    }

    if (gameStarted == true) {

      //start moving the ball
//      float Time = Clock.getElapsedTime().asSeconds();
      ball.move(ballSpeed * std::cos(ballAngleRad), ballSpeed * std::sin(ballAngleRad));

      // keyboard input for player paddle
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        //std::cout << std::to_string(playerPaddle.getPosition().y) + "\n";
        if (playerPaddle.getPosition().y > 0.0) {
          playerPaddle.move(0.0f, -0.2f);
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        if (playerPaddle.getPosition().y < 500.0) {
          playerPaddle.move(0.0f, 0.2f);
        }
      }

    }


    //clear screen
    App.clear();

    // draw
    App.draw(backgroundSprite);
    App.draw(playerScoreTxt);
    App.draw(aiScoreTxt);
    App.draw(playerPaddle);
    App.draw(aiPaddle);
    App.draw(ball);

    // display
    App.display();
  }

  // Done.
  return 0;
}
