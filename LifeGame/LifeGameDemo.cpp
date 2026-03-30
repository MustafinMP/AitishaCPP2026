#include <SFML/Graphics.hpp>
#include <iostream>

using std::vector;

const int width = 25;
const int height = 20;
const int scale = 25;

void initGrid(vector<vector<int>>& grid) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      grid[y][x] = (std::rand() % 100 < 30) ? 1 : 0;
    }
  }
};

int countNeightbours(vector<vector<int>>& grid, int x, int y) {
  int count = 0;
  int lx = (x + width - 1) % width;
  int rx = (x + 1) % width;
  int ty = (y + height - 1) % height;
  int by = (y + 1) % height;
  count += grid[ty][lx];
  count += grid[ty][x];
  count += grid[ty][rx];
  count += grid[y][rx];
  count += grid[by][rx];
  count += grid[by][x];
  count += grid[by][lx];
  count += grid[y][lx];
  return count;
};

void update(vector<vector<int>>& grid) {
  vector<vector<int>> nextGrid(height, vector<int>(width, 0));

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int count = countNeightbours(grid, x, y);

      if (count < 2) {
        nextGrid[y][x] = 0;
      }
      if (count > 3) {
        nextGrid[y][x] = 0;
      }
      if ((count == 2 || count == 3) && grid[y][x] == 1) {
        nextGrid[y][x] = 1;
      }
      if (count == 3) {
        nextGrid[y][x] = 1;
      }
    }
  }

  grid = nextGrid;
};

void draw(sf::RenderWindow& window, vector<vector<int>>& grid) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (grid[y][x] == 1) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(scale, scale));
        rect.setPosition(sf::Vector2f(x * scale, y * scale));
        window.draw(rect);
      }
    }
  }
};

int main() {
  sf::RenderWindow window(sf::VideoMode({ width * scale, height * scale }), "Life game");
  window.setFramerateLimit(1);

  vector<vector<int>> grid(height, vector<int>(width, 0));

  initGrid(grid);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    update(grid);
    window.clear();
    draw(window, grid);
    window.display();
  }
}

