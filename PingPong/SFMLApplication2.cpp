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
    }

    ball.move(width, height);

    window.clear();
    leftRacket.draw(window);
    rightRacket.draw(window);
    ball.draw(window);
    window.display();
  }
}
