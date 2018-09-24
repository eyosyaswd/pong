// This is the Game Application Layer. It will include things like
// -- the game loop
// -- SFML layer

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Pong", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
  bool gameStarted = false;
  sf::Clock Clock;

  // load the background
  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("../res/images/soccer_field_background.jpg")) {
    std::cout << "Error occued while loading background image file" << std::endl;
  }
  sf::Sprite backgroundSprite;
  sf::Vector2u backgroundSize = backgroundTexture.getSize();
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setOrigin(18, 10);

  // load the font for the scores
  sf::Font font;
  if (!font.loadFromFile("../res/fonts/neuropol_x_rg.ttf")){
    std::cout << "Error occured while loading font file" << std::endl;
  }

  // create player's score
  int playerScore = 0;
  sf::Text playerScoreTxt;
  playerScoreTxt.setFont(font);
  playerScoreTxt.setString(std::to_string(playerScore));
  playerScoreTxt.setCharacterSize(50);
  playerScoreTxt.setPosition(50, 0);

  // create ai's score
  int aiScore = 0;
  sf::Text aiScoreTxt;
  aiScoreTxt.setFont(font);
  aiScoreTxt.setString(std::to_string(aiScore));
  aiScoreTxt.setCharacterSize(50);
  aiScoreTxt.setPosition(App.getSize().x - 100, 0);

  // create player paddle
  sf::RectangleShape playerPaddle(sf::Vector2f(10.0f, 100.0f));
  playerPaddle.setOrigin(playerPaddle.getSize().x / 2, playerPaddle.getSize().y / 2);
  playerPaddle.setPosition(0.0 + playerPaddle.getSize().x / 2, App.getSize().y / 2);

  // create ai paddle
  sf::RectangleShape aiPaddle(sf::Vector2f(10.0f, 100.0f));
  aiPaddle.setOrigin(aiPaddle.getSize().x/2, aiPaddle.getSize().y/2);
  aiPaddle.setPosition(App.getSize().x - aiPaddle.getSize().x / 2, App.getSize().y / 2);

  // create ball
  sf::Vector2f ballDirection(1.0, 1.0);
  float ballRadius = 8.0;
  float ballSpeed = 0.2;
  sf::CircleShape ball(ballRadius);
  ball.setOrigin(ballRadius, ballRadius);
  ball.setPosition(App.getSize().x / 2, App.getSize().y / 2);

  float ballAngleRad = 90.0;
  float PI = 3.14159265f;


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

    // start game if Space is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      gameStarted = true;
    }


    if (gameStarted == true) {
      // change ball direction when colliding
      // TODO: Change ball direction when colliding
      if (ball.getPosition().y > 600.0) {
        ballAngleRad = ballAngleRad * -1.0;
      } else if (ball.getPosition().y < 0.0) {
        ballAngleRad = ballAngleRad * -1.0;
      }

      // sf::FloatRect ballBoundingBox = ball.getGlobalBounds();
      // sf::FloatRect playerPaddleBoundingBox

      else if (ball.getPosition().x < 10.0) {
        ballAngleRad = (PI/180) - (ballAngleRad * -1.0);
      } else if (ball.getPosition().x > 780.0) {
        ballAngleRad = (PI/180) - (ballAngleRad * -1.0);
      }

      //start moving the ball
      // TODO: Start moving the ball
      ball.move(ballSpeed * std::cos(ballAngleRad), ballSpeed * std::sin(ballAngleRad));

      // keyboard input for player paddle
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        //std::cout << std::to_string(playerPaddle.getPosition().y) + "\n";
        if (playerPaddle.getPosition().y - playerPaddle.getSize().y / 2.0 > 0.0) {
          playerPaddle.move(0.0f, -0.2f);
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        if (playerPaddle.getPosition().y + (playerPaddle.getSize().y / 2.0) < App.getSize().y) {
          playerPaddle.move(0.0f, 0.2f);
        }
      }

      // ai paddle movement
      if ( ( (aiPaddle.getPosition().y - aiPaddle.getSize().y > 0.0) || (aiPaddle.getPosition().y < App.getSize().y) ) && (ball.getPosition().x > App.getSize().x / 2) ){
        //aiPaddle.move(0.0f, ballSpeed * std::sin(ballAngleRad));
        // TODO: Instead of making the AI move in the same direction as the ball's movement, make it move towards the ball
        //float delta = Clock.restart().asSeconds() * 60;
        sf::Vector2f dirToBall = aiPaddle.getPosition() - ball.getPosition();
        aiPaddle.move(0.0, dirToBall.x);
      }

    }

    //clear screen
    App.clear();

    // draw objects
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
