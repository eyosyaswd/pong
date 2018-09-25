// This is the Game Application Layer. It will include things like
// -- the game loop
// -- SFML layer

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>


int main(int argc, char** argv)
{
  // init app width and height
  float appWidth = 800.0;
  float appHeight = 600.0;

  // create main window
  sf::RenderWindow App(sf::VideoMode(appWidth,appHeight,32), "Pong", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
  bool gameStarted = false;
  sf::Clock Clock;

  // init the background image
  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("../res/images/soccer_field_background.jpg")) {
    std::cout << "Error occued while loading background image file" << std::endl;
  }
  sf::Sprite backgroundSprite;
  sf::Vector2u backgroundSize = backgroundTexture.getSize();
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setOrigin(18, 10);

  // init a font used for writing the score and messages
  sf::Font font;
  if (!font.loadFromFile("../res/fonts/neuropol_x_rg.ttf")){
    std::cout << "Error occured while loading font file" << std::endl;
  }

  // init kicking sound (when ball bounces off player or ai paddle)
  // init cheering sound (when player scores)
  // init booing sound (when ai scores)

  // init player's score
  int playerScore = 0;
  sf::Text playerScoreTxt;
  playerScoreTxt.setFont(font);
  playerScoreTxt.setString(std::to_string(playerScore));
  playerScoreTxt.setCharacterSize(50);
  playerScoreTxt.setPosition(50, 0);

  // init ai's score
  int aiScore = 0;
  sf::Text aiScoreTxt;
  aiScoreTxt.setFont(font);
  aiScoreTxt.setString(std::to_string(aiScore));
  aiScoreTxt.setCharacterSize(50);
  aiScoreTxt.setPosition(appWidth - 100, 0);

  // init player paddle
  sf::RectangleShape playerPaddle(sf::Vector2f(10.0, 100.0));
  playerPaddle.setOrigin(playerPaddle.getSize().x / 2, playerPaddle.getSize().y / 2);
  playerPaddle.setPosition(0.0 + playerPaddle.getSize().x / 2, appHeight / 2);
  float playerPaddleSpeed = 300.0;

  // init ai paddle
  sf::RectangleShape aiPaddle(sf::Vector2f(10.0, 100.0));
  aiPaddle.setOrigin(aiPaddle.getSize().x/2, aiPaddle.getSize().y/2);
  aiPaddle.setPosition(appWidth - aiPaddle.getSize().x / 2, appHeight / 2);
  float aiPaddleSpeed = 200.0;

  // init ball
  sf::Vector2f ballDirection(1.0, 0.5);
  float ballRadius = 5.0;
  float ballSpeed = 300.0;
  sf::CircleShape ball(ballRadius);
  ball.setOrigin(ballRadius, ballRadius);
  ball.setPosition(appWidth / 2, appHeight / 2);

  // init win messages and variables
  sf::Text youWonMessage;
  youWonMessage.setFont(font);
  youWonMessage.setString("Congratulations, you won!\nPress 'N' to play a new game.\nOr press 'ESC' to quit the game.");
  youWonMessage.setCharacterSize(30);
  youWonMessage.setPosition(60, 300);
  bool playerWon = false;

  // init lost message and variable
  sf::Text youLostMessage;
  youLostMessage.setFont(font);
  youLostMessage.setString("You lost :(, better luck next time!\nPress 'N' to play a new game.\nOr press 'ESC' to quit the game.");
  youLostMessage.setCharacterSize(30);
  youLostMessage.setPosition(60, 300);
  bool aiWon = false;

  // init message to press "Space" to play new game
  sf::Text pressSpace;
  pressSpace.setFont(font);
  pressSpace.setString("Press 'SPACE' to start.");
  pressSpace.setCharacterSize(30);
  pressSpace.setPosition(170, 500);

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

    // get elapsed time
    float elapsedTime = Clock.getElapsedTime().asSeconds();
    Clock.restart();

    // start/unpause game if "Space" is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      gameStarted = true;
    }

    // pause/unpause the game when "P" is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && gameStarted == true) {
      gameStarted = false;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && gameStarted == false) {
      gameStarted = true;
    }

    // pause game if window is out of focus (e.g. minimized)
    if (App.hasFocus() == false) {
      gameStarted = false;
    }

    //start a new game when "N" is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N) && gameStarted == false) {
      playerScore = 0;
      aiScore = 0;
      playerWon = false;
      aiWon = false;
      playerScoreTxt.setString(std::to_string(playerScore));
      aiScoreTxt.setString(std::to_string(aiScore));
    }

    // what to do when game is being played
    if (gameStarted == true) {
      // init bounding boxes for checking ball to paddle collision
      sf::FloatRect ballBoundingBox = ball.getGlobalBounds();
      sf::FloatRect playerPaddleBoundingBox = playerPaddle.getGlobalBounds();
      sf::FloatRect aiPaddleBoundingBox = aiPaddle.getGlobalBounds();

      // generate a random perturbation (between -0.2 and 0.2)
      float random = ((float) rand()) / (float) RAND_MAX;
      float r = random * (0.2 - (-0.2));
      float random_pert = -0.2 + r;

      // if the ball bounces off the paddles
      if (ballBoundingBox.intersects(playerPaddleBoundingBox) || ballBoundingBox.intersects(aiPaddleBoundingBox)) {
        ballDirection.x *= (-1.0 + random_pert);
      } else
      // if the ball bounces off the left wall (a.k.a. the ai scores)
      if (ball.getPosition().x - ballRadius <= 0) {
        ballDirection.x *= (-1.0 + random_pert);
        aiScore += 1;
        aiScoreTxt.setString(std::to_string(aiScore));
        gameStarted = false;
        ball.setPosition(appWidth / 2, appHeight / 2);
        playerPaddle.setPosition(0.0 + playerPaddle.getSize().x / 2, appHeight / 2);
        aiPaddle.setPosition(appWidth - aiPaddle.getSize().x / 2, appHeight / 2);
      } else
      // if the ball bounces off the right wall (a.k.a. the player scores)
      if (ball.getPosition().x + ballRadius >= appWidth) {
        ballDirection.x *= (-1.0 + random_pert);
        playerScore += 1;
        playerScoreTxt.setString(std::to_string(playerScore));
        gameStarted = false;
        ball.setPosition(appWidth / 2, appHeight / 2);
        playerPaddle.setPosition(0.0 + playerPaddle.getSize().x / 2, appHeight / 2);
        aiPaddle.setPosition(appWidth - aiPaddle.getSize().x / 2, appHeight / 2);
      } else

      // if the ball bounces off the top or bottom walls
      if ((ball.getPosition().y - ballRadius <= 0.0) || (ball.getPosition().y + ballRadius >= appHeight)) {
        ballDirection.y *= (-1.0 + random_pert);
      }

      // keep the ball moving
      ball.move(ballDirection.x * elapsedTime * ballSpeed, ballDirection.y * elapsedTime * ballSpeed);
      std::cout << "ballDirection.x == " + std::to_string(ballDirection.x) + ", ballDirection.y == " + std::to_string(ballDirection.y) << std::endl;

      // keyboard input for player paddle
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        if (playerPaddle.getPosition().y - playerPaddle.getSize().y / 2.0 > 0.0) {
          playerPaddle.move(0.0, -1.0 * elapsedTime * playerPaddleSpeed);
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        if (playerPaddle.getPosition().y + (playerPaddle.getSize().y / 2.0) < appHeight) {
          playerPaddle.move(0.0, elapsedTime * playerPaddleSpeed);
        }
      }

      // ai paddle movement
      if (ball.getPosition().x > appWidth / 2) {       // if ball is in the ai's half, move the paddle towards the ball
        if (aiPaddle.getPosition().y > ball.getPosition().y) {
            aiPaddle.move(0.0, -1.0 * elapsedTime * aiPaddleSpeed);
        } else if (aiPaddle.getPosition().y < ball.getPosition().y) {
            aiPaddle.move(0.0, elapsedTime * aiPaddleSpeed);
        }
      } else {      // else, move the ai paddle towards the center
        if (aiPaddle.getPosition().y > appHeight / 2) {
            aiPaddle.move(0.0, -1.0 * elapsedTime * aiPaddleSpeed);
        } else if (aiPaddle.getPosition().y < appHeight / 2) {
            aiPaddle.move(0.0, elapsedTime * aiPaddleSpeed);
        }
      }

    }

    // when a player reaches score 11
    if (playerScore == 11) {
      playerWon = true;
      gameStarted = false;
      playerScoreTxt.setString(std::to_string(playerScore));
      aiScoreTxt.setString(std::to_string(aiScore));
    } else if (aiScore == 11) {
      aiWon = true;
      gameStarted = false;
      playerScoreTxt.setString(std::to_string(playerScore));
      aiScoreTxt.setString(std::to_string(aiScore));
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
    if (playerWon == true) {
      App.draw(youWonMessage);
    } else if (aiWon == true) {
      App.draw(youLostMessage);
    }
    if ( (gameStarted == false) && (playerWon == false && aiWon == false) ) {
      App.draw(pressSpace);
    }

    // display
    App.display();
  }

  // Done.
  return 0;
}

// Bugs:
// TODO: (Critical) Ball sometimes slides across wall if it hits bottom wall or slides alongside wall/paddle if it hits side walls or paddles
//        - try printing the direction vectors and see what happens on contact
//        - last minute resort will be to create rectangles around the screen (hidden) and create using bounding boxes
//        - use else if's instead of just if's??
