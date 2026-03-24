#pragma once

#include <SFML/Graphics.hpp>

class Ball { 
private:
  int vx;
  int vy;
  sf::CircleShape circle;

public:
  int x;
  int y;
  int radius;
  Ball(int x, int y, int radius);
  void move(const int width, const int height);
  void pongToRight();
  void pongToLeft();
  void draw(sf::RenderWindow& window);
  bool touchedLeftSide();
  bool touchedRightSide(const int width);
  void setPosition(int x, int y);
};

