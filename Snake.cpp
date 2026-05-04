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

bool isValid(int x, int y) {
  return 0 <= x and x < width and 0 <= y and y < height;
}

struct Point {
  int x;
  int y;
};

class GameField {
private:
  deque<Point> snake;
  Point food;
  int dx, dy;
  bool gameOver = false;

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
    snake.push_back({ width / 2, height / 2 + 1 });
    snake.push_back({ width / 2, height / 2 + 2 });

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

  void update() {
    if (gameOver) {
      return;
    }

    Point head = snake.front();
    int next_x = head.x + dx;
    int next_y = head.y + dy;

    if (!isValid(next_x, next_y)) {
      std::cout << "You lose!!!";
      gameOver = true;
      return;
    }

    for (int i = 0; i < snake.size() - 1; i++) {
      if (next_x == snake[i].x and next_y == snake[i].y) {
        std::cout << "You lose!";
        gameOver = true;
        return;
      }
    }

    Point new_head;
    new_head.x = next_x;
    new_head.y = next_y;
    snake.push_front(new_head);

    if (next_x == food.x and next_y == food.y) {
      createFood();
    }
    else {
      snake.pop_back();
    }
  }

  void draw(sf::RenderWindow& window) {
    if (gameOver) {
      sf::RectangleShape rect;
      rect.setSize(sf::Vector2f(width * scale, height * scale));
      rect.setFillColor(sf::Color::Red);
      window.draw(rect);
    }
    else {
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
  }
};

int main() {
  srand(time(nullptr));
  sf::RenderWindow window(sf::VideoMode({ width * scale, height * scale }), "Game");
  window.setFramerateLimit(4);

  GameField game;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* keypress = event->getIf<sf::Event::KeyPressed>()) {
        game.handleInput(keypress->code);
      }
    }
    game.update();
    window.clear();
    game.draw(window);
    window.display();
  }
}
