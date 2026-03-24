// SFMLApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Racket.h"

int main() {
  const int width = 1000;
  const int height = 600;

  sf::RenderWindow window(sf::VideoMode({ width, height }), "Ping Pong");
  window.setFramerateLimit(60);
  Ball ball(500, 300, 30);
  Racket leftRacket(50, 150);
  Racket rightRacket(900, 150);

  
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (const auto* keypress = event->getIf<sf::Event::KeyPressed>()) {
        if (keypress->code == sf::Keyboard::Key::Q) {
          leftRacket.moveUp();
        }
        else if (keypress->code == sf::Keyboard::Key::A) {
          leftRacket.moveDown();
        }
        else if (keypress->code == sf::Keyboard::Key::P) {
          rightRacket.moveUp();
        }
        else if (keypress->code == sf::Keyboard::Key::L) {
          rightRacket.moveDown();
        }
      }
    }

    if (leftRacket.collideWithBall(ball)) {
      ball.pongToRight();
    }
    if (rightRacket.collideWithBall(ball)) {
      ball.pongToLeft();
    }

    leftRacket.update(height);
    rightRacket.update(height);
    ball.move(width, height);

    window.clear();
    leftRacket.draw(window);
    rightRacket.draw(window);
    ball.draw(window);
    window.display();
  }
}

