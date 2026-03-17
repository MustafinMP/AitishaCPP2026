#pragma once

#include <SFML/Graphics.hpp>

class Ball { 
private:
  int x;
  int y;
  int radius;
  int vx;
  int vy;
  sf::CircleShape circle;

public:
  Ball(int x, int y, int radius);
  void move(const int width, const int height);
  void pong();
  void draw(sf::RenderWindow& window);
  bool touchedLeftSide();
  bool touchedRightSide(const int width);
  void setPosition(int x, int y);
};

