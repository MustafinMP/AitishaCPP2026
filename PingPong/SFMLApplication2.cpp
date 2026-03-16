#include <SFML/Graphics.hpp>
#include "Ball.h"

int main() {
  const int width = 1000;
  const int height = 600;

  sf::RenderWindow window(sf::VideoMode({ width, height }), "Ping Pong");
  window.setFramerateLimit(60);
  Ball ball(500, 300, 30);
  
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    ball.move(width, height);

    window.clear();
    ball.draw(window);
    window.display();
  }
}
