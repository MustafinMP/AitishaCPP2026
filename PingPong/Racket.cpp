#include "Racket.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Racket::Racket(int x, int y) {
  this->x = x;
  this->y = y;
  this->w = 50;
  this->h = 150;
  this->rect.setSize(sf::Vector2f(this->w, this->h));
  this->rect.setPosition(sf::Vector2f(x, y));
  this->vy = 0;
}

void Racket::moveUp() {
  this->vy = -3;
};

void Racket::moveDown() {
  this->vy = 3;
};

void Racket::update(const int height) {
  if (this->vy < 0 && this->y > 0) {
    this->y += this->vy;
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
  }
  else if (this->vy > 0 && this->y + this->h < height) {
    this->y += this->vy;
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
  }
};

bool Racket::collideWithBall(Ball& ball) {
  int closest_x = std::max(this->x, std::min(ball.x, this->x + this->w));
  int closest_y = std::max(this->y, std::min(ball.y, this->y + this->h));

  int dx = ball.x - closest_x;
  int dy = ball.y - closest_y;
  return dx * dx + dy * dy <= ball.radius * ball.radius;
};

void Racket::draw(sf::RenderWindow& window) {
  window.draw(rect);
};