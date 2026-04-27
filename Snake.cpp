#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <ctime>

using std::vector;
using std::abs;
using std::deque;
using std::string;

const int width = 25;
const int height = 20;
const int scale = 50;

struct Point {
  int x;
  int y;
};

class GameField {
private:
  deque<Point> snake;
  Point food;
  int dx, dy;

  void createFood() {
    while (true) {
      int x = rand() % width;
      int y = rand() % height;

      bool onSnake = false;
      for (const auto& p : snake) {
        if (p.x == x && p.y == y) {
          onSnake = true;
          break;
        }
      }

      if (!onSnake) {
        food = { x, y };
        break;
      }
    }
  }

public:
  GameField() {
    snake.push_back({ width / 2, height / 2 });
    snake.push_back({ width / 2, height / 2 - 1 });
    snake.push_back({ width / 2, height / 2 - 2 });

    dx = 0;
    dy = -1;

    createFood();
  }

  void handleInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::Up && dy != 1) {
      dx = 0;
      dy = -1;
    }
    else if (key == sf::Keyboard::Key::Down && dy != -1) {
      dx = 0;
      dy = 1;
    }
    else if (key == sf::Keyboard::Key::Right && dx != -1) {
      dx = 1;
      dy = 0;
    }
    else if (key == sf::Keyboard::Key::Left && dx != 1) {
      dx = -1;
      dy = 0;
    }
  }

  void update() {}

  void draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(scale, scale));
        rect.setPosition(sf::Vector2f(x * scale, y * scale));
        rect.setFillColor(sf::Color::Green);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        window.draw(rect);
      }
    }
    for (const auto& p : snake) {
      sf::RectangleShape rect;
      rect.setSize(sf::Vector2f(scale, scale));
      rect.setPosition(sf::Vector2f(p.x * scale, p.y * scale));
      rect.setFillColor(sf::Color::Yellow);
      rect.setOutlineColor(sf::Color::White);
      rect.setOutlineThickness(1);
      window.draw(rect);
    }

    sf::CircleShape apple(scale / 2);
    apple.setPosition(sf::Vector2f(food.x * scale, food.y * scale));
    apple.setFillColor(sf::Color::Red);
    window.draw(apple);
  }
};

int main() {
  srand(time(nullptr));
  sf::RenderWindow window(sf::VideoMode({ width * scale, height * scale }), "Game");
  //window.setFramerateLimit(1);

  GameField game;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {}
    }

    window.clear();
    game.draw(window);
    window.display();
  }
}