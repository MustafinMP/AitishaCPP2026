#pragma once

#include "Ball.h"
#include <SFML/Graphics.hpp>

class Racket{
private:
  int x;
  int y;
  int w;
  int h;
  int vy;
  sf::RectangleShape rect;

public:
  Racket(int x, int y);
  void moveUp();
  void moveDown();
  void update(const int height);
  bool collideWithBall(Ball& ball);
  void draw(sf::RenderWindow& window);
};

