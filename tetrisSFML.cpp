#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using std::vector;
using std::abs;
using std::string;
using sf::Color;

const int width = 10;
const int height = 20;
const int scale = 40;

vector<char> shapeTypes = { 'I', 'J', 'L', 'O', 'Z', 'T', 'S' };

char randomShapeType() {
  return shapeTypes[abs(rand()) % 7];
}

vector<Color> colors = { Color::Blue, Color::Red, Color::Green, Color::Yellow };

int randomColor() {
  return abs(rand()) % colors.size() + 1;
}

Color getColor(int colorId) {
  return colors[colorId - 1];
}

class Shape {
public:
  int x, y, rotation, colorId;
  char type;

  Shape() : type(randomShapeType()), x(3), y(0), rotation(0), colorId(randomColor()) {};
  Shape(char type, int x, int y, int rotation, int colorId) : type(type), x(x), y(y), rotation(rotation), colorId(colorId) {};
};


class Tetris {
private:
  int points;
  vector<vector<int>> field;
  Shape currentShape;
  Shape nextShape;

public:
  Tetris() {
    points = 0;
    field.resize(height, vector<int>(width, 0));
  }

  void createNewShape() {
    currentShape = nextShape;
    nextShape = Shape();
  };

  void handleKeyboard() {};
  bool move() {};
  void rotate() {};
  bool collided() {};
  bool isFinished() {};
  void checkRows() {};
  void draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(scale, scale));
        rect.setPosition(sf::Vector2f(x * scale, y * scale));
        rect.setFillColor(Color::Black);
        rect.setOutlineColor(Color::White);
        rect.setOutlineThickness(1);
        window.draw(rect);
      }
    }
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(6 * scale, height * scale));
    rect.setPosition(sf::Vector2f(width * scale, 0));
    rect.setFillColor(Color::White);
    window.draw(rect);
  };
};

int main() {
  srand(time(nullptr));
  sf::RenderWindow window(sf::VideoMode({ (width + 6) * scale, height * scale }), "Game");
  window.setFramerateLimit(1);

  Tetris tetris;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* keypress = event->getIf<sf::Event::KeyPressed>()) {}
    };
    window.clear();
    tetris.draw(window);
    window.display();
  }
}

/*
Создать первую фигуру (и следующую)
пока (не поражение) то
  Обработка клавиш:
    если нажаты стрелки -> двигаем фигуру (если можем)
    если нажат поворот -> вращаем фигуру (если можем)

  Двигаем вниз на 1 шаг (либо полностью, если нажат пробел)
  если приземлились то
    проверяем заполненность рядов
    если не закончилась игра то
      создаем новую фигуру
    иначе 
      конец


*/