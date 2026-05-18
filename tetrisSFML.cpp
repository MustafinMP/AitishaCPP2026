#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include <array>
#include <cctype>
#include <stdexcept>

using std::vector;
using std::abs;
using std::string;
using std::array;
using sf::Color;

const int width = 10;
const int height = 20;
const int scale = 40;

using ShapeMask = array<array<bool, 4>, 4>;
using ShapeMasks = array<ShapeMask, 4>;

const ShapeMasks MASK_I = { {
    {{{{0,0,0,0}}, {{1,1,1,1}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}}},
    {{{{0,0,0,0}}, {{1,1,1,1}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}}}
} };

const ShapeMasks MASK_O = { {
    {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}}
} };

const ShapeMasks MASK_T = { {
    {{{{0,1,0,0}}, {{1,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,1,0,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{1,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}}}},
    {{{{0,1,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}, {{0,0,0,0}}}}
} };

const ShapeMasks MASK_S = { {
    {{{{0,1,1,0}}, {{1,1,0,0}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,1,0,0}}, {{0,1,1,0}}, {{0,0,1,0}}, {{0,0,0,0}}}},
    {{{{0,1,1,0}}, {{1,1,0,0}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,1,0,0}}, {{0,1,1,0}}, {{0,0,1,0}}, {{0,0,0,0}}}}
} };

const ShapeMasks MASK_Z = { {
    {{{{1,1,0,0}}, {{0,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,0,1,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}}}},
    {{{{1,1,0,0}}, {{0,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,0,1,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}}}}
} };

const ShapeMasks MASK_J = { {
    {{{{0,1,0,0}}, {{0,1,0,0}}, {{1,1,0,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{1,1,1,0}}, {{1,0,0,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}}},
    {{{{0,0,0,0}}, {{0,0,1,0}}, {{1,1,1,0}}, {{0,0,0,0}}}}
} };

const ShapeMasks MASK_L = { {
    {{{{0,0,1,0}}, {{0,0,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{1,1,1,0}}, {{0,0,1,0}}, {{0,0,0,0}}}},
    {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,1,0,0}}}},
    {{{{0,0,0,0}}, {{1,0,0,0}}, {{1,1,1,0}}, {{0,0,0,0}}}}
} };

ShapeMasks getShapeMask(char type) {
  if (type == 'I') { return MASK_I; }
  if (type == 'J') { return MASK_J; }
  if (type == 'L') { return MASK_L; }
  if (type == 'O') { return MASK_O; }
  if (type == 'Z') { return MASK_Z; }
  if (type == 'T') { return MASK_T; }
  if (type == 'S') { return MASK_S; }
}

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
  ShapeMasks masks;

  Shape() : type(randomShapeType()), x(3), y(0), rotation(0), colorId(randomColor()) {
    this->masks = getShapeMask(this->type);
  };
  Shape(char type, int x, int y, int rotation, int colorId) : type(type), x(x), y(y), rotation(rotation), colorId(colorId) {
    this->masks = getShapeMask(this->type);
  };
  void move() {
    y += 1;
  };
  void rotate() {};

  bool onBottom() {
    for (int sy = 0; sy < 4; sy++) {
      for (int sx = 0; sx < 4; sx++) {
        if (masks[rotation][sy][sx] and y + sy == height - 1) {
          return true;
        }
      }
    }
    return false;
  }

  void addToField(vector<vector<int>>& field) {
    for (int sy = 0; sy < 4; sy++) {
      for (int sx = 0; sx < 4; sx++) {
        if (masks[rotation][sy][sx]) {
          field[y + sy][x + sx] = colorId;
        }
      }
    }
  }

  void draw(sf::RenderWindow& window) {
    for (int sy = 0; sy < 4; sy++) {
      for (int sx = 0; sx < 4; sx++) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(scale, scale));
        rect.setPosition(sf::Vector2f((sx + x) * scale, (sy + y) * scale));
        if (masks[rotation][sy][sx]) {
          rect.setFillColor(getColor(colorId));
        }
        else {
          rect.setFillColor(Color::Black);
        }
        rect.setOutlineColor(Color::White);
        rect.setOutlineThickness(1);
        window.draw(rect);
      }
    }
  }
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

  bool move() {
    currentShape.move();
    if (currentShape.onBottom()) {
      currentShape.addToField(field);
      checkRows();
      createNewShape();
      return true;
    }
    return false;
  };

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
        if (field[y][x] == 0) {
          rect.setFillColor(Color::Black);
        }
        else {
          rect.setFillColor(getColor(field[y][x]));
        }
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

    currentShape.draw(window);
  };
};

int main() {
  srand(time(nullptr));
  bool touched = false;
  sf::RenderWindow window(sf::VideoMode({ (width + 6) * scale, height * scale }), "Game");
  window.setFramerateLimit(1);

  Tetris tetris;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* keypress = event->getIf<sf::Event::KeyPressed>()) {}
    };
    touched = tetris.move();

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
