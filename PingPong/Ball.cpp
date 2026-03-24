#include "Ball.h"

#include <SFML/Graphics.hpp>

Ball::Ball(int x, int y, int radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->vx = 2;
    this->vy = 1;
    this->circle = sf::CircleShape(radius);
    this->circle.setPosition(sf::Vector2f(x - radius, y - radius));
};

void Ball::move(const int width, const int height) {
  // проверка выхода за левую границу экрана
  if (this->x - this->radius <= 0) {
    this->vx = 2;
  }
  // проверка выхода за правую границу экрана
  else if (this->x + this->radius >= width) {
    this->vx = -2;
  }
  // проверка выхода за верхнюю границу экрана
  if (this->y - this->radius <= 0) {
    this->vy = 1;
  }
  // проверка выхода за нижнюю границу экрана
  else if (this->y + this->radius >= height) {
    this->vy = -1;
  }

  this->x += this->vx;
  this->y += this->vy;
  this->circle.setPosition(sf::Vector2f(this->x - this->radius, this->y - this->radius));
};

void Ball::pongToLeft() {
  this->vx = -2;
};

void Ball::pongToRight() {
  this->vx = 2;
};

void Ball::draw(sf::RenderWindow& window) {
    window.draw(circle);
};

bool Ball::touchedLeftSide() {
  return this->x - this->radius <= 0;
}

bool Ball::touchedRightSide(const int width) {
  return this->x + this->radius >= width;
}

void Ball::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
  this->circle.setPosition(sf::Vector2f(this->x - this->radius, this->y - this->radius));
}