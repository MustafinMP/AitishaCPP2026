#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::abs;

const int width = 16;
const int height = 16;
const int scale = 50;

sf::Font font;

bool isValid(int x, int y) {
  return 0 <= x && x < width && 0 <= y && y < height;
}

struct Cell {
  bool is_mine = false;
  int neightbor_mines = 0;
  bool is_opened = false;
  bool is_flagged = false;
};

class Board {
private:
  vector<vector<Cell>> grid;

  void placeMines(int minesCount) {
    int placed = 0;
    while (placed < minesCount) {
      int x = abs(rand()) % width;
      int y = abs(rand()) % height;
      if (!grid[y][x].is_mine) {
        grid[y][x].is_mine = true;
        placed += 1;
      }
    }
  }

  void countNeightbors() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (grid[y][x].is_mine) continue;

        for (int dy = -1; dy <= 1; dy++) {
          for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int cx = x + dx;
            int cy = y + dy;
            if (isValid(cx, cy) && grid[cy][cx].is_mine) {
              grid[y][x].neightbor_mines += 1;
            }
          }
        }
      }
    }
  }

public:
  Board(int mines) {
    grid.resize(height, vector<Cell>(width));
    placeMines(mines);
    countNeightbors();
  }

  void toggleFlag(int x, int y) {
    if (isValid(x, y) && !grid[y][x].is_opened) {
      grid[y][x].is_flagged = !grid[y][x].is_flagged;
    }
  }

  void open(int x, int y) {
    if (isValid(x, y) && !grid[y][x].is_opened && !grid[y][x].is_flagged) {
      grid[y][x].is_opened = true;

      if (grid[y][x].neightbor_mines == 0) {
        for (int dy = -1; dy <= 1; dy++) {
          for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            open(x + dx, y + dy);
          }
        }
      }
    }
  }

  bool isGameOver() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (grid[y][x].is_opened && grid[y][x].is_mine) return true;
      }
    }
    return false;
  }

  bool isWin() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (!((grid[y][x].is_mine && grid[y][x].is_flagged) || grid[y][x].is_opened)) return false;
      }
    }
    return true;
  }

  void draw(sf::RenderWindow& window) {
    graphicsDraw(window);
  }

  void graphicsDraw(sf::RenderWindow& window) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        Cell cell = grid[y][x];
        drawCell(window, cell, x, y);
      }
    }
  }

  void drawCell(sf::RenderWindow& window, Cell& cell, int x, int y) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(scale, scale));
    rect.setPosition(sf::Vector2f(x * scale, y * scale));
    rect.setFillColor(sf::Color(120, 120, 120));
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);
    window.draw(rect);
    if (cell.is_opened) {
      sf::Text text(font, std::to_string(cell.neightbor_mines), scale);
      text.setPosition(sf::Vector2f(x * scale, y * scale));
      window.draw(text);
    }
    else if (cell.is_flagged) {
      sf::CircleShape flag(scale / 2);
      flag.setPosition(sf::Vector2f(x * scale, y * scale));
      flag.setFillColor(sf::Color::Red);
      window.draw(flag);
    }
    else {
      rect.setFillColor(sf::Color(90, 90, 90));
    }
  }

  void consoleDraw() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        Cell cell = grid[y][x];
        if (cell.is_opened) {
          std::cout << cell.neightbor_mines << ' ';
        } 
        else if (cell.is_flagged) {
          std::cout << "F ";
        }
        else {
          std::cout << "? ";
        }
      }
      std::cout << std::endl;
    }
  }
};


int main() {
  if (!font.openFromFile("consola.ttf")) {
    return -1;
  }
  sf::RenderWindow window(sf::VideoMode({ width * scale, height * scale }), "Game");
  //window.setFramerateLimit(1);

  Board board(15);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
        int x = mouseClick->position.x / scale;
        int y = mouseClick->position.y / scale;
        if (mouseClick->button == sf::Mouse::Button::Left) {
          board.open(x, y);
        }

        else if (mouseClick->button == sf::Mouse::Button::Right) {
          board.toggleFlag(x, y);
        }
      }
    }

    window.clear();
    // дописать проверку на найденную бомбу
    board.draw(window);
    window.display();
  }
}

/*
int main() {
  Board board(15);
  board.consoleDraw();
  while (true) {
    std::string command;
    int x, y;
    std::cout << "Enter command >>";
    std::cin >> command;
    std::cin >> x;
    std::cin >> y;
    if (command == "open") {
      board.open(x, y);
    }
    else if (command == "flag") {
      board.toggleFlag(x, y);
    }
    if (board.isGameOver()) {
      std::cout << "You lose!";
      break;
    }
    if (board.isWin()) {
      std::cout << "You win!";
      break;
    }
    board.draw();
  }
}

*/
